#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.10 External Variables and Scope
 *
 * Exercise 1-22
 *
 *    Write a program to "fold" long input lines into two or more
 *    shorter lines after the last non-blank character that occurs
 *    before the n-th column of input. Make sure your program does
 *    something intelligent with very long lines, and if there are no
 *    blanks or tabs before the specified column.
 *
 * Note
 *
 *    More needs to be done on this program but the basics have been
 *    fleshed out.
 *
 * Design
 *
 *    The desired line length should be specified as program option
 *    but for our purposes it is set using a symbolic constant.
 *
 *    What to do with null characters (^@) in a line?
 *
 *      They can be skipped, replaced with a printable character or
 *      used to terminate the line like a new line. Here they will be
 *      left in the line and printed out but, then it is not possible
 *      to use any string functions like printf("%s", buffer).
 *
 *    How to handle horizontal tabs (^I) in a line?
 *
 *      They may be either counted as a single character column or
 *      some number of character columns up until the next tabstop.
 *      An option should be provided on the command line for either.
 *
 *    How to handle backspaces (^H) in a line?
 *    How to handle deletes (^?) in a line?
 *    How to handle carriage returns (^M) in a line?
 *
 */

#define   FOLD    15        /* desired length of line */

#define   TRUE     1
#define   FALSE    0

char buffer[FOLD];   /* hold a line plus a newline */

void print_line(int nc);     /* print out the line in the buffer */

int is_white(int c);    /* is white space */

int main()
{
    int c;                 /* character */
    int len;               /* current line length */
    int tos;               /* index to last tab or space */

    tos = -1;              /* no tabs or spaces read so far */
    len = 0;               /* set index to first character */

    while ((c = getchar()) != EOF)
    {
        if (c == '\n' && len < FOLD)   /* end of line and fits in buffer */
        {
            print_line(len);
            len = 0;
            tos = -1;
        }
        else if (len == FOLD)       /* end of line buffer full */
        {
            print_line(FOLD);
            buffer[0] = c;          /* add char to next line */
            len = 1;                /* set for next char */
            if (is_white(c))
                tos = 0;
            else
                tos = -1;
        }
        else
        {
            buffer[len] = c;
            if (is_white(c))
                tos = len;
            ++len;
        }
    }
}

/* function
 *
 *     print out the line in buffer with terminating newline
 */
void print_line(int nc)
{
    int i;
    for (i = 0; i < nc; ++i)
        printf("%c", buffer[i]);
    printf("%c", '\n');
    fflush(stdout);
}

/* function
 *
 *    is the character a tab or a space
 */
int is_white(int c)
{
    if (c == ' ' || c == '\t')
        return TRUE;
    else
        return FALSE;
}

