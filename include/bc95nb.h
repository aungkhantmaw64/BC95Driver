#ifndef D_BC95_H
#define D_BC95_H

#include <stdint.h>
#include "serial_io.h"
#include "string_search.h"

typedef struct bc95nb *bc95nb_t;

bc95nb_t bc95nb_create(serialIO_t serial, int resetPin);
void bc95nb_destroy(bc95nb_t modem);
int bc95nb_isReady(bc95nb_t modem);
#endif