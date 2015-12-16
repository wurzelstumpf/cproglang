#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.2 Variables and Arithmetic Expressions
 *
 * Exercise 1-4
 *
 *    Write a program to print the corresponding Celsius to Fahrenheit table.
 *
 */

int main()
{
    float fahr, celcius;
    int lower, upper, step;

    lower = 0;      /* Lower temperature limit */
    upper = 300;    /* Upper temperature limit */
    step = 20;      /* Step size */

    celcius = lower;
    
    printf("%s%s%s\n", "celcius", "  ", "fahrenheit");

    while (celcius <= upper)
    {
        fahr = ((9.0/5.0) * celcius) + 32.0;
        printf("%7.0f%s%10.1f\n", celcius,"  ", fahr);
        celcius = celcius + step;
    }
}
