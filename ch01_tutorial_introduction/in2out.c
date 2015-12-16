#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.5 Character Input and Output
 *
 * Example
 *
 *    File copying
 *
 */

int main()
{
    int c;

    c = getchar();
    while (c != EOF)
    {
        putchar(c);
        c = getchar();
    }
}
