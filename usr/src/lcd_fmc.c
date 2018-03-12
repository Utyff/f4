#include "lcd_fmc.h"
#include "lcd.h"
#include "delay.h"


// Write register function
//regval: register value
void LCD_WR_REG(vu16 regval) {
    regval = regval;        // Use -O2 optimization, you must insert delay
    LCD->LCD_REG = regval;  // write to write register number
    delay_us(1);
}

// Write LCD data
//data: value to be written
void LCD_WR_DATA(vu16 data) {
    data = data;            // Use -O2 optimization, you must insert delay
    LCD->LCD_RAM = data;
    delay_us(1);
}

// Read LCD data
// Return Value: Value read
u16 LCD_RD_DATA(void) {
    vu16 ram;            // Prevent Optimization
//    delay_us(5);
    ram = LCD->LCD_RAM;
    return ram;
}

// Write register
//LCD_Reg: Register Address
//LCD_RegValue: data to be written
void LCD_WriteReg(vu16 LCD_Reg, vu16 LCD_RegValue) {
    LCD->LCD_REG = LCD_Reg;        // Write to write register number  
//    delay_us(1);
    LCD->LCD_RAM = LCD_RegValue;   // write data
//    delay_us(5);
}

// Read register
//LCD_Reg: Register Address
// Return Value: read data
u16 LCD_ReadReg(vu16 LCD_Reg) {
    LCD_WR_REG(LCD_Reg);        // Write the register number to be read
//    delay_us(5);
    return LCD_RD_DATA();       // Return value read
}

// Start writing GRAM
void LCD_WriteRAM_Prepare(void) {
    LCD->LCD_REG = lcddev.wramcmd;
//    delay_us(1);
}

//LCD write GRAM
//RGB_Code: color values
void LCD_WriteRAM(u16 RGB_Code) {
    LCD->LCD_RAM = RGB_Code;  // write sixteen GRAM
    delay_us(15);
}
