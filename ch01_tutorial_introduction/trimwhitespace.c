#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.9 Character Arrays
 *
 * Exercise 1-18
 *
 *    Write a program to remove trailing blanks and tabs from each
 *    line of input, and to delete entirely blank lines.
 *
 * Notes
 *
 *    Needed to change the function name getline to getaline to avoid
 *    a conflict with the standard library function called getline
 *
 * Design
 *
 *    The length of a line that we can hold is limited so when a
 *    line exceed this limit we will return the value 1 to the
 *    caller program instead of the value 0 (all ok)
 *
 */

# define MAXLINE 1000    /* maximum input line size */

void trim(char s[], int len);
int getaline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char buffer[MAXLINE];  /* edit buffer */

    max = 0;
    while ((len = getaline(line, MAXLINE)) > 0)
    {
        copy(buffer, line);

        if (len > max)
            max = len;

        trim(buffer, len);

        if (buffer[0] != '\n')
            printf("%s", buffer);
        
    }


    if (max > MAXLINE)
        return 1;
    else
        return 0;
}

/* trim
 *
 *    remove trailing blanks and tabs from each line
 *    terminates line with character sequence "\n\0"
 *    just as the function getaline does
 *    assumes s is at least 2 chars long
 *
 */
void trim(char s[], int len)
{
    int i;

    i = len - 2;      /* one char before terminating newline */

    while ((s[i] == '\t' || s[i] == ' ') && i >= 0)
        --i;

    s[++i] = '\n';
    s[++i] = '\0';
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
