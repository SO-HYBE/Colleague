# -------------- Question 1 --------------

import math

def calculate_triangle_area(x0, y0, x1, y1, x2, y2):
    side_a = math.sqrt((x1 - x0)**2 + (y1 - y0)**2)
    side_b = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    side_c = math.sqrt((x0 - x2)**2 + (y0 - y2)**2)

    s = (side_a + side_b + side_c) / 2
    area = math.sqrt(s * (s - side_a) * (s - side_b) * (s - side_c))

    return area

x0, y0 = 0, 0
x1, y1 = 4, 0
x2, y2 = 0, 3

triangle_area = calculate_triangle_area(x0, y0, x1, y1, x2, y2)

print(f"The area of the triangle with vertices ({x0},{y0}), ({x1},{y1}), and ({x2},{y2}) is: {triangle_area:.2f}")


# -------------- Question 2 --------------

# using for loops
for i in range(99, 0, -2):
    print(i)

# using while loops
i = 99
while i > 0:
    print(i)
    i -= 2