#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.10 External Variables and Scope
 *
 * Exercise 1-20
 *
 *    Write a program detab that replaces tabs in the input with the
 *    proper number of blanks to space to the next tab stop. Assume a
 *    fixed set of tab stops, say every n colmns.  Should n be a
 *    variable or a symbolic parameter?
 *
 * Design
 *
 *    Read a character and output it.  If the character is a tab we
 *    need to keep a count of the the number of characters read for
 *    each line and use that value to output an appropriate number of
 *    spaces to the next tabstop.
 *
 *    Convention has it that tabstops are expected to occur every 8
 *    columns. Hence n = 8 for our program and we will write the
 *    initial version using a symbolic constant.  It should actually
 *    be possible to modify this by providing a command line option
 *    and in a future version it would make more sense to use a
 *    variable to represent n.
 *
 *    Once a tab has been encountered the program will use modulo
 *    division by the value of n on the current number of characters
 *    read for the line in order to determine how many spaces need to
 *    be written till the next tabstop.
 *
 */

#define TABSTOP 8    /* number of columns in a tab */

int main()
{
    int c;         /* character */
    int nc;        /* number of characters read in current line */
    int ns;        /* number of spaces to next tabstop */
    int i;         /* for loop index */

    ns = nc = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            ns = (TABSTOP - ( nc % TABSTOP ));
            for (i = 0; i < ns ; ++i)
            {
/***            putchar('^');      for debugging ***/
                putchar(' ');
                ++nc;
            }
        }
        else 
        {
            if (c == '\n')
                nc = 0;
            else
                ++nc;
            putchar(c);
        }
    }
    return 0;
}

