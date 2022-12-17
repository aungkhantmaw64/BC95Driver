#ifndef SERIALIO_H
#define SERIALIO_H

#include <stdint.h>

/**
 * @brief SerialIOStruct shall be defined in implementation
 * based on the device API
 *
 *
 */
typedef struct SerialIOStruct *SerialIO_t;

/**
 * @brief Allocate a UART peripheral and returns a pointer to the peripheral
 *
 * @param number Uart peripheral number
 * @param baudrate Uart baudrate (9600, 115200, etc.)
 * @return SerialIO_t if the allocation is valid
 *         NULL if the allocated UART device is not free
 */
SerialIO_t SerialIO_Create(int number, uint32_t baudrate);
/**
 * @brief Free the UART device and its memory allocation
 *
 * @param serial The pointer to the UART device struct
 */
void SerialIO_Destroy(SerialIO_t serial);
/**
 * @brief Read a single byte from the rx buffer
 *
 * @param serial The pointer to the UART device struct
 * @return char if rx buffer is not empty
 */
char SerialIO_Read(SerialIO_t serial);
/**
 * @brief Write a single byte to the tx buffer
 *
 * @param serial The pointer to the UART device struct
 * @param byte Character byte to be written
 */
void SerialIO_Write(SerialIO_t serial, char byte);
/**
 * @brief Read bytes from the rxbuffer until the given character
 *        is seen
 * @param serial The pointer to the UART device struct
 * @param buffer Buffer where read bytes will be stored
 * @param end End character where the read process is stopped
 * @param timeout_ms Timeout to wait for the given character
 */
void SerialIO_ReadStringUntil(SerialIO_t serial, char *buffer, char end, uint32_t timeout_ms);
/**
 * @brief Write a string lateral to the tx buffer
 *
 * @param serial The pointer to the UART device struct
 * @param text String lateral to be written
 */
void SerialIO_Print(SerialIO_t serial, const char *text);
/**
 * @brief Fetch the number of bytes in the rx buffer
 *
 * @param serial The pointer to the UART device struct
 * @return int Number of bytes in the rx buffer
 */
int SerialIO_IsAvailable(SerialIO_t serial);

#endif // SERIALIO_H
