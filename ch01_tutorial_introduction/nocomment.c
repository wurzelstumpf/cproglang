/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.10 External Variables and Scope
 *
 * Exercise 1-23
 *
 *    Write a program to remove all comments from a C program. Don't
 *    forget to handle quoted strings and character constants
 *    properly. C comments do not nest.
 *
 *  Design
 *
 *    Read a char at a time using getchar().  Once the sequence
 *    'slash'* has been read ignore all subsequent characters until
 *    the sequence 'asterisk''/' has been read.
 *
 */
#include <stdio.h>

/* These booleans would be better handled with enum
 */
#define   TRUE     1
#define   FALSE    0

int main()
{
    int c;                 /* current char */
    int p = -1;            /* previous char */
    int comment = FALSE;
    int string = FALSE;

    while ((c = getchar()) != EOF)
    {
        if (p == '/' && c == '*' && !string)
        {
            comment = TRUE;
        }
        else if (p == '*' && c == '/' && !string)
        {
            comment = FALSE;
        }
        else
        {
            char s[] = "////****///**\"**//**/*";    /* for testing */

           if (c == '"')
           {
               if (p != '\'')          /* if not a character constant */
               {
                   if (string && p == '\\')       /* escaped? */
                       ;
                   else
                       string = (string) ? FALSE : TRUE;   /* start or end of string */
               }
           }

           if ((c == '/' || c == '*'))
           {
               if (string && !comment)
                   putchar(c);
           }
           else
           {
               if (!comment)
                   putchar(c);
           }
   
           p = c;
        }
    }
    return 0;
}


