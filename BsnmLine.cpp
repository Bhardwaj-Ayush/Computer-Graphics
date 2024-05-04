import matplotlib.pyplot as plt

def draw_line(x0, y0, x1, y1):
    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx - dy

    points = []
    while True:
        points.append((x0, y0))

        if x0 == x1 and y0 == y1:
            break
        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x0 += sx
        if e2 < dx:
            err += dx
            y0 += sy

    return points

def plot_line(x0, y0, x1, y1):
    points = draw_line(x0, y0, x1, y1)
    x_values = [point[0] for point in points]
    y_values = [point[1] for point in points]
    plt.plot(x_values, y_values, marker='o')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('Bresenham Line Drawing Algorithm')
    plt.grid()
    plt.show()

# Example usage
x0, y0 = 1, 1
x1, y1 = 8, 5
plot_line(x0, y0, x1, y1)
