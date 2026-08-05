#ifndef __HEARTRATE_H__
#define __HEARTRATE_H__

#include "header.h"

void HeartRate_Init(void);

/* Process one filtered IR sample */
void HeartRate_Process(s16 sample);

/* Return current BPM */
u16 Get_BPM(void);

#endif
