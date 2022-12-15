#include "fake_time_service.h"

#ifdef TEST

static uint32_t theInitTime = 0;
static uint8_t theStep = 0;

void FakeTimeService_Create(uint32_t initTime, uint8_t step)
{
    theInitTime = initTime;
    theStep = step;
}

void FakeTimeService_Destroy(void)
{
    theInitTime = 0;
    theStep = 0;
}

uint32_t getMillis(void)
{
    uint32_t time = theInitTime;
    theInitTime += theStep;
    return time;
}

#endif