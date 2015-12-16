#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.5 Character Input and Output
 *
 * Exercise 1-6
 *
 *    Verify that the expression getchar() != EOF is 0 or 1.
 *
 */

int main()
{
    int c, notEOF, bool;

    while ((bool = ((c = getchar())) != EOF))
    {
        notEOF = bool;
        putchar(c);
    }

    printf("When boolean expression ((c = getchar()) != EOF) is true  it's value is: %d\n", notEOF);
    printf("When boolean expression ((c = getchar()) != EOF) is false it's value is: %d\n", bool);
}
