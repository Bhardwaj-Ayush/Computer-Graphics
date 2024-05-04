#include <iostream>
#include <graphics.h>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

const int x_max = 400;
const int y_max = 300;
const int x_min = 100;
const int y_min = 100;

int computeCode(int x, int y) {
    int code = INSIDE;
    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;
    return code;
}

void cohenSutherland(int x0, int y0, int x1, int y1) {
    int code1 = computeCode(x0, y0);
    int code2 = computeCode(x1, y1);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int x, y;
            int codeOut = (code1 != 0) ? code1 : code2;
            if (codeOut & TOP) {
                x = x0 + (x1 - x0) * (y_max - y0) / (y1 - y0);
                y = y_max;
            } else if (codeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (y_min - y0) / (y1 - y0);
                y = y_min;
            } else if (codeOut & RIGHT) {
                y = y0 + (y1 - y0) * (x_max - x0) / (x1 - x0);
                x = x_max;
            } else if (codeOut & LEFT) {
                y = y0 + (y1 - y0) * (x_min - x0) / (x1 - x0);
                x = x_min;
            }

            if (codeOut == code1) {
                x0 = x;
                y0 = y;
                code1 = computeCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                code2 = computeCode(x1, y1);
            }
        }
    }

    if (accept) {
        setcolor(YELLOW);
        line(x0, y0, x1, y1);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);

    int x0 = 50, y0 = 50, x1 = 450, y1 = 350;
    setcolor(WHITE);
    line(x0, y0, x1, y1);

    cohenSutherland(x0, y0, x1, y1);

    getch();
    closegraph();
    return 0;
}
