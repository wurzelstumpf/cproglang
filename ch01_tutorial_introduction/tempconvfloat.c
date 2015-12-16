#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.2 Variables and Arithmetic Expressions
 *
 * Example
 *
 *    Modified to use float types
 *
 */

int main()
{
    float fahr, celcius;
    int lower, upper, step;

    lower = 0;      /* Lower temperature limit */
    upper = 300;    /* Upper temperature limit */
    step = 20;      /* Step size */

    fahr = lower;
    
    printf("%s%s%s\n", "fahrenheit", "  ", "celcius");

    while (fahr <= upper)
    {
        celcius = (5.0/9.0) * (fahr - 32);
        printf("%10.0f%s%7.1f\n", fahr,"  ", celcius);
        fahr = fahr + step;
    }
}
