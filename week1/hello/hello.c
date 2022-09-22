#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get username
    string username = get_string("What is your name: ");

    //print username
    printf("hello, %s\n", username);
}
