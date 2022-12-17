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
static ModemController modem = NULL;

void setUp(void)
{
    FakeTimeService_Create(0, 1);
    io = getSerialIO(UART_NO, BAUDRATE);
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, io);

    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    modem = ModemController_Create(serialIO, RESET_PIN);
}

void tearDown(void)
{
    FakeTimeService_Destroy();
    ModemController_Destroy(modem);
}

void test_CreateSucceeds(void)
{
    TEST_ASSERT_NOT_NULL(modem);
    TEST_ASSERT_EQUAL(io, modem->serial);
    TEST_ASSERT_EQUAL(RESET_PIN, modem->resetPin);
}

void _expectAStringInBuffer(SerialIO_t expectedIO, char *expectedString, char endChar)
{
    /* _Ignore cannot be used after _Expect*/
    SerialIO_IsAvailable_IgnoreAndReturn(strlen(expectedString));
    SerialIO_ReadStringUntil_Expect(expectedIO, NULL, endChar, 300);
    SerialIO_ReadStringUntil_IgnoreArg_buffer();
    SerialIO_ReadStringUntil_ReturnArrayThruPtr_buffer(expectedString, strlen(expectedString));
}

void test_RebootUE(void)
{
    SerialIO_Print_Expect(io, "AT+NRB\r");
    _expectAStringInBuffer(io, "\r", '\n');
    _expectAStringInBuffer(io, "REBOOTING\r", '\n');
    SerialIO_IsAvailable_IgnoreAndReturn(0);
    int retval = ModemController_RebootUE(modem);

    TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, retval);
}

void test_ModemIsReadyImmediately(void)
{
    SerialIO_Print_Expect(io, "AT\r");
    _expectAStringInBuffer(io, "\r", '\n');
    _expectAStringInBuffer(io, "OK\r", '\n');
    SerialIO_IsAvailable_IgnoreAndReturn(0);
    TEST_ASSERT_EQUAL(1, ModemController_IsReady(modem));
}

void test_SetModemToFullFunctionalityMode(void)
{
    SerialIO_Print_Expect(io, "AT+CFUN=1\r");
    _expectAStringInBuffer(io, "\r", '\n');
    _expectAStringInBuffer(io, "OK\r", '\n');
    SerialIO_IsAvailable_IgnoreAndReturn(0);
    TEST_ASSERT_EQUAL(CMD_SUCCESS, ModemController_SetUEFunction(modem, UE_LEVEL_FULL));
}

void test_GetModuleIMEI(void)
{
    SerialIO_Print_Expect(io, "AT+CGSN=1\r");
    _expectAStringInBuffer(io, "\r", '\n');
    _expectAStringInBuffer(io, "+CGSN:490154203237511\n", '\n');
    _expectAStringInBuffer(io, "OK\r", '\n');
    SerialIO_IsAvailable_IgnoreAndReturn(0);

    char imei[20];
    TEST_ASSERT_EQUAL(CMD_SUCCESS, ModemController_GetIMEI(modem, imei));
    TEST_ASSERT_EQUAL_STRING("490154203237511", imei);
}

#endif // TEST
