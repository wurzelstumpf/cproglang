#include <stdio.h>
#include <limits.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.9 Bitwise Operators
 *
 * Exercise 2-7
 *
 *    Write a function invert(x,p,n) that returns x with the n bits
 *    that begin at position p inverted (ie 1 changed to 0 and vice
 *    versa), leaving the other bits unchanged.
 *
 */

const int max = 100;
const int w1 = 19;
const int w2 = 32;

unsigned int invert(unsigned int x, int p, int n);
void printbits(unsigned int u);

int main()
{
	char buf[max];
	unsigned int x = 0252;
	int p = 4;
	int n = 3;

	snprintf(buf, max, "%s%d%s%d%s", "invert(x,", p, ",", n, ")");
	printf("%*s --> \n", w1, buf);
	printf("%*s --> %*o\n", w1, "x", w2, x);
	printf("%*s --> ", w1, "x");
	printbits(x);
	invert(x, p, n);

	x = 0252;
	p = 0;
	n = 1;
	snprintf(buf, max, "%s%d%s%d%s", "invert(x,", p, ",", n, ")");
	printf("%*s --> \n", w1, buf);
	printf("%*s --> %*o\n", w1, "x", w2, x);
	printf("%*s --> ", w1, "x");
	printbits(x);
	invert(x, p, n);

	x = 031234567252;
	p = 31;
	n = 1;
	snprintf(buf, max, "%s%d%s%d%s", "invert(x,", p, ",", n, ")");
	printf("%*s --> \n", w1, buf);
	printf("%*s --> %*o\n", w1, "x", w2, x);
	printf("%*s --> ", w1, "x");
	printbits(x);
	invert(x, p, n);
}


/* Function
 *
 *    Return x with the n bits that begin at position p inverted
 *    
 * 
 */
unsigned int invert(unsigned int x, int p, int n)
{
	/* examples in comments show low order 8 bits
	 *    p = 4
	 *    n = 3  
	 *    x = 1010 1010 
	 */
	unsigned int mh = ~0 << (p + 1);           /* mask high eg 1110 0000 */

        /*  the following cludge was required because shifting 1000 by
	 *  1 to the left resulted in 1111 instead of 0000 as expected
	 *  (probably due to rounding up in order to try and represent
	 *  a number outside the range of the word size)
	 */
	if (p == ((sizeof(x) * CHAR_BIT) - 1))
		mh = 0;
	printf("%*s --> ", w1, "mh");
	printbits(mh);

	unsigned int ml = ~(~0 << (p + 1 - n));    /* mask low eg 0000 0011 */
	printf("%*s --> ", w1, "ml");
	printbits(ml);

	unsigned int ma = mh | ml;                 /* mask and eg 1110 0011 */
	printf("%*s --> ", w1, "ma");
	printbits(ma);

	unsigned int x0 = x & ma;                  /* x0 is    eg 1010 0010 */
	printf("%*s --> ", w1, "x0");
	printbits(x0);

	unsigned int xa = x & ~ma;                 /* xa is    eg 0000 1000 */
	printf("%*s --> ", w1, "xa");
	printbits(xa);

	unsigned int xc = ~xa & ~ma;               /* xc is    eg 0001 0100 */
	printf("%*s --> ", w1, "xc");
	printbits(xc);

	unsigned int re = xc | x0;                 /* return   eg 1011 0110 */
	printf("%*s --> ", w1, "re");
	printbits(re);
	printf("%*s --> %*o\n", w1, "re", w2, re);

	return re;
}

/* Function
 *
 *    Print out the bit pattern
 */
void printbits(unsigned int u)
{
	int i;
	unsigned short w = sizeof(u) * CHAR_BIT;
	for (i = (w - 1); i >= 0 ; i--)
		printf("%d", u & (01 << i) ? 1 : 0);
	printf("\n");
}
