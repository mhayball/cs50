# Import get_int from CS50
from cs50 import get_int

# Get user input
number = get_int("Number: ")
r_number = number
checksum1 = 0
checksum2 = 0

# Cycle through digits
for i in range(16):
    digit = r_number % 10

    # If even, add to checksum2
    if i % 2 == 0:
        checksum2 += digit

    # Otherwise, process to checksum1
    else:
        checksum1 += (digit * 2 % 10) + (digit * 2 // 10)

    # Store first 4 digits for categorising later
    if i == 12:
        start = r_number

    # Shorter r_number for next cycle
    r_number = r_number // 10

# Add checksum
checksum = checksum1 + checksum2

# Check if checksum final digit = 0, e.g. card is valid
if checksum % 10 == 0:

    # Check card type
    # Visa 13 or 16 digit
    if (start == 4 or start // 1000 == 4):
        print("VISA")

    # MC 16 digit, 51, 52, 53, 54 or 55
    elif (start // 100 == 51 or start // 100 == 52 or start // 100 == 53 or start // 100 == 54 or start // 100 == 55):
        print("MASTERCARD")

    # AMEX 15 digit, 34 or 37
    elif (start // 10 == 34 or start // 10 == 37):
        print("AMEX")

    else:
        print("INVALID")

else:
    print("INVALID")
