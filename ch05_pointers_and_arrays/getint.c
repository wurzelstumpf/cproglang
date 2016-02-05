/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.2 Pointers and Function Arguments
 *
 * Exercise 5-1
 *
 *    As written, getint treats a + or - not followed by a digit as a
 *    valid representation of zero. Fix it to push such a character
 *    back on the input.
 *
 */
#include <stdio.h>
#include <ctype.h>

int getint(int *);
int getch(void);
void ungetch(int);

int main()
{
    int n;
    int rc;
    int w1 = 8;

    while((rc = getint(&n)) != EOF && rc != 0)
    {
        printf("getint returned: %*i  and retrieved: %i\n", w1, rc, n);
    }
    return 0;
}

/* getint - get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))     /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        c = getch();
        if (!isdigit(c))
        {
            ungetch(c);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return(c);
}

/* Character input handlers
 */
#define BUFSIZE 100

char buf[BUFSIZE];        /* buffer for ungetch */
int bufp = 0;             /* next free position in buf */

/* getch - get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch - push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: to many characters\n");
    else
        buf[bufp++] = c;
}
