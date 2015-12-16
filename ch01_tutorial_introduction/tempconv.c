#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.2 Variables and Arithmetic Expressions
 *
 * Example
 *
 *     Print a table of fahrenheit to celcuis conversions
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
    
    while (fahr <= upper)
    {
        celcius = (5 * (fahr - 32) ) / 9;
        printf("%d\t%d\n", fahr, celcius);
        fahr = fahr + step;
    }
}
