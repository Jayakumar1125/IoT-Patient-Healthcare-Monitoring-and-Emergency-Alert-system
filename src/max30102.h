#ifndef __MAX30102_H__
#define __MAX30102_H__

#include "header.h"
#define REG_TEMP_INT      0x1F
#define REG_TEMP_FRAC     0x20
#define REG_TEMP_CONFIG   0x21
#define REG_TEMP_INT      0x1F
#define REG_TEMP_FRAC     0x20
/* I2C Address */
#define MAX30102_ADDR          0x57

/* Registers */
#define REG_INTR_STATUS1       0x00
#define REG_INTR_STATUS2       0x01
#define REG_INTR_ENABLE1       0x02
#define REG_INTR_ENABLE2       0x03

#define REG_FIFO_WR_PTR        0x04
#define REG_OVF_COUNTER        0x05
#define REG_FIFO_RD_PTR        0x06
#define REG_FIFO_DATA          0x07
#define REG_FIFO_CONFIG        0x08

#define REG_MODE_CONFIG        0x09
#define REG_SPO2_CONFIG        0x0A

#define REG_LED1_PA            0x0C
#define REG_LED2_PA            0x0D

#define REG_REV_ID             0xFE
#define REG_PART_ID            0xFF

typedef struct
{
    u32 red;
    u32 ir;
}MAX30102_Data;

/* Driver API */
void MAX30102_Init(void);
void MAX30102_Reset(void);

void MAX30102_WriteReg(u8 reg,u8 value);
u8   MAX30102_ReadReg(u8 reg);

void MAX30102_ReadFIFO(MAX30102_Data *sample);

u8 MAX30102_GetWritePointer(void);
u8 MAX30102_GetReadPointer(void);

void MAX30102_DumpRegisters(void);

#endif
