#include "heartrate.h"

#define SAMPLE_RATE     50      /* 50 samples/second */
#define THRESHOLD       10

static u16 bpm = 0;

static s16 prev = 0;
static u8 state = 0;

static u32 sample_count = 0;
static u32 last_peak = 0;

void HeartRate_Init(void)
{
    bpm = 0;
    prev = 0;
    state = 0;
    sample_count = 0;
    last_peak = 0;
}

void HeartRate_Process(s16 sample)
{
    sample_count++;

    /* Rising edge */
    if((state == 0) &&
       (sample > THRESHOLD) &&
       (prev <= THRESHOLD))
    {
        if(last_peak != 0)
        {
            u32 diff = sample_count - last_peak;

            /* Accept only 40-180 BPM */
            if((diff > 16) && (diff < 75))
            {
                bpm = (60 * SAMPLE_RATE) / diff;
            }
        }

        last_peak = sample_count;
        state = 1;
    }

    /* Falling edge */
    if(sample < 0)
    {
        state = 0;
    }

    prev = sample;
}

u16 Get_BPM(void)
{
    return bpm;
}