# -------------- Question 1 --------------
def in_both(word1, word2):
    common = ""
    for letter in word1:
        if letter in word2 and letter not in common:
            common += letter
    return common

print(in_both('ahmed','mohammed'))

# -------------- Question 2 --------------

largest = None
smallest = None

while True:
    num = input("Enter a number: ")
    if num == "done":
        break
    try:
        n = int(num)
        if largest is None or n > largest:
            largest = n
        if smallest is None or n < smallest:
            smallest = n
    except ValueError:
        print("Invalid input")

print("Maximum is", largest)
print("Minimum is", smallest)

# -------------- Question 3 --------------

import math

def volume_cube(side):
    return side ** 3

s = 2
print("Volume of cube with side", s, "is", volume_cube(s), ".")

import random

def random_dice():
    die1 = random.randrange(1, 7)
    die2 = random.randrange(1, 7)
    return die1 + die2

print("Sum of two random dice, rolled once:", random_dice())
print("Sum of two random dice, rolled again:", random_dice())
print("Sum of two random dice, rolled again:", random_dice())

import math

def volume_sphere(radius):
    return 4.0/3.0 * math.pi * (radius ** 3)

r = 2
print("Volume of sphere of radius", r, "is", volume_sphere(r), ".")

def area_triangle(base, height):
    return 0.5 * base * height

b = 5
h = 2 + 2
print("Area of triangle with base", b, "and height", h, "is", area_triangle(b, h), ".")

def is_mary(x):
    if x == "Mary":
        print("Found Mary!")
    else:
        print("No Mary.")

is_mary("Mary")
is_mary("Fred")




# -------------- Question 4 --------------

def harmonic_sum(n):
    if n < 2:
        return 0
    else:
        return 1 / (n - 1) + harmonic_sum(n - 1)

print('harmonic sum is:',harmonic_sum(100))

# -------------- Question 5 --------------

def common_members(list1, list2):
    return list(set(list1) & set(list2))

print(common_members([1, 3, 5, 7, 9], [2,3,5,6,9, 12]))

# -------------- Question 6 --------------

dict1 = {'a': 1, 'b': 2}
dict2 = {'c': 3, 'd': 4}

merged_dict = dict1.copy()
merged_dict.update(dict2)

print(merged_dict)

# -------------- Question 7 --------------

scores = [2, 3, 6, 6, 5]

unique_scores = list(set(scores))
unique_scores.sort()

if len(unique_scores) > 1:
    print(unique_scores[-2])
else:
    print(unique_scores[0])


# -------------- Question 8 --------------

import math

class Circle:
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return math.pi * self.radius ** 2

    def perimeter(self):
        return 2 * math.pi * self.radius

circ = Circle(3)

area = circ.area()
print(area)

perm = circ.perimeter()
print(perm)