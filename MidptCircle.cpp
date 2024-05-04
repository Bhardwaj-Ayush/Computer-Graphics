#include <iostream>
#include <graphics.h>

void draw_circle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        if (p < 0)
            p += 2 * x + 3;
        else {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Example usage
    int xc = 200, yc = 200, r = 100;
    draw_circle(xc, yc, r);

    getch();
    closegraph();
    return 0;
}
