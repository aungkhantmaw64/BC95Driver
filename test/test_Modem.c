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
}

void tearDown(void)
{
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
    char *expectedResponse = "\r\nREBOOT\r\n";
    io = getSerialIO(UART_NO, BAUDRATE);
    FakeTimeService_Create(0, 1);
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, io);
    SerialIO_Print_Expect(io, "AT+NRB\r");
    SerialIO_IsAvailable_ExpectAndReturn(io, 7);
    SerialIO_ReadStringUntil_Expect(io, NULL, '\n', 300);
    SerialIO_ReadStringUntil_IgnoreArg_buffer();
    SerialIO_ReadStringUntil_ReturnArrayThruPtr_buffer(expectedResponse, strlen(expectedResponse));

    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);
    int retval = ModemController_RebootUE(modem);
    TEST_ASSERT_EQUAL_STRING(expectedResponse, modem->rxBuffer);
    TEST_ASSERT_EQUAL_INT(0, retval);
    FakeTimeService_Destroy();
}
#endif // TEST
