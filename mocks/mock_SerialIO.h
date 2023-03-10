/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_SERIALIO_H
#define _MOCK_SERIALIO_H

#include "unity.h"
#include "SerialIO.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_SerialIO_Init(void);
void mock_SerialIO_Destroy(void);
void mock_SerialIO_Verify(void);




#define SerialIO_Create_IgnoreAndReturn(cmock_retval) SerialIO_Create_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void SerialIO_Create_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, SerialIO_t cmock_to_return);
#define SerialIO_Create_StopIgnore() SerialIO_Create_CMockStopIgnore()
void SerialIO_Create_CMockStopIgnore(void);
#define SerialIO_Create_ExpectAndReturn(number, baudrate, cmock_retval) SerialIO_Create_CMockExpectAndReturn(__LINE__, number, baudrate, cmock_retval)
void SerialIO_Create_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, int number, uint32_t baudrate, SerialIO_t cmock_to_return);
typedef SerialIO_t (* CMOCK_SerialIO_Create_CALLBACK)(int number, uint32_t baudrate, int cmock_num_calls);
void SerialIO_Create_AddCallback(CMOCK_SerialIO_Create_CALLBACK Callback);
void SerialIO_Create_Stub(CMOCK_SerialIO_Create_CALLBACK Callback);
#define SerialIO_Create_StubWithCallback SerialIO_Create_Stub
#define SerialIO_Create_IgnoreArg_number() SerialIO_Create_CMockIgnoreArg_number(__LINE__)
void SerialIO_Create_CMockIgnoreArg_number(UNITY_LINE_TYPE cmock_line);
#define SerialIO_Create_IgnoreArg_baudrate() SerialIO_Create_CMockIgnoreArg_baudrate(__LINE__)
void SerialIO_Create_CMockIgnoreArg_baudrate(UNITY_LINE_TYPE cmock_line);
#define SerialIO_Destroy_Ignore() SerialIO_Destroy_CMockIgnore()
void SerialIO_Destroy_CMockIgnore(void);
#define SerialIO_Destroy_StopIgnore() SerialIO_Destroy_CMockStopIgnore()
void SerialIO_Destroy_CMockStopIgnore(void);
#define SerialIO_Destroy_Expect(serial) SerialIO_Destroy_CMockExpect(__LINE__, serial)
void SerialIO_Destroy_CMockExpect(UNITY_LINE_TYPE cmock_line, SerialIO_t serial);
typedef void (* CMOCK_SerialIO_Destroy_CALLBACK)(SerialIO_t serial, int cmock_num_calls);
void SerialIO_Destroy_AddCallback(CMOCK_SerialIO_Destroy_CALLBACK Callback);
void SerialIO_Destroy_Stub(CMOCK_SerialIO_Destroy_CALLBACK Callback);
#define SerialIO_Destroy_StubWithCallback SerialIO_Destroy_Stub
#define SerialIO_Destroy_IgnoreArg_serial() SerialIO_Destroy_CMockIgnoreArg_serial(__LINE__)
void SerialIO_Destroy_CMockIgnoreArg_serial(UNITY_LINE_TYPE cmock_line);
#define SerialIO_Read_IgnoreAndReturn(cmock_retval) SerialIO_Read_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void SerialIO_Read_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, char cmock_to_return);
#define SerialIO_Read_StopIgnore() SerialIO_Read_CMockStopIgnore()
void SerialIO_Read_CMockStopIgnore(void);
#define SerialIO_Read_ExpectAndReturn(serial, cmock_retval) SerialIO_Read_CMockExpectAndReturn(__LINE__, serial, cmock_retval)
void SerialIO_Read_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, SerialIO_t serial, char cmock_to_return);
typedef char (* CMOCK_SerialIO_Read_CALLBACK)(SerialIO_t serial, int cmock_num_calls);
void SerialIO_Read_AddCallback(CMOCK_SerialIO_Read_CALLBACK Callback);
void SerialIO_Read_Stub(CMOCK_SerialIO_Read_CALLBACK Callback);
#define SerialIO_Read_StubWithCallback SerialIO_Read_Stub
#define SerialIO_Read_IgnoreArg_serial() SerialIO_Read_CMockIgnoreArg_serial(__LINE__)
void SerialIO_Read_CMockIgnoreArg_serial(UNITY_LINE_TYPE cmock_line);
#define SerialIO_Write_Ignore() SerialIO_Write_CMockIgnore()
void SerialIO_Write_CMockIgnore(void);
#define SerialIO_Write_StopIgnore() SerialIO_Write_CMockStopIgnore()
void SerialIO_Write_CMockStopIgnore(void);
#define SerialIO_Write_Expect(serial, byte) SerialIO_Write_CMockExpect(__LINE__, serial, byte)
void SerialIO_Write_CMockExpect(UNITY_LINE_TYPE cmock_line, SerialIO_t serial, char byte);
typedef void (* CMOCK_SerialIO_Write_CALLBACK)(SerialIO_t serial, char byte, int cmock_num_calls);
void SerialIO_Write_AddCallback(CMOCK_SerialIO_Write_CALLBACK Callback);
void SerialIO_Write_Stub(CMOCK_SerialIO_Write_CALLBACK Callback);
#define SerialIO_Write_StubWithCallback SerialIO_Write_Stub
#define SerialIO_Write_IgnoreArg_serial() SerialIO_Write_CMockIgnoreArg_serial(__LINE__)
void SerialIO_Write_CMockIgnoreArg_serial(UNITY_LINE_TYPE cmock_line);
#define SerialIO_Write_IgnoreArg_byte() SerialIO_Write_CMockIgnoreArg_byte(__LINE__)
void SerialIO_Write_CMockIgnoreArg_byte(UNITY_LINE_TYPE cmock_line);
#define SerialIO_ReadStringUntil_Ignore() SerialIO_ReadStringUntil_CMockIgnore()
void SerialIO_ReadStringUntil_CMockIgnore(void);
#define SerialIO_ReadStringUntil_StopIgnore() SerialIO_ReadStringUntil_CMockStopIgnore()
void SerialIO_ReadStringUntil_CMockStopIgnore(void);
#define SerialIO_ReadStringUntil_Expect(serial, buffer, end, timeout_ms) SerialIO_ReadStringUntil_CMockExpect(__LINE__, serial, buffer, end, timeout_ms)
void SerialIO_ReadStringUntil_CMockExpect(UNITY_LINE_TYPE cmock_line, SerialIO_t serial, char* buffer, char end, uint32_t timeout_ms);
typedef void (* CMOCK_SerialIO_ReadStringUntil_CALLBACK)(SerialIO_t serial, char* buffer, char end, uint32_t timeout_ms, int cmock_num_calls);
void SerialIO_ReadStringUntil_AddCallback(CMOCK_SerialIO_ReadStringUntil_CALLBACK Callback);
void SerialIO_ReadStringUntil_Stub(CMOCK_SerialIO_ReadStringUntil_CALLBACK Callback);
#define SerialIO_ReadStringUntil_StubWithCallback SerialIO_ReadStringUntil_Stub
#define SerialIO_ReadStringUntil_ReturnThruPtr_buffer(buffer) SerialIO_ReadStringUntil_CMockReturnMemThruPtr_buffer(__LINE__, buffer, sizeof(char))
#define SerialIO_ReadStringUntil_ReturnArrayThruPtr_buffer(buffer, cmock_len) SerialIO_ReadStringUntil_CMockReturnMemThruPtr_buffer(__LINE__, buffer, cmock_len * sizeof(*buffer))
#define SerialIO_ReadStringUntil_ReturnMemThruPtr_buffer(buffer, cmock_size) SerialIO_ReadStringUntil_CMockReturnMemThruPtr_buffer(__LINE__, buffer, cmock_size)
void SerialIO_ReadStringUntil_CMockReturnMemThruPtr_buffer(UNITY_LINE_TYPE cmock_line, char* buffer, size_t cmock_size);
#define SerialIO_ReadStringUntil_IgnoreArg_serial() SerialIO_ReadStringUntil_CMockIgnoreArg_serial(__LINE__)
void SerialIO_ReadStringUntil_CMockIgnoreArg_serial(UNITY_LINE_TYPE cmock_line);
#define SerialIO_ReadStringUntil_IgnoreArg_buffer() SerialIO_ReadStringUntil_CMockIgnoreArg_buffer(__LINE__)
void SerialIO_ReadStringUntil_CMockIgnoreArg_buffer(UNITY_LINE_TYPE cmock_line);
#define SerialIO_ReadStringUntil_IgnoreArg_end() SerialIO_ReadStringUntil_CMockIgnoreArg_end(__LINE__)
void SerialIO_ReadStringUntil_CMockIgnoreArg_end(UNITY_LINE_TYPE cmock_line);
#define SerialIO_ReadStringUntil_IgnoreArg_timeout_ms() SerialIO_ReadStringUntil_CMockIgnoreArg_timeout_ms(__LINE__)
void SerialIO_ReadStringUntil_CMockIgnoreArg_timeout_ms(UNITY_LINE_TYPE cmock_line);
#define SerialIO_Print_Ignore() SerialIO_Print_CMockIgnore()
void SerialIO_Print_CMockIgnore(void);
#define SerialIO_Print_StopIgnore() SerialIO_Print_CMockStopIgnore()
void SerialIO_Print_CMockStopIgnore(void);
#define SerialIO_Print_Expect(serial, text) SerialIO_Print_CMockExpect(__LINE__, serial, text)
void SerialIO_Print_CMockExpect(UNITY_LINE_TYPE cmock_line, SerialIO_t serial, const char* text);
typedef void (* CMOCK_SerialIO_Print_CALLBACK)(SerialIO_t serial, const char* text, int cmock_num_calls);
void SerialIO_Print_AddCallback(CMOCK_SerialIO_Print_CALLBACK Callback);
void SerialIO_Print_Stub(CMOCK_SerialIO_Print_CALLBACK Callback);
#define SerialIO_Print_StubWithCallback SerialIO_Print_Stub
#define SerialIO_Print_IgnoreArg_serial() SerialIO_Print_CMockIgnoreArg_serial(__LINE__)
void SerialIO_Print_CMockIgnoreArg_serial(UNITY_LINE_TYPE cmock_line);
#define SerialIO_Print_IgnoreArg_text() SerialIO_Print_CMockIgnoreArg_text(__LINE__)
void SerialIO_Print_CMockIgnoreArg_text(UNITY_LINE_TYPE cmock_line);
#define SerialIO_IsAvailable_IgnoreAndReturn(cmock_retval) SerialIO_IsAvailable_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void SerialIO_IsAvailable_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, int cmock_to_return);
#define SerialIO_IsAvailable_StopIgnore() SerialIO_IsAvailable_CMockStopIgnore()
void SerialIO_IsAvailable_CMockStopIgnore(void);
#define SerialIO_IsAvailable_ExpectAndReturn(serial, cmock_retval) SerialIO_IsAvailable_CMockExpectAndReturn(__LINE__, serial, cmock_retval)
void SerialIO_IsAvailable_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, SerialIO_t serial, int cmock_to_return);
typedef int (* CMOCK_SerialIO_IsAvailable_CALLBACK)(SerialIO_t serial, int cmock_num_calls);
void SerialIO_IsAvailable_AddCallback(CMOCK_SerialIO_IsAvailable_CALLBACK Callback);
void SerialIO_IsAvailable_Stub(CMOCK_SerialIO_IsAvailable_CALLBACK Callback);
#define SerialIO_IsAvailable_StubWithCallback SerialIO_IsAvailable_Stub
#define SerialIO_IsAvailable_IgnoreArg_serial() SerialIO_IsAvailable_CMockIgnoreArg_serial(__LINE__)
void SerialIO_IsAvailable_CMockIgnoreArg_serial(UNITY_LINE_TYPE cmock_line);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
