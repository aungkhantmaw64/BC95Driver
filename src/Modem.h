#ifndef MODEM_H
#define MODEM_H

#include "SerialIO.h"

typedef struct ModemStruct *ModemController;

#define MAX_BUFFER_SIZE 50

enum
{
    CMD_FAILED = -1,
    CMD_SUCCESS = 0
};

struct ModemStruct
{
    SerialIO_t serial;
    int resetPin;
    char rxBuffer[MAX_BUFFER_SIZE];
};

ModemController ModemController_Create(SerialIO_t serial, int resetPin);
void ModemController_Destroy(ModemController modem);
int ModemController_RebootUE(ModemController modem);
int ModemController_IsReady(void);

#endif // MODEM_H
