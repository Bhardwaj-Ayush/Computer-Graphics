#include <iostream>
#include <graphics.h>

using namespace std;

// Function to calculate Hermite basis functions
float hermiteBasis(int i, float t) {
    if (i == 0)
        return 2 * t * t * t - 3 * t * t + 1;
    else if (i == 1)
        return -2 * t * t * t + 3 * t * t;
    else if (i == 2)
        return t * t * t - 2 * t * t + t;
    else
        return t * t * t - t * t;
}

// Function to draw Hermite curve
void drawHermiteCurve(int x0, int y0, int x1, int y1, int rx0, int ry0, int rx1, int ry1) {
    float x, y;
    for (float t = 0; t <= 1; t += 0.001) {
        x = hermiteBasis(0, t) * x0 + hermiteBasis(1, t) * x1 + hermiteBasis(2, t) * rx0 + hermiteBasis(3, t) * rx1;
        y = hermiteBasis(0, t) * y0 + hermiteBasis(1, t) * y1 + hermiteBasis(2, t) * ry0 + hermiteBasis(3, t) * ry1;
        putpixel(x, y, WHITE);
    }
}

// Function to calculate Bezier basis functions
float bezierBasis(int i, int n, float t) {
    float coeff = 1;
    for (int j = 1; j <= n; j++) {
        if (i == j)
            continue;
        coeff *= (t - j) / (i - j);
    }
    return coeff;
}

// Function to draw Bezier curve
void drawBezierCurve(int x[], int y[], int n) {
    float px, py;
    for (float t = 0; t <= 1; t += 0.001) {
        px = 0;
        py = 0;
        for (int i = 0; i <= n; i++) {
            px += x[i] * bezierBasis(i, n, t);
            py += y[i] * bezierBasis(i, n, t);
        }
        putpixel(px, py, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Hermite curve control points
    int x0 = 50, y0 = 200, x1 = 200, y1 = 50;
    int rx0 = 100, ry0 = 250, rx1 = 250, ry1 = 100;

    // Draw Hermite curve
    drawHermiteCurve(x0, y0, x1, y1, rx0, ry0, rx1, ry1);

    // Bezier curve control points
    int bx[] = {300, 450, 600, 750};
    int by[] = {200, 50, 250, 100};
    int n = sizeof(bx) / sizeof(bx[0]) - 1;

    // Draw Bezier curve
    drawBezierCurve(bx, by, n);

    getch();
    closegraph();
    return 0;
}
