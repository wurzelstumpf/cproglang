/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.2 Pointers and Function Arguments
 *
 * Exercise 5-2
 *
 *    Write getfloat, the floating-point analog of getint. What type
 *    does getfloat return as its function value?
 *
 *    hmmm 
 *
 *         getfloat will take a pointer to a double as it's argument
 *         and return a double at the address contained in the pointer
 *
 */
#include <stdio.h>
#include <ctype.h>

int getfloat(double *);
int getch(void);
void ungetch(int);

int main()
{
    double f;
    int rc;
    int w1 = 8;

    while((rc = getfloat(&f)) != EOF && rc != 0)
    {
        printf("getfloat returned: %*i  and retrieved: %g\n", w1, rc, f);
    }
    return 0;
}

/* getfloat - get next floating point value from input into *f
 *
 *   handle strings of digits with decimal points for now:
 *
 *      12.3   -89.0   23435.34301
 *
 */
int getfloat(double *f)
{
    double val, power;
    int c, sign;

    while (isspace(c = getch()))     /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') 
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        c = getch();
        if (!isdigit(c) && c != '.')
        {
            ungetch(c);
            return 0;
        }
    }
    for (val = 0.0; isdigit(c); c = getch())
        val = 10.0 * val + (c - '0');
    if (c == '.')
        c = getch();
    for (power = 1.0; isdigit(c); c = getch())
    {
        val = 10.0 * val + (c - '0');
        power *= 10.0;
    }
    *f = sign * val / power;
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
