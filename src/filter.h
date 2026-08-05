#ifndef __FILTER_H__
#define __FILTER_H__

#include "header.h"

void Filter_Init(void);

s16 DC_Remove(u32 input);

s16 Moving_Average(s16 input);

#endif
