#ifdef TEST

#include "unity.h"
#include <stdlib.h>
#include "Modem.h"
#include "mock_SerialIO.h"
#include "FakeTimeService.h"

#include <string.h>

#define UART_NO 2
#define BAUDRATE 9600
#define RESET_PIN 26

struct SerialIOStruct
{
    int number;
    uint32_t baudrate;
};

static SerialIO_t getSerialIO(int number, uint32_t baudrate)
{
    SerialIO_t temp = calloc(1, sizeof(struct SerialIOStruct));
    temp->number = number;
    temp->baudrate = baudrate;
    return temp;
}

static SerialIO_t io = NULL;

void setUp(void)
{
    FakeTimeService_Create(0, 100);
}

void tearDown(void)
{
    FakeTimeService_Destroy();
}

void _mockATCommand(SerialIO_t expected_io, const char *cmd, char *response)
{
    SerialIO_Print_Expect(expected_io, cmd);
    SerialIO_IsAvailable_ExpectAndReturn(expected_io, 7);
    SerialIO_ReadStringUntil_Expect(expected_io, NULL, '\n', 300);
    SerialIO_ReadStringUntil_IgnoreArg_buffer();
    SerialIO_ReadStringUntil_ReturnArrayThruPtr_buffer(response, strlen(response));
}

void test_CreateSucceeds(void)
{
    io = getSerialIO(UART_NO, BAUDRATE);
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, io);
    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);
    TEST_ASSERT_NOT_NULL(modem);
    TEST_ASSERT_EQUAL(io, modem->serial);
    TEST_ASSERT_EQUAL(RESET_PIN, modem->resetPin);
}

void test_CreateFailed_WhenSerialIsNULL(void)
{
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, NULL);
    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);

    TEST_ASSERT_NULL(modem);
}

void test_RebootUE(void)
{
    io = getSerialIO(UART_NO, BAUDRATE);

    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, io);
    _mockATCommand(io, "AT+NRB\r", "\r\nREBOOT\r\n");

    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);
    int retval = ModemController_RebootUE(modem);

    TEST_ASSERT_EQUAL_STRING("\r\nREBOOT\r\n", modem->rxBuffer);
    TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, retval);
}

void test_ModemIsReadyImmediately(void)
{
    io = getSerialIO(UART_NO, BAUDRATE);
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, io);
    _mockATCommand(io, "AT\r", "\r\nOK\r\n");

    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);
    TEST_ASSERT_EQUAL(1, ModemController_IsReady(modem));
}

void test_SetModemToFullFunctionalityMode(void)
{
    io = getSerialIO(UART_NO, BAUDRATE);
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, io);
    _mockATCommand(io, "AT+CFUN=1\r", "\r\nOK\r\n");

    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);

    TEST_ASSERT_EQUAL(CMD_SUCCESS, ModemController_SetUEFunction(modem, UE_LEVEL_FULL));
}
#endif // TEST
