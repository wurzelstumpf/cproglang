/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4.10 Recursion
 *
 * Exercise 4-12
 *
 *    Adapt the ideas of printd to write a recursive version of itoa;
 *    that is, convert an integer into a string by calling a recursive
 *    routine.
 *
 *
 */
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

const short max = 1000;         /* max length of string arrays */

void itoa_r(int n, char s[]);
void i2a(int n, char s[]);
void reverse(char s[]);

int main()
{
    char s[max];
    int n = 0;
    short w1 = 16;
    short w2 = 16;

    n = 0;
    itoa_r(n, s);
    printf("int: %*i   itoa_r: %*s\n", w1, n, w2, s);
    i2a(n, s);
    printf("int: %*i      i2a: %*s\n", w1, n, w2, s);

    n = 3;
    itoa_r(n, s);
    printf("int: %*i   itoa_r: %*s\n", w1, n, w2, s);
    i2a(n, s);
    printf("int: %*i      i2a: %*s\n", w1, n, w2, s);

    n = -12345;
    itoa_r(n, s);
    printf("int: %*i   itoa_r: %*s\n", w1, n, w2, s);
    i2a(n, s);
    printf("int: %*i      i2a: %*s\n", w1, n, w2, s);

    n = -2147483647;
    itoa_r(n, s);
    printf("int: %*i   itoa_r: %*s\n", w1, n, w2, s);
    i2a(n, s);
    printf("int: %*i      i2a: %*s\n", w1, n, w2, s);

    /* largest negative int on this system is -2147483648 */
    n = -2147483648;
    itoa_r(n, s);
    printf("int: %*i   itoa_r: %*s\n", w1, n, w2, s);
    i2a(n, s);
    printf("int: %*i      i2a: %*s\n", w1, n, w2, s);

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

/* itoa_r - represent integer n as a character string in s -- using recursion ;-)
 */
void itoa_r(int n, char s[])
{
    /*  need static ints to record position in s
     *  and to work out when to reset i to 0
     */
    static int i = 0;
    static int j = 0;
    static int w = 20;
    static int sign = 0;

    /* printf("%*s i = %*i j = %*i\n", w, "itoa_r before while", 8, i, 8, j); */

    if (n < 0)
    {
        sign = '-';
        n = -n;          /* this won't work for largest negative number */
    }
    
    if ((n / 10) > 0)
    {
        w += 2;
        j++;
        itoa_r(n / 10, s);
        w -= 2;
    }

    /* printf("%*s i = %*i j = %*i\n", w, "itoa_r  after while", 8, i, 8, j); */

    if (i == 0 && sign == '-')
    {
        s[i++] = sign;
    }
    s[i++] = n % 10 + '0';     /* set digit */
    s[i] = '\0';               /* terminate string */
    if (j == 0)
    {
        i = 0;
    }
    else
    {
        j--;
    }

    /* printf("%*s i = %*i j = %*i\n", w, "itoa_r  after  else", 8, i, 8, j); */

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
