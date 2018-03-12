#ifndef _LCD_FMC_H
#define _LCD_FMC_H

#include "_main.h"

//////////////////////////////////////////////////////////////////////////////////
//----------------- LCD port definition ----------------
//#define	LCD_LED PBout(1)  		// LCD Backlight PB1
// LCD address structure
typedef struct
{
    u16 LCD_REG;
    u16 LCD_RAM;
} LCD_TypeDef;

// Note: LCD /CS is NE1 - Bank 1 of NOR/SRAM Bank 1~4
// for A16 as command line for data command
//#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0001fffE))

// use Bank1.sector1 of NOR / SRAM, address bits HADDR [27,26]=00
// for A18 as command line for data command
// Note that the STM32 will shift to the right one bit when set!
#define LCD_BASE        ((u32)(0x60000000 | 0x00007FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////

void LCD_WR_REG(vu16 regval);
u16 LCD_RD_DATA(void);
void LCD_WR_DATA(vu16 data);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);

#endif //_LCD_FMC_H
