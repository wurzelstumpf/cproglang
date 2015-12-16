#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.5 Character Input and Output
 *
 * Exercise 1.12
 *
 *     Write a program that prints its input one word per line
 *
 */

#define  IN  1    /* inside a word */
#define  OUT 0    /* outside a word */

int main()
{
    int c, nl, nw ,nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
        ++nc;                /* count characters */
        if (c == '\n')       /* count newline characters */
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (state == IN)   /* were we in a word? */
            {
                putchar('\n'); /* one line for each word read */
            }
            state = OUT;
        }
        else
        {
            if (state == OUT)
            {
                state = IN;
                ++nw;
            }
            putchar(c);
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}
