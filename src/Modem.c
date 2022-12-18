#include "Modem.h"
#include <stdio.h>
#include <stdlib.h>
#include "TimeService.h"
#include <string.h>
#include <memory.h>
#include "SubStringSearch.h"

#define MODEM_BAUDRATE 9600

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

void ModemController_sendATCmd(ModemController modem, const char *cmd)
{
    SerialIO_Print(modem->serial, cmd);
    uint32_t startTime = getMillis();
    char temp[MAX_BUFFER_SIZE];
    memset(modem->responseBuffer, 0, MAX_BUFFER_SIZE);
    while ((getMillis() - startTime) < 300)
    {
        if (SerialIO_IsAvailable(modem->serial) > 0)
        {
            memset(temp, 0, MAX_BUFFER_SIZE);
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
    ModemController_sendATCmd(modem, "AT+NRB\r");
    return _checkResponseStatus(modem, "REBOOT");
}

int ModemController_IsReady(ModemController modem)
{
    ModemController_sendATCmd(modem, "AT\r");
    return _hasValidResponse(modem);
}

int ModemController_SetUEFunction(ModemController modem, UEFunction_t mode)
{
    ModemController_sendATCmd(modem, "AT+CFUN=1\r");
    return _checkResponseStatus(modem, "OK");
}

/* main_str: Target String
 *  from_: starts extracting from the end index of this substring until 'end'
 * dest: destination to store the extracted string
 */
static void _extractString(char *target_str, char *from_, char end, char *dest)
{

    int t = findSubstringIndex(target_str, from_) + strlen(from_);
    int i = 0;
    while (target_str[t] != end)
    {
        dest[i++] = target_str[t++];
    }
}

int ModemController_GetIMEI(ModemController modem, char *dest)
{
    ModemController_sendATCmd(modem, "AT+CGSN=1\r");
    int resStatus = _checkResponseStatus(modem, "OK");
    if (resStatus != CMD_SUCCESS)
        return resStatus;
    else
    {
        int buffSize = sizeof(dest) / sizeof(char);
        memset(dest, 0, buffSize);
        _extractString(modem->responseBuffer, "+CGSN:", '\n', dest);
        return resStatus;
    }
}

int ModemController_IsNetworkConnected(ModemController modem)
{
    ModemController_sendATCmd(modem, "AT+CGATT?\r");
    int resStatus = _checkResponseStatus(modem, "OK");
    if (resStatus != CMD_SUCCESS)
        return 0;
    else
    {
        char currentMode[2];
        memset(currentMode, 0, 2);
        _extractString(modem->responseBuffer, "+CGATT:", '\n', currentMode);
        return (strcmp("1", currentMode) == 0);
    }
}