#ifndef __LCD_H
#define __LCD_H

#include "main.h"
//#include <lcd_fmc.h>

// set the x coordinate instruction
#define LCD_SET_X 0x2a
// Set the y coordinate instruction
#define LCD_SET_Y 0x2b
// begin to write the GRAM command
#define LCD_WR_RAM_CMD 0x2c

#define MAX_X 320
#define MAX_Y 240

#define delay_ms(ms) HAL_Delay(ms)
#define DBG_Trace(msg)

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef __IO uint32_t vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t vu8;

// LCD important parameter set
typedef struct {
    u16 width;            //LCD width
    u16 height;            //LCD height
    u16 id;                //LCD ID
    u8 dir;            // horizontal screen or vertical screen control: 0, vertical screen; 1, horizontal screen.
} _lcd_dev;

// LCD parameters
extern _lcd_dev lcddev;    // management LCD important parameters

extern u16 POINT_COLOR; // Pen color
extern u16 BACK_COLOR;  // Background color


// Scan direction definition
#define L2R_U2D  0 // From left to right, top to bottom
#define L2R_D2U  1 // from left to right, from bottom to top
#define R2L_U2D  2 // Right to left, top to bottom
#define R2L_D2U  3 // Right to left, bottom to top

#define U2D_L2R  4 // from top to bottom, left to right
#define U2D_R2L  5 // from top to bottom, right to left
#define D2U_L2R  6 // From bottom to top, left to right
#define D2U_R2L  7 // From bottom to top, right to left

#define DFT_SCAN_DIR  L2R_U2D  // The default scan direction

// 16bit RGB colors
#define WHITE        0xFFFF
#define BLACK        0x0000
#define BLUE         0x001F
#define BRED         0XF81F
#define GRED         0XFFE0
#define GBLUE        0X07FF
#define RED          0xF800
#define MAGENTA      0xF81F
#define GREEN        0x07E0
#define CYAN         0x7FFF
#define YELLOW       0xFFE0
#define BROWN        0XBC40
#define BRRED        0XFC07  // reddish brown
#define GRAY         0X8430  // Gray  1000 0100 0011 0000

#define DARKGRAY     0X6208  // Gray  0100 0010 0000 1000
#define DARKBLUE     0X01CF
#define LIGHTBLUE    0X7D7C
#define GRAYBLUE     0X5458

#define LIGHTGREEN   0X841F
#define LIGHTGRAY    0XEF5B


#ifdef __cplusplus
extern "C" {
#endif

void LCD_Init(void);                                                        // Initialize
void LCD_Clear(u16 Color);                                                    // Clear the screen
void LCD_SetCursor(u16 Xpos, u16 Ypos);                                        // Set the cursor
void LCD_DrawPoint(u16 x, u16 y);                                            // Draw the points
void LCD_Fast_DrawPoint(u16 x, u16 y, u16 color);                                // Quickly draw points
void LCD_Draw_Circle(u16 x0, u16 y0, u8 r);                                        // Draw a circle
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);                            // Draw lines
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);                        // Draw the rectangle
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);                        // fill the monochrome
void LCD_drawBMP(u16 sx, u16 sy, u16 ex, u16 ey, const u16 *bmp);                // fill in the specified color
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode);                        // display a character
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size);                        // display a number
void LCD_ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode);                // display numbers
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, const char *p, u8 mode);    // display a string,12/16 font
void LCD_Scan_Dir(u8 dir);                           // Set the screen scan direction
void LCD_Display_Dir(u8 dir);                        // set the screen display direction
void LCD_Set_Window(u16 sx, u16 sy, u16 ex, u16 ey); // Set the window


//----------------- LCD port definition ----------------
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
// For F7 0x60000000 remap to 0xC0000000 for disable ARM Core cache.
#if defined (STM32F765xx) || defined(STM32F746xx)
#define LCD_BASE        ((u32)(0xC0000000 | 0x00007FFFE))
#else
#define LCD_BASE        ((u32)(0x60000000 | 0x00007FFFE))
#endif
#define LCD             ((LCD_TypeDef *) LCD_BASE)

__STATIC_INLINE void LCD_WR_REG(vu16 regval) {
    LCD->LCD_REG = regval;
}

__STATIC_INLINE void LCD_WR_DATA(vu16 data) {
    LCD->LCD_RAM = data;
}

// Read LCD data
// Return Value: Value read
__STATIC_INLINE u16 LCD_RD_DATA(void) {
    return LCD->LCD_RAM;
}

// Write register
//LCD_Reg: Register Address
//LCD_RegValue: data to be written
__STATIC_INLINE void LCD_WriteReg(vu16 LCD_Reg, vu16 LCD_RegValue) {
    LCD_WR_REG(LCD_Reg);         // Write to write register number
    LCD_WR_DATA(LCD_RegValue);   // write data
}

// Read register
//LCD_Reg: Register Address
// Return Value: read data
__STATIC_INLINE u16 LCD_ReadReg(vu16 LCD_Reg) {
    LCD_WR_REG(LCD_Reg);        // Write the register number to be read
    return LCD_RD_DATA();       // Return value read
}


// Start writing GRAM
__STATIC_INLINE void LCD_WriteRAM_Prepare(void) {
    LCD_WR_REG(LCD_WR_RAM_CMD);
}

#ifdef __cplusplus
}
#endif

#endif
