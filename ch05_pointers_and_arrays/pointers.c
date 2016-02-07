/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.5 Character Pointers and Functions
 *
 * Exercise 5-6
 *
 *    Rewrite appropriate programs from earlier chapters and exercises
 *    with pointers instead of array indexing. Good possibilities
 *    include getline (Chapters 1 and 4), atoi, itoa, and their
 *    variants (Chapters 2, 3, and 4), reverse (Chapter 3), and
 *    strindex and getop (Chapter 4).
 *
 *    hmmm ... let's not get to carried away here ;-)
 *             the following is from the reverse line program
 *             in chapter 1
 *
 */
#include <stdio.h>

# define MAXLINE 1000    /* maximum input line size */

void printdiv(int c, int n);
int getaline(char *line, int maxline);
void copy(char *to, char *from);
void reverse(char *s);

int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */

    printdiv('=',70);
    printf("Using pointers instead of arrays for reverse line from chapter 1\n");
    printdiv('-',70);
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
void reverse(char *s)
{
    char buffer[MAXLINE];  /* edit buffer */

    int i;

    copy(buffer, s);

    /* go to end of line */
    for (i = 0; buffer[i] != '\n' && i < MAXLINE ; ++i)
        ;

    if (i != MAXLINE)  /* do nothing if overflow */
    {
        --i;        /* don't want newline at beginning */
        while (i >= 0)
        {
            *s++ = buffer[i];
            --i;
        }
        *s++ = '\n';
        *s = '\0';
    }
}

/* getaline
 *
 *    read a line into s, return length
 */
int getaline(char *s, int lim)
{
    int c, i;

    for (i=0; i < lim -1 && (c = getchar()) != EOF && c != '\n'; ++i, ++s)
        *s = c;
        
    if (c == '\n')
    {
        *s++ = c;
        ++i;
    }
    *s = '\0';
    return i;
}

/* copy
 *
 *    copy 'from' into 'to'
 *    assume that 'to' is big enough
 */
void copy(char *to, char *from)
{
    while ((*to++ = *from++))
           ;
}

/* printdiv - print a one line divider
 */
void printdiv(int c, int n)
{
    while (n-- != 0)
        printf("%c", c);
    printf("\n");
}
        
