#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.5 Character Input and Output
 *
 * Exercise 1-9
 *
 *    Write a program to copy it's input to it's output, replacing
 *    each string of one or more blanks by a single blank.
 *
 */

#define TRUE  1
#define FALSE 0

int main()
{
    int c, inblank;

    c = inblank = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            if (inblank == FALSE)
            {
                inblank = TRUE;
                putchar(c);
            }
        }
        else
        {
            inblank = FALSE;
            putchar(c);
        }
    }
}
