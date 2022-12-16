#ifndef FAKETIMESERVICE_H
#define FAKETIMERSERVICE_H

#include "TimeService.h"

void FakeTimeService_Create(uint32_t initTime, uint8_t step);
void FakeTimeService_Destroy(void);

#endif