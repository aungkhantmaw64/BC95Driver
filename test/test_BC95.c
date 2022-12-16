#include "unity.h" // compile/link in Unity test framework
#include "bc95nb.h"
#include "mock_serial_io.h"
#include "fake_time_service.h"

#define DEFAULT_UART_NO 2
#define DEFAULT_BAUDRATE 9600
#define DEFAULT_RESET_PIN 25

struct serialIO
{
    int number;
    uint32_t baudrate;
};

static serialIO_t serial;
static bc95nb_t modem;

void setUp(void)
{
}

void tearDown(void)
{
}

void testBC95_CreateSucceeds_DevicePtrNotNull(void)
{
    struct serialIO expected_serial = {.number = DEFAULT_UART_NO,
                                       .baudrate = DEFAULT_BAUDRATE};
    serialIO_create_ExpectAndReturn(DEFAULT_UART_NO, DEFAULT_BAUDRATE, &expected_serial);
    serial = serialIO_create(DEFAULT_UART_NO, DEFAULT_BAUDRATE);
    modem = bc95nb_create(serial, DEFAULT_RESET_PIN);
    TEST_ASSERT_NOT_NULL(serial);
    TEST_ASSERT_NOT_NULL(modem);
}

void testBC95_CreateFailed_DevicePtrNull(void)
{
    serialIO_create_ExpectAndReturn(DEFAULT_UART_NO, DEFAULT_BAUDRATE, NULL);
    serial = serialIO_create(DEFAULT_UART_NO, DEFAULT_BAUDRATE);
    modem = bc95nb_create(serial, DEFAULT_RESET_PIN);
    TEST_ASSERT_NULL(serial);
    TEST_ASSERT_NULL(modem);
}

// void testBC95_DeviceIsReadyImmediately(void)
// {
//     FakeTimeService_Create(0, 1);

//     struct serialIO expected_serial = {.number = DEFAULT_UART_NO,
//                                        .baudrate = DEFAULT_BAUDRATE};
//     serialIO_create_ExpectAndReturn(DEFAULT_UART_NO,
//                                     DEFAULT_BAUDRATE,
//                                     &expected_serial);
//     serial = serialIO_create(DEFAULT_UART_NO,
//                              DEFAULT_BAUDRATE);
//     modem = bc95nb_create(serial,
//                           DEFAULT_RESET_PIN);

//     TEST_ASSERT_TRUE(bc95nb_isReady(modem));
//     FakeTimeService_Destroy();
// }