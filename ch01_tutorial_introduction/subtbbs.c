#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.5 Character Input and Output
 *
 * Exercise 1-10
 *
 *    Write a program to copy it's input to it's output, replacing
 *    each tab by \t, each backspace by \b, and each backslash by \\.
 *     This makes tabs and backspaces visible in an unambiguous way.
 *
 */

int main()
{
    int c;

    c = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            putchar('\\');
            putchar('t');
        }
        else if ( c == '\b')
        {
            putchar('\\');
            putchar('b');
        }
        else if ( c == '\\')
        {
            putchar('\\');
            putchar('\\');
        }
        else
        {
            putchar(c);
        }
    }
}
