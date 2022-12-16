#ifndef D_SERIAL_IO_H
#define D_SERIAL_IO_H

#include <stdint.h>
#include <stddef.h>

typedef struct serialIO *serialIO_t;

serialIO_t serialIO_create(int number, uint32_t baudrate);
void serialIO_write(serialIO_t serial, char byte);
void serialIO_print(serialIO_t serial, const char *str);
int serialIO_isAvailable(serialIO_t serial);
char serialIO_read(serialIO_t serial);
void serialIO_readStringUntil(serialIO_t serial, char end, char *buffer);
void serialIO_destroy(serialIO_t serial);

#endif