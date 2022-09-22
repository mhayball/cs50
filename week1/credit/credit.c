#include <cs50.h>
#include <stdio.h>

long power(int base, int exponent);
int check_sum(long number);

int main(void)
{
    // get CC number
    long number;
    number = get_long("Number: ");

    // checksum
    int i, checksum, checksum1, checksum2, digit, start;
    long r_number;
    r_number = number;
    checksum1 = 0;
    checksum2 = 0;

    // loop through digits
    for (i = 0; i < 16; i++)
    {
        // calculate digit
        digit = r_number % 10;
        //printf("%i - %i - %li\n", i, digit, r_number);

        if (i % 2 == 0)
        {
            //printf("even\n");
            checksum2 += digit;
        }
        else
        {
            //printf("odd\n");
            checksum1 += (digit * 2 % 10) + (digit * 2 / 10);
        }

        // store first 4 digits for categorising later
        if (i == 12)
        {
            start = r_number;
        }

        // shorten number for next cycle
        r_number = r_number / 10;

    }

    // add checksum
    checksum = checksum1 + checksum2;

    // check if checksum final digit = 0, e.g. card is valid
    if (checksum % 10 == 0)
    {
        //printf("VALID\n");

        // check card type
        // visa 13 or 16 digit, 4
        if (start == 4 || start / 1000 == 4)
        {
            printf("VISA\n");
        }
        // mc 16 digit, 51, 52, 53, 54, 55
        else if (start / 100 == 51 || start / 100 == 52 || start / 100 == 53 || start / 100 == 54 || start / 100 == 55)
        {
            printf("MASTERCARD\n");
        }
        // amex 15 digit, 34, 37
        else if (start / 10 == 34 || start / 10 == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
