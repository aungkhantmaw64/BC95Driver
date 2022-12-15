#ifndef D_FAKE_TIME_SERVICE_H
#define D_FAKE_TIME_SERVICE_H

#include "time_service.h"

void FakeTimeService_Create(uint32_t initTime, uint8_t step);
void FakeTimeService_Destroy(void);

#endif