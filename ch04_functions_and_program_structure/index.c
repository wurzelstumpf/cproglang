/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4.1 Basics of Functions
 *
 * Exercise 4-1
 *
 *    Write the function strrindex(s,t), which returns the position of
 *    the rightmost occurrence of t in s, or -1 if there is none.
 *
 * Notes
 *
 *    Copied from p69 of book then modified
 */
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000         /* maximum input line length */

int getaline(char line[], int max);
int strrindex(char source[], char searchfor[]);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";     /* pattern to search for */

int main()
{
    char line[MAXLINE];
    int found = 0;

    while (getaline(line, MAXLINE) > 0)
    {
        int pos = -1;
        int w1 = 3;
        
        if ((pos = strindex(line, pattern)) >= 0)
        {
            printf(" pos: %*i char: %c  line: %s", w1, pos, line[pos], line);
            found++;
        }

        if ((pos = strrindex(line, pattern)) >= 0)
        {
            printf("rpos: %*i  char: %c  line: %s", w1, pos, line[pos], line);
            found++;
        }
    }

    return found;
}

/* Function
 *
 *    get line into s, return length
 *
 *    Note named function getaline to avoid conflict with getline
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

/* Function
 *
 *   return index of the right most occurance of t in s, -1 if none
 *
 */
int strrindex(char s[], char t[])
{
    int i, j, k;

    for (i = strlen(s) - 1; i >= 0 ; i--)
    {
        for (j = i, k = strlen(t) - 1; k >= 0 && j >= 0 && s[j] == t[k]; j--, k--)
            ;
        if (k < 0 )
            return ++j;
    }
    return -1;
}

/* Function
 *
 *   return index of t in s, -1 if none
 *
 */
int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}
