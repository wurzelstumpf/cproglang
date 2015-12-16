#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.7 Functions
 *
 * Exercise 1-15
 *
 *    Rewrite the temperature conversion program of Section 1.2 to use
 *    a function for conversion
 *
 */

int fahr2celcius(int c);

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
        celcius = fahr2celcius(fahr);
        printf("%10d%s%7d\n", fahr,"  ", celcius);
        fahr = fahr + step;
    }
}

int fahr2celcius(int f)
{
    return ((5 * (f -32)) / 9);
}
