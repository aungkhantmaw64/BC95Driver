#ifndef MODEM_H
#define MODEM_H

#include "SerialIO.h"

typedef struct ModemStruct *ModemController;

#define MAX_BUFFER_SIZE 50

enum
{
    CMD_TIMEOUT_ERROR = -2,
    CMD_FAILED = -1,
    CMD_SUCCESS = 0
};

typedef enum UEFunctionEnum
{
    UE_LEVEL_MINIMUM,
    UE_LEVEL_FULL,
} UEFunction_t;

struct ModemStruct
{
    SerialIO_t serial;
    int resetPin;
    char rxBuffer[MAX_BUFFER_SIZE];
};

ModemController ModemController_Create(SerialIO_t serial, int resetPin);
void ModemController_Destroy(ModemController modem);
int ModemController_RebootUE(ModemController modem);
int ModemController_IsReady(ModemController modem);
int ModemController_SetUEFunction(ModemController modem, UEFunction_t mode);
#endif // MODEM_H
