#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 3.6 Loops - Do - while
 *
 * Exercise 3-6
 *
 *    Write a version of itoa that accepts three arguments instead of
 *    two. The third argument is a minimum field width; the converted
 *    nuber must be padded with blanks on the left if neccessary to
 *    make it wide enough.
 */

const short max = 100;         /* max length of string arrays */

void itoa3(int n, char s[], int w);
void reverse(char s[]);

int main()
{
    char s[max];
    int n = 0;
    int w = 5;
    short w1 = 16;

    itoa3(n, s, w);
    printf("int: %*i   itoa3: %s\n", w1, n, s);

    n = 21;
    itoa3(n, s, w);
    printf("int: %*i   itoa3: %s\n", w1, n, s);

    n = 5234;
    itoa3(n, s, w);
    printf("int: %*i   itoa3: %s\n", w1, n, s);

    n = 52344;
    itoa3(n, s, w);
    printf("int: %*i   itoa3: %s\n", w1, n, s);

    n = 523440;
    itoa3(n, s, w);
    printf("int: %*i   itoa3: %s\n", w1, n, s);

    n = -2147483647;
    itoa3(n, s, w);
    printf("int: %*i   itoa3: %s\n", w1, n, s);

    /* largest negative int on this system is -2147483648 */
    n = -2147483648;   
    itoa3(n, s, w);
    printf("int: %*i   itoa3: %s\n", w1, n, s);

    return 0;
}

/* Function
 *
 *    Represent integer n as a character string
 *
 *    Designed to handle largest negative int on any two's complement
 *    system
 */
void itoa3(int n, char s[], int w)
{
    int i, sign;

    short carry = 0;          /* don't need to add one to char string */

    if ((sign = n) < 0)       /* record sign */
    {
        if (n == INT_MIN)
        {
            n = INT_MAX;
            ++carry;            /* need to add one to char string */
        }
        else
            n = -n;           /* make n positive */
    }
    i = 0;
    do
    {
        int c = n % 10;
        if (carry)
        {
            if ((c += 1) == 10)
            {
                c = 0;
                ++carry;
            }
            else
                carry = 0;
        }
        s[i++] = c + '0';     /* get next digit */
    }
    while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    while (i < w)           /* pad with minimum required blanks */
        s[i++] = ' ';
    
    s[i] = '\0';
    reverse(s);
}


/* Function
 *
 *   Reverse string s in place
 *
 */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
