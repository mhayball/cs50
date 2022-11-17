# Import get_int from CS50
from cs50 import get_int

# Initialise height
height = 0

# Get user input
while (height < 1 or height > 8):
    height = get_int("Height: ")

# Print rows of pyramid
for i in range(1, height+1):

    # Print initial spaces/indents
    print(" " * (height - i), end="")

    # Print first #
    for j in range(i):
        print("#", end="")

    # Print middle space
    print("  ", end="")

    # Print final #
    for k in range(i):
        print("#", end="")

    # Print new line
    print("")
