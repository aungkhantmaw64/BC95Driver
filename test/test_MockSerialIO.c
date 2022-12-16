#ifdef TEST

#include "unity.h"

#include "mock_SerialIO.h"
#include <string.h>
#include <memory.h>

#include <stdlib.h>

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

void test_ReadStringUntil()
{
    char *expectedResponse = "\r\nREBOOT\r\n";
    char buffer[50];
    memset(buffer, 0, 50);
    io = getSerialIO(UART_NO, BAUDRATE);

    SerialIO_ReadStringUntil_Expect(io, NULL, '\n', 300);
    SerialIO_ReadStringUntil_IgnoreArg_buffer();
    SerialIO_ReadStringUntil_ReturnArrayThruPtr_buffer(expectedResponse, strlen(expectedResponse));

    SerialIO_ReadStringUntil(io, buffer, '\n', 300);
    TEST_ASSERT_EQUAL_STRING(expectedResponse, buffer);
}

#endif // TEST
