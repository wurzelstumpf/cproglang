#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.3 The for Statement
 *
 * Exercise 1-5
 *
 *    Modify the temperature conversion program to print the table in
 *    reverse order, that is, from 300 degrees to 0.
 *
 */

int main()
{
    int fahr, celcius;
    int lower, upper, step;

    lower = 0;      /* Lower temperature limit */
    upper = 300;    /* Upper temperature limit */
    step = 20;      /* Step size */

    printf("%s  %s\n", "fahrenheit", "celcius");

    for (fahr = upper; fahr >= lower; fahr = fahr - step)
    {
        celcius = (5 * (fahr - 32) ) / 9;
        printf("%10d  %7d\n", fahr, celcius);
    }
}
