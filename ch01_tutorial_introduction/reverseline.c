#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.9 Character Arrays
 *
 * Exercise 1-19
 *
 *    Write a function reverse(s) that reverses the character string
 *    s. Use it to write a program that reverses its input a line at a
 *    time.
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

int getaline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);

int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */

    max = 0;
    while ((len = getaline(line, MAXLINE)) > 0)
    {
        if (len > max)
            max = len;

/*        printf("%s: %3d  %8s: %s", "Chars", len, "Line", line);
 */
/*        printf("%s", line);
 */
        reverse(line);
        printf("%s", line);

/*        printf("%s: %3d  %8s: %s", "Chars", len, "Reversed", line);
 */
    }


    if (max > MAXLINE)
        return 1;
    else
        return 0;
}

/* reverse
 *
 *    reverse the character string in the line s
 *    assumes the character array s is MAXLINE long
 *    assumes line is terminated by '\n' character
 */
void reverse(char s[])
{
    char buffer[MAXLINE];  /* edit buffer */

    int i, j;

    copy(buffer, s);

    /* go to end of line */
    for (i = 0; buffer[i] != '\n' && i < MAXLINE ; ++i)
        ;

    if (i != MAXLINE)  /* do nothing if overflow */
    {
        --i;        /* don't want newline at beginning */
        j = 0;
        while (i >= 0)
        {
            s[j] = buffer[i];
            --i;
            ++j;
        }
        s[j] = '\n';
        s[++j] = '\0';
    }
}

/* getaline
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
