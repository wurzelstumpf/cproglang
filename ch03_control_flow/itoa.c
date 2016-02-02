#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 3.6 Loops - Do - while
 *
 * Exercise 3-4
 *
 *    In a two's complement number representation, our version of itoa
 *    does not handle the largest negative number, that is, the value
 *    of n equal to -(2^wordsize-1). Explain why not. Modify it to
 *    print that value correctly, regardless of the machine on which
 *    it runs.
 *
 *    In a 3 bit wordsize system two's complement can represent
 *    integers from -4 to 3:
 *
 *         3  011
 *         2  010
 *         1  001
 *         0  000
 *        -1  111
 *        -2  110
 *        -3  101
 *        -4  111
 *
 *    The largest negative number represented by a word on this system
 *    is -4 however it's nearest positive equivalent is 3. Thus, when
 *    n is equal to -4 the line in itoa where:
 *
 *        n = -n;           * make n positive *
 *
 *    Will not make n positive 4 since that integer can't be
 *    represented by a word on that system.
 */

const short max = 1000;         /* max length of string arrays */

void itoa(int n, char s[]);
void i2a(int n, char s[]);
void reverse(char s[]);

int main()
{
    char s[max];
    int n = 0;
    short w1 = 16;
    short w2 = 16;

    itoa(n, s);
    printf("int: %*i   itoa: %*s\n", w1, n, w2, s);

    n = 0;
    i2a(n, s);
    printf("int: %*i    i2a: %*s\n", w1, n, w2, s);

    n = -2147483647;
    itoa(n, s);
    printf("int: %*i   itoa: %*s\n", w1, n, w2, s);

    n = -2147483647;
    i2a(n, s);
    printf("int: %*i    i2a: %*s\n", w1, n, w2, s);

    /* largest negative int on this system is -2147483648 */
    n = -2147483648;   
    itoa(n, s);
    printf("int: %*i   itoa: %*s\n", w1, n, w2, s);

    n = -2147483648;   
    i2a(n, s);
    printf("int: %*i    i2a: %*s\n", w1, n, w2, s);

    return 0;
}

/* Function
 *
 *    Represent integer n as a character string
 *
 *    Designed to handle largest negative int on any two's complement
 *    system
 */
void i2a(int n, char s[])
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
    s[i] = '\0';
    reverse(s);
}

/* Function
 *
 *    Represent integer n as a character string
 *
 *    From p64 of book
 */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)   /* record sign */
        n = -n;           /* make n positive */
    i = 0;
    do
    {
        s[i++] = n % 10 + '0';     /* get next digit */
    }
    while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';
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
