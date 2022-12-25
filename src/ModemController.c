#include "ModemController.h"
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
    modem->netstat.mode = 0;
    modem->netstat.stat = 0;
    modem->netstat.conn = 0;
    return modem;
}

void ModemController_Destroy(ModemController modem)
{
    if (modem)
        free(modem);
}

void ModemController_SendATCmd(ModemController modem, const char *cmd)
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

static void _clearBuffer(char *buffer)
{
    int _size = sizeof(buffer) / sizeof(char);
    memset(buffer, 0, _size);
}

/* This function find a string between from_ and to_ in target_str.
Then, put it in dest*/

static void _getSubstring(char *target_str, char *from_, char to_, char *dest)
{

    int t = findSubstringIndex(target_str, from_) + strlen(from_);
    int i = 0;
    while (target_str[t] != to_)
    {
        dest[i++] = target_str[t++];
    }
}

int ModemController_RebootUE(ModemController modem)
{
    ModemController_SendATCmd(modem, "AT+NRB\r");
    return _checkResponseStatus(modem, "REBOOT");
}

int ModemController_IsReady(ModemController modem)
{
    ModemController_SendATCmd(modem, "AT\r");
    return _hasValidResponse(modem);
}

int ModemController_SetUEFunction(ModemController modem, UEFunction_t mode)
{
    ModemController_SendATCmd(modem, "AT+CFUN=1\r");
    return _checkResponseStatus(modem, "OK");
}

/* main_str: Target String
 *  from_: starts extracting from the end index of this substring until 'end'
 * dest: destination to store the extracted string
 */

int ModemController_GetIMEI(ModemController modem, char *dest)
{
    ModemController_SendATCmd(modem, "AT+CGSN=1\r");
    int resStatus = _checkResponseStatus(modem, "OK");
    if (resStatus == CMD_SUCCESS)
    {
        _clearBuffer(dest);
        _getSubstring(modem->responseBuffer, "+CGSN:", '\n', dest);
    }
    return resStatus;
}

int ModemController_GetIMSI(ModemController modem, char *dest)
{
    ModemController_SendATCmd(modem, "AT+CIMI\r");
    int resStatus = _checkResponseStatus(modem, "OK");
    if (resStatus == CMD_SUCCESS)
    {
        _clearBuffer(dest);
        int idx = 2; /* Starts with 2 since 0 and 1 are \r\n*/
        while (modem->responseBuffer[idx] != '\r')
        {
            dest[idx - 2] = modem->responseBuffer[idx];
            idx++;
        }
    }
    return resStatus;
}

int ModemController_GetNetworkRegiStat(ModemController modem)
{
    ModemController_SendATCmd(modem, "AT+CEREG?\r");
    int resStatus = _checkResponseStatus(modem, "OK");
    if (resStatus == CMD_SUCCESS)
    {
        char status[10];
        memset(status, 0, 10);
        _getSubstring(modem->responseBuffer, "+CEREG:", '\r', status);
        modem->netstat.mode = (OperationModeBit)status[0];
        modem->netstat.stat = (RegistrationStatusBit)status[2];
    }
    return resStatus;
}

int ModemController_IsNetworkConnected(ModemController modem)
{
    ModemController_SendATCmd(modem, "AT+CGATT?\r");
    int resStatus = _checkResponseStatus(modem, "OK");
    if (resStatus == CMD_SUCCESS)
    {
        char state[2];
        memset(state, 0, 2);
        _getSubstring(modem->responseBuffer, "+CGATT:", '\r', state);
        return ((ConnectionStatusBit)state[0] == UE_NETWORK_CONNECTED);
    }
    return 0;
}