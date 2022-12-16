#include "bc95nb.h"
#include "time_service.h"
#include <string.h>
#include "string_search.h"

struct bc95nb
{
    int resetPin;
    serialIO_t serial;
};

static struct bc95nb modem_struct;
static char *rxBuffer;

bc95nb_t bc95nb_create(serialIO_t serial, int resetPin)
{
    bc95nb_t modem = NULL;
    if (serial)
    {
        modem_struct.resetPin = resetPin;
        modem_struct.serial = serial;
        modem = &modem_struct;
    }
    return modem;
}

void bc95nb_destroy(bc95nb_t modem)
{
    modem_struct.resetPin = -1;
    serialIO_destroy(modem_struct.serial);
    modem = NULL;
}

int bc95nb_isReady(bc95nb_t modem)
{

    return 0;
}