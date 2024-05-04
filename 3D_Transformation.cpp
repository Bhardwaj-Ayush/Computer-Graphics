#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

struct Point3D {
    float x, y, z;
};

// Function to perform translation
void translate(Point3D& p, float tx, float ty, float tz) {
    p.x += tx;
    p.y += ty;
    p.z += tz;
}

// Function to perform rotation around X-axis
void rotateX(Point3D& p, float angle) {
    float rad = angle * (M_PI / 180.0); // Convert angle to radians
    float cosA = cos(rad);
    float sinA = sin(rad);

    float newY = p.y * cosA - p.z * sinA;
    float newZ = p.y * sinA + p.z * cosA;

    p.y = newY;
    p.z = newZ;
}

// Function to perform rotation around Y-axis
void rotateY(Point3D& p, float angle) {
    float rad = angle * (M_PI / 180.0); // Convert angle to radians
    float cosA = cos(rad);
    float sinA = sin(rad);

    float newX = p.x * cosA + p.z * sinA;
    float newZ = -p.x * sinA + p.z * cosA;

    p.x = newX;
    p.z = newZ;
}

// Function to perform rotation around Z-axis
void rotateZ(Point3D& p, float angle) {
    float rad = angle * (M_PI / 180.0); // Convert angle to radians
    float cosA = cos(rad);
    float sinA = sin(rad);

    float newX = p.x * cosA - p.y * sinA;
    float newY = p.x * sinA + p.y * cosA;

    p.x = newX;
    p.y = newY;
}

// Function to perform scaling
void scale(Point3D& p, float sx, float sy, float sz) {
    p.x *= sx;
    p.y *= sy;
    p.z *= sz;
}

// Function to apply parallel projection
void parallelProjection(Point3D& p, float d) {
    p.x /= d;
    p.y /= d;
}

// Function to apply perspective projection
void perspectiveProjection(Point3D& p, float d) {
    p.x /= (p.z / d);
    p.y /= (p.z / d);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Define the original 3D object
    Point3D object[] = {
        {-50, -50, -50},
        {50, -50, -50},
        {50, 50, -50},
        {-50, 50, -50},
        {-50, -50, 50},
        {50, -50, 50},
        {50, 50, 50},
        {-50, 50, 50}
    };

    int n = sizeof(object) / sizeof(object[0]);

    // Draw the original 3D object
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        line(object[i].x, object[i].y, object[j].x, object[j].y);
    }

    // Perform transformations
    for (int i = 0; i < n; i++) {
        translate(object[i], 100, 100, 100); // Translation
        rotateX(object[i], 45); // Rotation around X-axis
        rotateY(object[i], 30); // Rotation around Y-axis
        rotateZ(object[i], 60); // Rotation around Z-axis
        scale(object[i], 2, 2, 2); // Scaling
    }

    // Apply parallel projection
    for (int i = 0; i < n; i++) {
        parallelProjection(object[i], 100);
    }

    // Draw the transformed object after parallel projection
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        line(object[i].x, object[i].y, object[j].x, object[j].y);
    }

    // Clear the screen
    cleardevice();

    // Draw the original 3D object
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        line(object[i].x, object[i].y, object[j].x, object[j].y);
    }

    // Apply perspective projection
    for (int i = 0; i < n; i++) {
        perspectiveProjection(object[i], 100);
    }

    // Draw the transformed object after perspective projection
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        line(object[i].x, object[i].y, object[j].x, object[j].y);
    }

    getch();
    closegraph();
    return 0;
}
