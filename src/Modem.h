#ifndef MODEM_H
#define MODEM_H

#include "SerialIO.h"

#define MAX_BUFFER_SIZE 50

enum
{
    CMD_TIMEOUT_ERROR = -2,
    CMD_FAILED = -1,
    CMD_SUCCESS = 0
}; /* Command response status */

typedef enum UEFunctionEnum
{
    UE_LEVEL_MINIMUM,
    UE_LEVEL_FULL,
} UEFunction_t; /* UE Functionality Level */

typedef struct ModemControllerStruct *ModemController;

struct ModemControllerStruct
{
    SerialIO_t serial;
    int resetPin;
    char responseBuffer[MAX_BUFFER_SIZE];
}; /* Struct containing modem infos*/

/**
 * @brief Create a modem controller instance
 *
 * @param serial Pointer to the UART peripheral the modem accociates with
 * @param resetPin Digital IO pin to reboot the modem by hardware
 * @return ModemController if success, NULL otherwise
 */
ModemController ModemController_Create(SerialIO_t serial, int resetPin);
/**
 * @brief Free the modem controller and its memory allocations
 *
 * @param modem The modem
 */
void ModemController_Destroy(ModemController modem);
/**
 * @brief Reboot the modem by software
 *
 * @param modem The modem
 * @return Command reponse status
 */
int ModemController_RebootUE(ModemController modem);
/**
 * @brief Check if the connection to the modem is correct
 *        and ready to receive commands
 *
 * @param modem The modem
 * @return 1 if ready. 0 if not.
 */
int ModemController_IsReady(ModemController modem);
/**
 * @brief Set the UE phone function
 *
 * @param modem The modem
 * @param mode Functionality level
 * @return Command response status
 */
int ModemController_SetUEFunction(ModemController modem, UEFunction_t mode);

#endif // MODEM_H
