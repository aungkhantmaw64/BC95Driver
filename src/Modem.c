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

int ModemController_RebootUE(ModemController modem)
{
    SerialIO_Print(modem->serial, "AT+NRB\r");
    uint32_t time = getMillis();
    while ((getMillis() - time) < 300)
    {
        if (SerialIO_IsAvailable(modem->serial) > 0)
        {
            SerialIO_ReadStringUntil(modem->serial, modem->rxBuffer, '\n', 300);
            if (findSubstringIndex(modem->rxBuffer, "REBOOT") >= 0)
                return 0;
            else
                return -1;
        }
    }
    return -1;
}