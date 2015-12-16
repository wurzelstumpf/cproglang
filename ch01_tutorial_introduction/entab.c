#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.10 External Variables and Scope
 *
 * Exercise 1-21
 *
 *    Write a program entab that replaces strings of blanks by the
 *    minimum number of tabs and blanks to achieve the same spacing.
 *    Use the same tabstop as for detab.  When either a tab or a
 *    single blank would suffice to reach a tab stop, which should be
 *    given preference?
 *
 * Design
 *
 *    Read a character and output it.  If the character is a space
 *    we need to keep a count of the the number of consecutive spaces
 *    and see if we reach a tab stop.  If so we can replace the spaces
 *    with a tab.
 *
 *    Convention has it that tabstops are expected to occur every 8
 *    columns. Hence n = 8 for our program and we will write the
 *    initial version using a symbolic constant.  It should actually
 *    be possible to modify this by providing a command line option
 *    and in a future version it would make more sense to use a
 *    variable to represent n.
 *
 *    As we are adding tabs a tab should be used instead of a single
 *    space to reach a tab stop.  
 *
 */

#define TABSTOP 8     /* number of character columns in a tab */
#define IN_SPACE  0   /* state - reading sequence of space characters */
#define OUT_SPACE 1   /* state - not reading sequence of space chars */

int columns_to_next_tabstop(int cc);

int main()
{
    int c;         /* character */
    int nc;        /* number of character columns read in current line */
    int ns;        /* number of consecutive spaces */
    int pt;        /* column pointer */
    int state;     /* state - whether reading space characters or not */

    nc = ns = pt = 0;

    state = OUT_SPACE;

    while ((c = getchar()) != EOF)
    {
        ++nc;
        
        if (c == ' ')      /* is a space character */
        {
            ++ns;
            state = IN_SPACE;
        }
        else if (c == '\t')
        {
            /* if tab char then update number of chars columns to next tabstop
             */
            nc += columns_to_next_tabstop(nc);
            putchar(c);
        }
        else if (c == '\n')
        {
            /* if end of line reset char column counter
             */
            nc = 0;
            putchar(c);
        }
        else
        {
            /* did we just read one of more spaces?
             */
             if (state == IN_SPACE)
             {
                 state = OUT_SPACE;

                 /* replace spaces by appropriate number of tabs
                  */
                 pt = nc - ns;
                 while ((pt + columns_to_next_tabstop(pt)) < nc)
                 {
                     putchar('\t');

                     /* Note: add one here to advance to next char
                      *       and avoid a subtle problem
                      */
                     pt += (columns_to_next_tabstop(pt) + 1);
                 }
                 /* pad with spaces to bring to current char column
                  */
                 while(pt < nc)
                 {
                     putchar('_');
                     ++pt;
                 }
                 ns = 0;   /* end consecutive space counting */
             }
             putchar(c);
        }
    }
    return 0;
}


/* return number of character columns to the next tab stop
 *
 * arguments:    cc - current column on line
 */
int columns_to_next_tabstop(int cc)
{
    int remainder = cc % TABSTOP;
    
    if (remainder == 0)
        return 0;
    else
        return (TABSTOP - remainder);
}
