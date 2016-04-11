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
 *    This is an implementation of the storage stack from p101 and p102
 */
#include <stdio.h>
#include "alloc.h"

static char alloc_buf[ALLOC_SZ];  /* storage for alloc */
static char *alloc_ptr = alloc_buf; /* next free position */

char *alloc(int n)              /* return pointer to space for n characters */
{
    if (alloc_buf + ALLOC_SZ - alloc_ptr >= n)
    {
        alloc_ptr += n;
        return alloc_ptr - n;   /* old ptr */
    }
    else
    {
        return NULL;            /* not enough space */
    }
}

void afree(char *p)
{
    if (p >= alloc_buf && p < alloc_buf + ALLOC_SZ)
        alloc_ptr = p;
}
            
        
            
            
        
