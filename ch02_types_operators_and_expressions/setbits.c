#include <stdio.h>
#include <limits.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.9 Bitwise Operators
 *
 * Exercise 2-6
 *
 *    Write a function setbits(x,p,n,y) that returns x with the n bits
 *    that begin at position p set to the rightmost n bits of y,
 *    leaving the other bits unchanged.
 *
 */

const int max = 100;
const int w1 = 19;
const int w2 = 32;

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
void printbits(unsigned int u);

int main()
{
	char buf[max];
	unsigned int x = 0252;
	unsigned int y = 0326;
	int p = 4;
	int n = 3;

	snprintf(buf, max, "%s%d%s%d%s", "setbits(x,", p, ",", n, ",y)");
	printf("%*s --> \n", w1, buf);
	printf("%*s --> %*o\n", w1, "x", w2, x);
	printf("%*s --> ", w1, "x");
	printbits(x);
	printf("%*s --> %*o\n", w1, "y", w2, y);
	printf("%*s --> ", w1, "y");
	printbits(y);
	setbits(x, p, n, y);

	x = 0252;
	y = 0327;
	p = 0;
	n = 1;
	snprintf(buf, max, "%s%d%s%d%s", "setbits(x,", p, ",", n, ",y)");
	printf("%*s --> \n", w1, buf);
	printf("%*s --> %*o\n", w1, "x", w2, x);
	printf("%*s --> ", w1, "x");
	printbits(x);
	printf("%*s --> %*o\n", w1, "y", w2, y);
	printf("%*s --> ", w1, "y");
	printbits(y);
	setbits(x, p, n, y);

	x = 031234567252;
	y = 0321;
	p = 31;
	n = 1;
	snprintf(buf, max, "%s%d%s%d%s", "setbits(x,", p, ",", n, ",y)");
	printf("%*s --> \n", w1, buf);
	printf("%*s --> %*o\n", w1, "x", w2, x);
	printf("%*s --> ", w1, "x");
	printbits(x);
	printf("%*s --> %*o\n", w1, "y", w2, y);
	printf("%*s --> ", w1, "y");
	printbits(y);
	setbits(x, p, n, y);
}


/* Function
 *
 *    Return x with the n bits that begin at position p set to the
 *    rightmost n bits of y, leaving the other bits unchanged.
 *    
 * 
 */
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
	/* examples in comments show low order 8 bits
	 *    p = 4
	 *    n = 3  
	 *    x = 1010 1010 and  y = 1101 0110 
	 */
	unsigned int mh = ~0 << (p + 1);           /* mask high eg 1110 0000 */

        /*  the following cludge was required because shifting 1000 by 1 to the
	 *  left resulted in 1111 instead of 0000 as expected
	 */
	if (p == ((sizeof(x) * CHAR_BIT) - 1))
		mh = 0;
	printf("%*s --> ", w1, "mh");
	printbits(mh);

	unsigned int ml = ~(~0 << (p + 1 - n));    /* mask low  eg 0000 0011 */
	printf("%*s --> ", w1, "ml");
	printbits(ml);

	unsigned int ma = mh | ml;                 /* mask and  eg 1110 0011 */
	printf("%*s --> ", w1, "ma");
	printbits(ma);

	unsigned int x0 = x & ma;                  /* x0 is     eg 1010 0010 */
	printf("%*s --> ", w1, "x0");
	printbits(x0);

	unsigned int my = ~(~0 << n);              /* mask y    eg 0000 0111 */
	printf("%*s --> ", w1, "my");
	printbits(my);

	unsigned int ny = y & my;                  /* new  y    eg 0000 0110 */
	printf("%*s --> ", w1, "ny");
	printbits(ny);

	unsigned int sy = ny << (p + 1 - n);       /* shifted y eg 0001 1000 */
	printf("%*s --> ", w1, "sy");
	printbits(sy);

	unsigned int re = x0 | sy;                 /* return    eg 1011 1010 */
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
