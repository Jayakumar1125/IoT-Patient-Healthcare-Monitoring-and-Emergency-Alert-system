#ifndef __SPO2_H__
#define __SPO2_H__

#include "header.h"



#define SPO2_SAMPLE_SIZE 100



void SpO2_Init(void);



void SpO2_Process(u32 red,
                  u32 ir);



u8 Get_SpO2(void);



#endif

