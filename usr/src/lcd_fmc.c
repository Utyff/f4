#include "lcd_fmc.h"
#include "lcd.h"


// Write register function
//regval: register value
/*
void LCD_WR_REG(vu16 regval) {
    LCD->LCD_REG = regval;  // write to write register number
}

// Write LCD data
//data: value to be written
void LCD_WR_DATA(vu16 data) {
    LCD->LCD_RAM = data;
}
//*/
// Read LCD data
// Return Value: Value read
u16 LCD_RD_DATA(void) {
    vu16 ram;            // Prevent Optimization
    ram = LCD->LCD_RAM;
    return ram;
}

// Write register
//LCD_Reg: Register Address
//LCD_RegValue: data to be written
void LCD_WriteReg(vu16 LCD_Reg, vu16 LCD_RegValue) {
    LCD->LCD_REG = LCD_Reg;        // Write to write register number  
    LCD->LCD_RAM = LCD_RegValue;   // write data
}

// Read register
//LCD_Reg: Register Address
// Return Value: read data
u16 LCD_ReadReg(vu16 LCD_Reg) {
    LCD_WR_REG(LCD_Reg);        // Write the register number to be read
    return LCD_RD_DATA();       // Return value read
}

// Start writing GRAM
void LCD_WriteRAM_Prepare(void) {
    LCD->LCD_REG = lcddev.wramcmd;
}
