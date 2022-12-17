#include "Modem.h"
#include <stdio.h>
#include <stdlib.h>
#include "TimeService.h"
#include <string.h>
#include <memory.h>

#define MODEM_BAUDRATE 9600

int findSubstringIndex(const char *main_str, const char *sub_str)
{
    char *temp = strstr(main_str, sub_str);
    if (!temp)
        return -1;
    return temp - main_str;
}

ModemController ModemController_Create(SerialIO_t serial, int resetPin)
{
    if (!serial)
        return NULL;
    ModemController modem = calloc(1, sizeof(struct ModemControllerStruct));
    modem->serial = serial;
    modem->resetPin = resetPin;
    return modem;
}

void ModemController_Destroy(ModemController modem)
{
    if (modem)
        free(modem);
}

static void _sendATCmd(ModemController modem, const char *cmd)
{
    SerialIO_Print(modem->serial, cmd);
    uint32_t startTime = getMillis();
    char temp[MAX_BUFFER_SIZE];
    memset(temp, 0, MAX_BUFFER_SIZE);
    memset(modem->responseBuffer, 0, MAX_BUFFER_SIZE);
    while ((getMillis() - startTime) < 300)
    {
        if (SerialIO_IsAvailable(modem->serial) > 0)
        {
            SerialIO_ReadStringUntil(modem->serial, temp, '\n', 300);
            if (strlen(modem->responseBuffer) == 0)
                strcpy(modem->responseBuffer, temp);
            else
                strcat(modem->responseBuffer, temp);
        }
    }
}

static int _checkResponseStatus(ModemController modem, const char *expected_response)
{
    if (strlen(modem->responseBuffer) == 0)
        return CMD_TIMEOUT_ERROR;
    else
    {
        if (findSubstringIndex(modem->responseBuffer, expected_response) != -1)
            return CMD_SUCCESS;
        else
            return CMD_FAILED;
    }
}

static int _hasValidResponse(ModemController modem)
{
    return (_checkResponseStatus(modem, "OK") == CMD_SUCCESS);
}

int ModemController_RebootUE(ModemController modem)
{
    _sendATCmd(modem, "AT+NRB\r");
    return _checkResponseStatus(modem, "REBOOT");
}

int ModemController_IsReady(ModemController modem)
{
    _sendATCmd(modem, "AT\r");
    return _hasValidResponse(modem);
}

int ModemController_SetUEFunction(ModemController modem, UEFunction_t mode)
{
    _sendATCmd(modem, "AT+CFUN=1\r");
    return _checkResponseStatus(modem, "OK");
}

int ModemController_GetIMEI(ModemController modem, char *buffer)
{
    _sendATCmd(modem, "AT+CGSN=1\r");
    int buffSize = sizeof(buffer) / sizeof(char);
    memset(buffer, 0, buffSize);
    int resStatus = _checkResponseStatus(modem, "OK");
    if (resStatus != CMD_SUCCESS)
        return resStatus;
    int index = findSubstringIndex(modem->responseBuffer, "+CGSN:") + strlen("+CGSN:");
    int buffer_i = 0;
    while (modem->responseBuffer[index] != '\n')
    {
        buffer[buffer_i++] = modem->responseBuffer[index++];
    }
    return resStatus;
}