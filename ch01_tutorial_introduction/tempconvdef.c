#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.4 Symbolic Constants
 *
 * Example
 *
 *     Use of symbolic constants
 *
 */

#define LOWER 0      /* Lower temperature limit */
#define UPPER 300    /* Upper temperature limit */ 
#define STEP  20     /* Step size */

int main()
{
    int fahr, celcius;
    int lower, upper, step;

    printf("%s  %s\n", "fahrenheit", "celcius");

    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
    {
        celcius = (5 * (fahr - 32) ) / 9;
        printf("%10d  %7d\n", fahr, celcius);
    }
}
