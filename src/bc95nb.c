#include "bc95nb.h"

struct bc95nb
{
    int resetPin;
    serialIO_t serial;
};

static serialIO_t serial = NULL;

static struct bc95nb modem_struct;

static bc95nb_t modem = NULL;

bc95nb_t bc95nb_create(serialIO_t serial, int resetPin)
{
    if (serial)
    {
        modem_struct.resetPin = resetPin;
        modem_struct.serial = serial;
        modem = &modem_struct;
        return modem;
    }
    return NULL;
}

void bc95nb_destroy(bc95nb_t modem)
{
    modem_struct.resetPin = -1;
    modem_struct.serial = NULL;
    modem = NULL;
}