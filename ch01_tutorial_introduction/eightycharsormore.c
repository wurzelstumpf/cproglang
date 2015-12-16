#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.9 Character Arrays
 *
 * Exercise 1-17
 *
 *    Write a program to print all input lines that are longer than 80
 *    characters.
 *
 * Notes
 *
 *    Needed to change the function name getline to getaline to avoid
 *    a conflict with the standard library function called getline
 *
 */

# define MAXLINE 1000    /* maximum input line size */
# define PRINTLIM 80      /* print lines longer than this limit */

int getaline(char line[], int maxline);
void copy(char to[], char from[]);


int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while ((len = getaline(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
        if(len > PRINTLIM)
        {
            printf("%s: %3d  %s: %s", "Chars", len, "Line", line);
        }
    }

    if (max > 0 && max > PRINTLIM)     /* there was a line */
    {
        printf("%s: %3d  %s: %s", "Chars", max, "Long", longest);
    }

    return 0;
}

/* getline
 *
 *    read a line into s, return length
 */
int getaline(char s[], int lim)
{
    int c, i;

    for (i=0; i < lim -1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy
 *
 *    copy 'from' into 'to'
 *    assume that 'to' is big enough
 */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
