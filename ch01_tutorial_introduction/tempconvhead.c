#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.3 Variables and Arithmetic Expressions
 *
 * Exercise 1-3
 *
 *    Modify the temperature conversion program to print a heading
 *    above the table.
 *
 */

int main()
{
    int fahr, celcius;
    int lower, upper, step;

    lower = 0;      /* Lower temperature limit */
    upper = 300;    /* Upper temperature limit */
    step = 20;      /* Step size */

    fahr = lower;
    
    printf("%s   %s\n", "fahrenheit",  "celcius");

    while (fahr <= upper)
    {
        celcius = (5 * (fahr - 32) ) / 9;
        printf("%10d%s%7d\n", fahr,"  ", celcius);
        fahr = fahr + step;
    }
}
