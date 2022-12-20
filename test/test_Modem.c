#ifdef TEST

#include "unity.h"
#include <stdlib.h>
#include "Modem.h"
#include "mock_SerialIO.h"
#include "FakeTimeService.h"
#include "mock_SubStringSearch.h"
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

static ModemController modem = NULL;

static SerialIO_t io = NULL;
static char expected_response[MAX_BUFFER_SIZE];

void setUp(void)
{
    FakeTimeService_Create(0, 1);
    io = getSerialIO(UART_NO, BAUDRATE);
    memset(expected_response, 0, MAX_BUFFER_SIZE);
    SerialIO_Create_ExpectAndReturn(UART_NO, BAUDRATE, io);

    SerialIO_t serialIO = SerialIO_Create(UART_NO, BAUDRATE);
    modem = ModemController_Create(serialIO, RESET_PIN);
}

void tearDown(void)
{
    free(io);
    FakeTimeService_Destroy();
    ModemController_Destroy(modem);
}

static void _ModuleRespondBackWith(char *expectedString)
{
    /* _Ignore cannot be used after _Expect*/
    if (expectedString)
    {
        SerialIO_IsAvailable_IgnoreAndReturn(strlen(expectedString));
        SerialIO_ReadStringUntil_Expect(io, NULL, '\n', 300);
        SerialIO_ReadStringUntil_IgnoreArg_buffer();
        SerialIO_ReadStringUntil_ReturnArrayThruPtr_buffer(expectedString, strlen(expectedString));
        if (strlen(expected_response) == 0)
        {
            strcpy(expected_response, expectedString);
        }
        else
        {
            strcat(expected_response, expectedString);
        }
    }
    else
    {
        SerialIO_IsAvailable_IgnoreAndReturn(0);
    }
}

static void _ATCommandSend(const char *cmd)
{
    SerialIO_Print_Expect(io, cmd);
}

static void _ResponseContainsGivenPhraseAt(const char *phrase, int index)
{
    findSubstringIndex_ExpectAndReturn(expected_response, phrase, index);
}

void test_CreateSucceeds(void)
{
    TEST_ASSERT_NOT_NULL(modem);
    TEST_ASSERT_EQUAL(io, modem->serial);
    TEST_ASSERT_EQUAL(RESET_PIN, modem->resetPin);
}

void test_SendATCmd(void)
{
    _ATCommandSend("AT+CGSN=1\r");
    _ModuleRespondBackWith("\r\n");
    _ModuleRespondBackWith("+CGSN:490154203237511\n");
    _ModuleRespondBackWith("OK\r\n");
    _ModuleRespondBackWith(NULL);

    ModemController_SendATCmd(modem, "AT+CGSN=1\r");

    TEST_ASSERT_EQUAL_STRING(expected_response, modem->responseBuffer);
}

void test_RebootUE(void)
{
    _ATCommandSend("AT+NRB\r");
    _ModuleRespondBackWith("\r\n");
    _ModuleRespondBackWith("REBOOTING\r\n");
    _ModuleRespondBackWith(NULL);
    _ResponseContainsGivenPhraseAt("REBOOT", 2);

    int retval = ModemController_RebootUE(modem);

    TEST_ASSERT_EQUAL_STRING(expected_response, modem->responseBuffer);
    TEST_ASSERT_EQUAL_INT(CMD_SUCCESS, retval);
}

void test_ModemIsReady(void)
{
    _ATCommandSend("AT\r");
    _ModuleRespondBackWith("\r\n");
    _ModuleRespondBackWith("OK\r\n");
    _ModuleRespondBackWith(NULL);
    _ResponseContainsGivenPhraseAt("OK", 2);

    int retval = ModemController_IsReady(modem);

    TEST_ASSERT_EQUAL_STRING(expected_response, modem->responseBuffer);
    TEST_ASSERT_EQUAL(1, retval);
}

void test_SetModemToFullFunctionalityMode(void)
{
    _ATCommandSend("AT+CFUN=1\r");
    _ModuleRespondBackWith("\r\n");
    _ModuleRespondBackWith("OK\r\n");
    _ModuleRespondBackWith(NULL);

    _ResponseContainsGivenPhraseAt("OK", 2);

    int retval = ModemController_SetUEFunction(modem, UE_LEVEL_FULL);

    TEST_ASSERT_EQUAL(CMD_SUCCESS, retval);
}

void test_GetModuleIMEI_Succeeds(void)
{

    _ATCommandSend("AT+CGSN=1\r");
    _ModuleRespondBackWith("\r\n");
    _ModuleRespondBackWith("+CGSN:490154203237511\n");
    _ModuleRespondBackWith("OK\r\n");
    _ModuleRespondBackWith(NULL);

    int okIndex = strlen(expected_response) - strlen("OK\r\n");

    _ResponseContainsGivenPhraseAt("OK", okIndex);
    _ResponseContainsGivenPhraseAt("+CGSN:", 2);

    char imei[20];
    int retval = ModemController_GetIMEI(modem, imei);

    TEST_ASSERT_EQUAL_STRING(expected_response, modem->responseBuffer);
    TEST_ASSERT_EQUAL(CMD_SUCCESS, retval);
    TEST_ASSERT_EQUAL_STRING("490154203237511", imei);
}

void test_ModemControllerIsNotConnectedToNetwork(void)
{
    _ATCommandSend("AT+CGATT?\r");
    _ModuleRespondBackWith("\r\n");
    _ModuleRespondBackWith("+CGATT:0\n");
    _ModuleRespondBackWith("OK\r\n");
    _ModuleRespondBackWith(NULL);

    int okIndex = strlen(expected_response) - strlen("OK\r\n");

    _ResponseContainsGivenPhraseAt("OK", okIndex);
    _ResponseContainsGivenPhraseAt("+CGATT:", 2);

    int retval = ModemController_IsNetworkConnected(modem);

    TEST_ASSERT_FALSE(retval);
}

#endif // TEST
