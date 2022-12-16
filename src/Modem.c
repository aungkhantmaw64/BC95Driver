#include "Modem.h"
#include <stdlib.h>

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