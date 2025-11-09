#include <_main.h>
#include <delay.h>
#include "lcd.h"


extern float time;

void mainInitialize() {
    DWT_Init();
    LCD_Init();
}
