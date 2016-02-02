#include <stdio.h>
#include <limits.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.9 Bitwise Operators
 *
 * Exercise 2-8
 *
 *    Write a function rightrot(x,n) that returns the value of the
 *    integer x rotated to the right by n bit positions.
 *
 */

const int max = 100;
const int w1 = 19;

int rightrot(int x, int n);
void printbits(char id[], int u);

int main()
{
    char buf[max];
    int x = 0252;
    int n = 3;
    int r = 0;

    snprintf(buf, max, "%s%i%s", "rightrot(x,", n, ")");
    printbits(buf, x);
    r = rightrot(x, n);
    printbits("r", r);

    x = 0252;
    n = 0;
    snprintf(buf, max, "%s%i%s", "rightrot(x,", n, ")");
    printbits(buf, x);
    r = rightrot(x, n);
    printbits("r", r);

    x = -0252;
    n = 0;
    snprintf(buf, max, "%s%i%s", "rightrot(x,", n, ")");
    printbits(buf, x);
    r = rightrot(x, n);
    printbits("r", r);

    x = -0252;
    n = 1;
    snprintf(buf, max, "%s%i%s", "rightrot(x,", n, ")");
    printbits(buf, x);
    r = rightrot(x, n);
    printbits("r", r);


    x = -0252;
    n = 65;
    snprintf(buf, max, "%s%i%s", "rightrot(x,", n, ")");
    printbits(buf, x);
    r = rightrot(x, n);
    printbits("r", r);
}


/* Function
 *
 *    Return x rotated to the right by n bits
 *    
 * 
 */
int rightrot(int x, int n)
{
    /* examples in comments:
     *    assume 8 bit word size
     *    n = 3  
     *    x = 1010 1010 
     */
    unsigned int ws = sizeof(x) * CHAR_BIT;  /* word size in bits */
    n %= ws;                                 /* if n greater than ws */

    unsigned int mh = ~0 << (ws - n);        /* mask high eg 1110 0000 */

    /*  the following cludge was required because shifting 1000 by
     *  1 to the left resulted in 1111 instead of 0000 as expected
     *  (probably due to rounding up in order to try and represent
     *  a number outside the range of the word size)
     */
    if (n == 0)
	mh = 0;
    
    printbits("mh", mh);

    unsigned int ml = ~(~0 << n);  /* mask low eg 0000 0111 */
    printbits("ml", ml);

    unsigned int sb = x & ml;      /* save bit   eg 0000 0010 */
    printbits("sb", sb);

    sb <<= ws - n;                 /* left shift eg 0100 0000 */
    printbits("ls", sb);

    x >>= n;                       /* right shift by n bits */
    printbits("rs", x);

    x &= ~mh;                      /* nuke bits eg 0001 0101 */
    printbits("nb", x);

    return  x | sb;                /* return   eg 0101 0101 */

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
