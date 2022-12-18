#ifndef TIMESERVICE_H
#define TIMESERVICE_H

#include <stdint.h>

/**
 * @brief Get the elasped time since the system boot-up
 *        in terms of milliseconds
 *
 * @return uint32_t
 */
uint32_t getMillis(void);

#endif // TIMESERVICE_H
