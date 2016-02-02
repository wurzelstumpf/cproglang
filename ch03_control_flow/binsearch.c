#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 3.3 Else-If
 *
 * Exercise 3-1
 *
 *    Our binary search makes two tests inside the loop, when one
 *    would suffice (at the price of more tests outside). Write a
 *    version with only one test inside the loop and measure the
 *    difference in run-time.
 *
 * Notes
 *
 *    Increased array size to 2 million and ran the program using the
 *    time command first with binsearch1 commented out:
 *
 *          # time ./binsearch
 *          binsearch returned: 999992 for term -8
 *          binsearch returned: 1000007 for term 7
 *          binsearch returned: 999999 for term -1
 *          binsearch returned: 1000000 for term 0
 *          binsearch returned: 1000002 for term 2
 *          binsearch returned: 1000008 for term 8
 *          binsearch returned: 999991 for term -9
 *          
 *          real 0m0.015s user 0m0.009s sys 0m0.006s
 *
 *    and then with binsearch commented out:
 *
 *          # time ./binsearch
 *          binsearch1 returned: 999992 for term -8
 *          binsearch1 returned: 1000007 for term 7
 *          binsearch1 returned: 999999 for term -1
 *          binsearch1 returned: 1000000 for term 0
 *          binsearch1 returned: 1000002 for term 2
 *          binsearch1 returned: 1000008 for term 8
 *          binsearch1 returned: 999991 for term -9
 *          
 *          real 0m0.015s user 0m0.008s sys 0m0.006s
 *    
 *    so no real difference discernable on this computer
 */

#define ARRAY_SIZE 16       /* tested with this value */

int binsearch(int x, int v[], int n);
int binsearch1(int x, int v[], int n);

int main()
{
    int array[ARRAY_SIZE];
    int w1 = 20;
    int r;
    long term;

    /* populate array with elements */
    unsigned int i;
    int j = - (ARRAY_SIZE / 2);
    for (i = 0; i < ARRAY_SIZE; i++, j++)
        array[i] = j;

    term = -8;
    r = binsearch(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch returned:",  r, "for term", term);
    r = binsearch1(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch1 returned:",  r, "for term", term);

    term = 7;
    r = binsearch(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch returned:",  r, "for term", term);
    r = binsearch1(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch1 returned:",  r, "for term", term);

    term = -1;
    r = binsearch(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch returned:",  r, "for term", term);
    r = binsearch1(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch1 returned:",  r, "for term", term);

    term = 0;
    r = binsearch(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch returned:",  r, "for term", term);
    r = binsearch1(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch1 returned:",  r, "for term", term);

    term = 2;
    r = binsearch(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch returned:",  r, "for term", term);
    r = binsearch1(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch1 returned:",  r, "for term", term);

    term = 8;
    r = binsearch(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch returned:",  r, "for term", term);
    r = binsearch1(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch1 returned:",  r, "for term", term);

    term = -9;
    r = binsearch(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch returned:",  r, "for term", term);
    r = binsearch1(term, array, ARRAY_SIZE);
    printf("%*s %i %s %li\n", w1, "binsearch1 returned:",  r, "for term", term);

}

/* Function
 *
 *  binary search with one test inside the loop 
 *
 */
int binsearch1(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2;
    while (low <= high && x != v[mid])
    {
        if (x < v[mid])
            high =  mid - 1;
        else                   /* x > v[mid] */
            low = mid + 1;
        mid = (low + high) / 2;
    }
    return (x == v[mid]) ? mid: -1;
}

/* Function
 *
 *  binary search with two tests inside the loop 
 *  (from p58)
 *
 */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high =  mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;  /* found match */
    }
    return -1;
}
