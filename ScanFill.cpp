#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

// Function to swap two integers
void swapInt(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to draw a horizontal line
void drawHorizontalLine(int x1, int x2, int y) {
    for (int x = x1; x <= x2; x++) {
        putpixel(x, y, WHITE);
    }
}

// Function to implement the scanline polygon fill algorithm
void scanLineFill(vector<Point>& polygon) {
    int minY = INT_MAX, maxY = INT_MIN;

    // Find minimum and maximum y-coordinates of the polygon
    for (const Point& p : polygon) {
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }

    // Iterate over scanlines
    for (int y = minY; y <= maxY; y++) {
        vector<int> intersections;

        // Find intersections with the scanline
        for (size_t i = 0; i < polygon.size(); i++) {
            int next = (i + 1) % polygon.size();
            int y1 = polygon[i].y, y2 = polygon[next].y;
            int x1 = polygon[i].x, x2 = polygon[next].x;

            if ((y1 <= y && y2 > y) || (y1 > y && y2 <= y)) {
                int x_intersect = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                intersections.push_back(x_intersect);
            }
        }

        // Sort intersections
        sort(intersections.begin(), intersections.end());

        // Fill between pairs of intersections
        for (size_t i = 0; i < intersections.size(); i += 2) {
            drawHorizontalLine(intersections[i], intersections[i + 1], y);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Define the polygon
    vector<Point> polygon = {{100, 100}, {200, 50}, {300, 100}, {200, 200}};

    // Draw the polygon
    setcolor(WHITE);
    for (size_t i = 0; i < polygon.size(); i++) {
        int next = (i + 1) % polygon.size();
        line(polygon[i].x, polygon[i].y, polygon[next].x, polygon[next].y);
    }

    // Fill the polygon
    scanLineFill(polygon);

    getch();
    closegraph();
    return 0;
}
