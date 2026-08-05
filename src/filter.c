#include "filter.h"

#define FILTER_SIZE 8

static u32 dc_estimate = 0;

static s16 ma_buffer[FILTER_SIZE];

static u8 index = 0;



void Filter_Init(void)
{
    u8 i;

    dc_estimate = 0;
    index = 0;

    for(i=0;i<FILTER_SIZE;i++)
        ma_buffer[i]=0;
}



/* Simple DC removal filter */
s16 DC_Remove(u32 input)
{
    dc_estimate = (dc_estimate * 15 + input) / 16;

    return (s16)((s32)input - (s32)dc_estimate);
}



/* 8-point moving average */
s16 Moving_Average(s16 input)
{
    s32 sum = 0;
    u8 i;

    ma_buffer[index] = input;

    index++;

    if(index >= FILTER_SIZE)
        index = 0;

    for(i=0;i<FILTER_SIZE;i++)
        sum += ma_buffer[i];

    return (s16)(sum / FILTER_SIZE);
}