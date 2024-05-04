#include <iostream>
#include <graphics.h>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

vector<Point> clipPolygon(vector<Point> polygon, int x_min, int y_min, int x_max, int y_max) {
    vector<Point> result;
    int n = polygon.size();

    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        int x1 = polygon[i].x, y1 = polygon[i].y;
        int x2 = polygon[next].x, y2 = polygon[next].y;

        // Check if both points are inside the window
        if (x1 >= x_min && x1 <= x_max && y1 >= y_min && y1 <= y_max) {
            result.push_back(polygon[i]);
        }

        // Check for intersection with each clipping edge
        if ((x1 < x_min && x2 >= x_min) || (x1 >= x_min && x2 < x_min)) {
            int new_x = x_min;
            int new_y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
            result.push_back({new_x, new_y});
        }

        if ((x1 > x_max && x2 <= x_max) || (x1 <= x_max && x2 > x_max)) {
            int new_x = x_max;
            int new_y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
            result.push_back({new_x, new_y});
        }

        if ((y1 < y_min && y2 >= y_min) || (y1 >= y_min && y2 < y_min)) {
            int new_x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
            int new_y = y_min;
            result.push_back({new_x, new_y});
        }

        if ((y1 > y_max && y2 <= y_max) || (y1 <= y_max && y2 > y_max)) {
            int new_x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
            int new_y = y_max;
            result.push_back({new_x, new_y});
        }
    }

    return result;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Define the clipping window
    int x_min = 100, y_min = 100, x_max = 300, y_max = 200;
    rectangle(x_min, y_min, x_max, y_max);

    // Define the polygon
    vector<Point> polygon = {{50, 150}, {200, 50}, {250, 250}, {100, 300}};

    // Clip the polygon
    vector<Point> clippedPolygon = clipPolygon(polygon, x_min, y_min, x_max, y_max);

    // Draw the clipped polygon
    setcolor(WHITE);
    for (size_t i = 0; i < clippedPolygon.size(); i++) {
        int next = (i + 1) % clippedPolygon.size();
        line(clippedPolygon[i].x, clippedPolygon[i].y, clippedPolygon[next].x, clippedPolygon[next].y);
    }
    getch();
    closegraph();
    return 0;
}
