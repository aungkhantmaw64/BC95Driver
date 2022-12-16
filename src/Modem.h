#ifndef MODEM_H
#define MODEM_H

#include "SerialIO.h"

typedef struct ModemStruct *ModemController;

struct ModemStruct
{
    SerialIO_t serial;
    int resetPin;
};

ModemController ModemController_Create(SerialIO_t serial, int resetPin);
void ModemController_Destroy(ModemController modem);
int ModemController_IsReady(void);

#endif // MODEM_H
