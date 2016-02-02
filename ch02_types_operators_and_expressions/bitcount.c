#include <stdio.h>
#include <limits.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.10 Assignment Operators and Expressions
 *
 * Exercise 2-9
 *
 *    In a two's complement number system, x &= (x-1) deletes the
 *    rightmost 1-bit in x. Explain why. Use this observation to write
 *    a faster version of bitcount.
 *
 *    In a two's complement number system negative numbers are
 *    represented by the complement of their positive counter part
 *    with the addition of 1.  Thus a word of 3 bits can represent the
 *    following range of integers:
 *
 *        3 ... 011
 *        2 ... 010
 *        1 ... 001
 *        0 ... 000
 *       -1 ... 111
 *       -2 ... 110
 *       -3 ... 101
 *       -4 ... 100
 *
 *
 *    Now the expression x &= (x-1) is equivalent to x = x & (x-1). If
 *    we look at the following cases:
 *
 *        x          01101
 *        1          00001
 *        x-1        01100
 *        x & (x-1)  01100
 *
 *        x          01110
 *        1          00001
 *        x-1        01101
 *        x & (x-1)  01100
 *
 *        we note that in the final expression the rightmost 1-bit of
 *        x and all following bits are zero'd out while the bits to
 *        the left of it are preserved.
 *
 *    Using this characteristic of binary arithmetic we can count
 *    1-bits without have to use the shift operator.
 *
 *
 */

const int w1 = 0;

int bitcount(int x);
void printbits(char id[], int u);

int main()
{
	int x = 11;
	int r = 0;

	r = bitcount(x);
        printbits("x", x);
        printf("bitcount(x = %i) returns: %i\n", x, r);

        x = 6345;
        r = 0;
	r = bitcount(x);
        printbits("x", x);
        printf("bitcount(x = %i) returns: %i\n", x, r);

        x = -6345;
        r = 0;
	r = bitcount(x);
        printbits("x", x);
        printf("bitcount(x = %i) returns: %i\n", x, r);

        x = -1;
        r = 0;
	r = bitcount(x);
        printbits("x", x);
        printf("bitcount(x = %i) returns: %i\n", x, r);

        x = 0;
        r = 0;
	r = bitcount(x);
        printbits("x", x);
        printf("bitcount(x = %i) returns: %i\n", x, r);

        x = 1234567;
        r = 0;
	r = bitcount(x);
        printbits("x", x);
        printf("bitcount(x = %i) returns: %i\n", x, r);
}

/* Function
 *
 *    Count the number of 1-bits in x
 */
int bitcount(int x)
{
    /* original version on page 50
     * 
     * newer and quicker? version .... 
     * given x &= (x-1) sets right most 1-bit in x to zero
     *
     * hmmmm 
     *
     *   while x != 0
     *       i = 01;
     *       test rightmost untested bit for 1-ness  x & i
     *       nuke it .... x &= (x-1)
     *       i *= 2;
     *   
     */
    
    int nb = 0;                     /* number of 1-bits counted */
    unsigned int m = 01;            /* & mask for testing bits */

    while (x != 0)
    {
        /* printf("========================================\n"); */
        /* printbits("x", x); */
        /* printbits("m", m); */

        if (x & m)
        {
            ++nb;

            /* printf("after & test nb is %i\n", nb); */
        
            x &= (x - 1);  /* nuke tested 1-bit, no need to do so if 0-bit */

            /* printf("after nuke tested bit\n"); */
            /* printbits("x", x); */

        }

        m *= 2;                   /* move mask to next rightmost bit */

        /* printf("after increment mask\n"); */
        /* printbits("m", m); */
        /* printf("------------------------------\n"); */
    }

    return nb;
}

/* Function
 *
 *    Print out the bit pattern
 */
void printbits(char id[], int u)
{
    int i;
    unsigned short w = sizeof(u) * CHAR_BIT;
    printf("%*s --> ", w1, id);
    for (i = (w - 1); i >= 0 ; i--)
	printf("%d", u & (01 << i) ? 1 : 0);
    printf("\n");
}
