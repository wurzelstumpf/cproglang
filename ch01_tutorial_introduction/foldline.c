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
 * Notes
 *
 *    Can compare output to GNU core utility:
 *    
 *      fold -w 8 -s < some.txt
 *
 *    The variable len is always set to the index value of the next
 *    free character in the array buffer. Once len is the same size as
 *    the fold column the current contents of the buffer are printed
 *    and the new character, if it is not a newline, is added to the
 *    beginning of the buffer and the len variable is adjusted
 *    appropriately.
 *
 *  Design
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
 * Todo
 *
 *    Sanity checking FOLD = 0 or FOLD < 0 or FOLD = 1
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

#define   FOLD    8        /* desired length of line */

/* These booleans would be better handled with enum
 */
#define   TRUE     1
#define   FALSE    0

char buffer[FOLD];   /* hold a line plus a newline */

int  find_first(int from);    /* find first tab or space from right of buffer */
void shift_left(int start);   /* shift contents of buffer from start to beginning */
void print_line(int nc);      /* print out the line in the buffer */
int is_white(int c);          /* is white space */

int main()
{
    int c;                 /* character */
    int len;               /* current line length */
    int tos;               /* index to last tab or space */

    tos = -1;              /* no tabs or spaces read so far */
    len = 0;               /* set index to first character */

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')              /* end of line */
        {
            print_line(len);
            len = 0;
            tos = -1;
        }
        else if (len == FOLD)        /* buffer full and next char not a newline */
        {
            if (tos < 0)             /* no tabs or spaces in line */
            {
                print_line(FOLD);
                buffer[0] = c;                 /* add char to next line */
                len = 1;                       /* set for next char */
                tos = (is_white(c)) ? 0 : -1;  /* is it a white space char */
            }
            else
            {
                print_line(tos);
                shift_left(tos + 1);   /* from first non white space */
                len = FOLD - tos -1;
                buffer[len] = c;
                tos = find_first(len);
                ++len;
            }
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
 *     find first tab or space from end of buffer
 */
int find_first(int from)
{
    int i;
    for (i = from; i >= 0; --i)
        if (is_white(buffer[i]))
            return i;
    return -1;
}

/* function
 *
 *     shift the buffer contents from start to the left
 */
void shift_left(int start)
{
    int i, j;
    for (i = start, j = 0; i < FOLD; ++i, ++j)
        buffer[j] = buffer[i];
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
    return (c == ' ' || c == '\t') ? TRUE : FALSE;
}

