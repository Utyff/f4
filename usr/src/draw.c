#include "draw.h"
#include "graph.h"


void drawFrame() {
    u16 x, y, step = 32;

    LCD_Clear(BLACK);
    POINT_COLOR = GRAY;  // Drawing pen color
    BACK_COLOR = BLACK;

    for (y = step; y < MAX_Y; y += step) {
        if (y == 128) POINT_COLOR = GRAY;  // Drawing pen color
        else POINT_COLOR = DARKGRAY;
        LCD_Fill(0, y, MAX_X, y, POINT_COLOR);
    }

    for (x = step; x < MAX_X; x += step) {
        if (x == 160) POINT_COLOR = GRAY;  // Drawing pen color
        else POINT_COLOR = DARKGRAY;
        LCD_Fill(x, 0, x, MAX_Y, POINT_COLOR);
    }
}

void drawScreen() {
    drawFrame();
   // drawGraph();
}
