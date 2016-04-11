/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.6 Pointer Arrays: Pointers to Pointers
 *
 * Exercise 5-7
 *
 *    Rewrite readlines to store lines in an array supplied by main rather than
 *    calling alloc to maintain storage. How much faster is the program?
 *
 * Notes
 *
 *    The solution to this problem consists of several files.
 *
 *    This is the code from p108 to p110
 */
#include <stdio.h>
#include <string.h>
#include "line.h"
#include "alloc.h"

#define MAX_LINES 200000000

char *lineptr[MAX_LINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* main program
 */
int main()
{
    int nlines;                 /* number of input lines read */

    if ((nlines = readlines(lineptr, MAX_LINES)) >= 0)
    {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input to big to sort\n");
        return 1;
    }
}


/* function: read input lines 
 */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAX_LEN];

    nlines = 0;
    while ((len = getaline(line, MAX_LEN)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* function: write output lines 
 */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* funtion: quick sort 
 */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)          /* do nothing if array contains fewer than two elements */
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* function: swap 
 */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
                
        
            
            
        
