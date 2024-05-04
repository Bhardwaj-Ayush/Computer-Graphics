#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <cmath>

using namespace std;

struct Point {
    float x, y, w; // Homogeneous coordinates
};

// Function to perform translation
void translate(Point& p, float tx, float ty) {
    float mat[3][3] = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}
    };

    float newX = p.x * mat[0][0] + p.y * mat[0][1] + p.w * mat[0][2];
    float newY = p.x * mat[1][0] + p.y * mat[1][1] + p.w * mat[1][2];
    p.w = p.x * mat[2][0] + p.y * mat[2][1] + p.w * mat[2][2];
    p.x = newX;
    p.y = newY;
}

// Function to perform rotation
void rotate(Point& p, float angle) {
    float rad = angle * (M_PI / 180.0); // Convert angle to radians
    float cosA = cos(rad);
    float sinA = sin(rad);

    float mat[3][3] = {
        {cosA, -sinA, 0},
        {sinA, cosA, 0},
        {0, 0, 1}
    };

    float newX = p.x * mat[0][0] + p.y * mat[0][1] + p.w * mat[0][2];
    float newY = p.x * mat[1][0] + p.y * mat[1][1] + p.w * mat[1][2];
    p.w = p.x * mat[2][0] + p.y * mat[2][1] + p.w * mat[2][2];
    p.x = newX;
    p.y = newY;
}

// Function to perform scaling
void scale(Point& p, float sx, float sy) {
    float mat[3][3] = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };

    float newX = p.x * mat[0][0] + p.y * mat[0][1] + p.w * mat[0][2];
    float newY = p.x * mat[1][0] + p.y * mat[1][1] + p.w * mat[1][2];
    p.w = p.x * mat[2][0] + p.y * mat[2][1] + p.w * mat[2][2];
    p.x = newX;
    p.y = newY;
}

// Function to perform shearing
void shear(Point& p, float shx, float shy) {
    float mat[3][3] = {
        {1, shx, 0},
        {shy, 1, 0},
        {0, 0, 1}
    };

    float newX = p.x * mat[0][0] + p.y * mat[0][1] + p.w * mat[0][2];
    float newY = p.x * mat[1][0] + p.y * mat[1][1] + p.w * mat[1][2];
    p.w = p.x * mat[2][0] + p.y * mat[2][1] + p.w * mat[2][2];
    p.x = newX;
    p.y = newY;
}

// Function to draw the object
void drawObject(const vector<Point>& object) {
    int n = object.size();
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        line(object[i].x / object[i].w, object[i].y / object[i].w, object[next].x / object[next].w, object[next].y / object[next].w);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Define the original object
    vector<Point> object = {{100, 100, 1}, {200, 100, 1}, {200, 200, 1}, {100, 200, 1}};

    // Draw the original object
    drawObject(object);

    // Translation
    for (Point& p : object) {
        translate(p, 100, 100);
    }
    drawObject(object);

    // Rotation
    for (Point& p : object) {
        rotate(p, 45);
    }
    drawObject(object);

    // Scaling
    for (Point& p : object) {
        scale(p, 1.5, 1.5);
    }
    drawObject(object);

    // Shearing
    for (Point& p : object) {
        shear(p, 0.5, 0);
    }
    drawObject(object);

    getch();
    closegraph();
    return 0;
}
