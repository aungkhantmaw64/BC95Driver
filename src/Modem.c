#include "Modem.h"
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
    ModemController modem = calloc(1, sizeof(struct ModemStruct));
    modem->serial = serial;
    modem->resetPin = resetPin;
    return modem;
}

void ModemController_Destroy(ModemController modem)
{
    if (modem)
        free(modem);
}

static int sendATCmd(ModemController modem, const char *cmd, const char *expected_reponse, uint32_t timeout_ms)
{
    SerialIO_Print(modem->serial, cmd);
    uint32_t current = getMillis();
    while ((getMillis() - current) < timeout_ms)
    {
        if (SerialIO_IsAvailable(modem->serial) > 0)
        {
            SerialIO_ReadStringUntil(modem->serial, modem->rxBuffer, '\n', 300);
            if (findSubstringIndex(modem->rxBuffer, expected_reponse) >= 0)
                return CMD_SUCCESS;
            else
                return CMD_FAILED;
        }
    }
    return CMD_FAILED;
}

int ModemController_RebootUE(ModemController modem)
{
    return sendATCmd(modem, "AT+NRB\r", "REBOOT", 300);
}
