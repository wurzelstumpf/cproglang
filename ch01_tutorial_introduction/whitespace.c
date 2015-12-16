#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.5 Character Input and Output
 *
 * Exercise 1-8
 *
 *    Write a program to count blanks, tabs and newlines.
 *
 */

int main()
{
    int c, nb, nt, nl, no;

    nb = nt = nl = no= 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            ++nb;
        else if (c == '\t')
            ++nt;
        else if (c == '\n')
            ++nl;
        else
            ++no;
    }

    printf("Number of blanks: %d, tabs: %d, newlines: %d, other: %d\n", nb, nt, nl, no);
}
