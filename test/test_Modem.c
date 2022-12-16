#ifdef TEST

#include "unity.h"
#include "Modem.h"
#include "mock_SerialIO.h"

#define UART_NO 2
#define BAUDRATE 9600
#define RESET_PIN 26

struct SerialIOStruct
{
    int number;
    uint32_t baudrate;
};

static struct SerialIOStruct io = {
    .number = UART_NO,
    .baudrate = BAUDRATE,
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_CreateSucceeds(void)
{
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, &io);
    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);
    TEST_ASSERT_NOT_NULL(modem);
    TEST_ASSERT_EQUAL(&io, modem->serial);
    TEST_ASSERT_EQUAL(RESET_PIN, modem->resetPin);
}

void test_CreateFailed_WhenSerialIsNULL(void)
{
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, NULL);
    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    ModemController modem = ModemController_Create(serialIO, RESET_PIN);

    TEST_ASSERT_NULL(modem);
}

#endif // TEST
