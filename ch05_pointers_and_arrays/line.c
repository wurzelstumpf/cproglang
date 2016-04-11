/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * File containing functions that manipulate lines
 *
 */
#include <stdio.h>
#include "line.h"

/* Function
 *
 *    get line into s, return length
 *
 *    line is terminated by either '\n''\0' or just '\0' for line > lim
 *
 *    note: named function getaline to avoid conflict with getline
 *    library function
 *
 */
int getaline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
