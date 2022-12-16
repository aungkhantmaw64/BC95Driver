#ifndef SERIALIO_H
#define SERIALIO_H

#include <stdint.h>

typedef struct SerialIOStruct *SerialIO_t;

SerialIO_t SerialIO_Create(int number, uint32_t baudrate);
void SerialIO_Destroy(SerialIO_t serial);
char SerialIO_Read(SerialIO_t serial);
void SerialIO_Write(SerialIO_t serial, char byte);
void SerialIO_ReadStringUntil(SerialIO_t serial, char *buffer, char end, uint32_t timeout_ms);
void SerialIO_Print(SerialIO_t serial, const char *text);
int SerialIO_IsAvailable(SerialIO_t serial);
#endif // SERIALIO_H
