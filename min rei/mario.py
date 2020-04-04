from cs50 import get_int

# Obtain height within range(1, 9)
while True:
    height = get_int("Height: ")
    if height in range(1, 9):
        break

# Genereate Pyramid
for i in range(1, height + 1):
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
