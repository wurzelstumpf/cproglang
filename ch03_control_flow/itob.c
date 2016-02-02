#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 3.6 Loops - Do - while
 *
 * Exercise 3-5
 *
 *    Write the function itob(n,s,b) that converts the integer n into
 *    a base b character representation in the string s. In
 *    particular, itob(n,s,16) formats n as a hexadecimal integer in
 *    s.
 *
 */

const short max = 1000;         /* max length of string arrays */

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    char s[max];
    int n = 0;
    int b = 10;
    short w1 = 16;
    short w2 = 3;
    short w3 = 16;

    /* Base 10 
     */
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = 2147483647;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = -2147483647;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    /* largest negative int on this system is -2147483648 */
    n = -2147483648;   
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);


    /* Base 8
     */
    n = 0;
    b = 8;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = 10;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = -32;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);
    
    n = 39284304;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);
    
    n = 2147483647;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = -2147483647;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    /* largest negative int on this system is -2147483648 */
    n = -2147483648;   
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    /* Base 16
     */
    n = 0;
    b = 16;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = 10;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = -32;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);
    
    n = 39284304;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);
    
    n = 2147483647;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    n = -2147483647;
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    /* largest negative int on this system is -2147483648 */
    n = -2147483648;   
    itob(n, s, b);
    printf("int: %*i  base: %*i   itob: %*s\n", w1, n, w2, b, w3, s);

    return 0;
}

/* Function
 *
 *    Represent integer n as a character string of the given base b
 *
 *    Designed to handle largest negative int on any two's complement
 *    system
 */
void itob(int n, char s[], int b)
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
        int c = n % b;
        if (carry)
        {
            if ((c += 1) == b)
            {
                c = 0;
                ++carry;
            }
            else
                carry = 0;
        }
        if ( c >= 0 && c <= 9)
            s[i++] = c + '0';        /* get next digit */
        else
            s[i++] = (c - 10) + 'a';  /* this works up to base 36 (0-9a-z) */
    }
    while ((n /= b) > 0);

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
