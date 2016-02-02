#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.6 Relational and Logical Operators
 *
 * Exercise 2-2
 *
 *    Write a loop equivalent to the for loop above (ie in function
 *    getaline) without using && or ||.
 *
 * Notes
 *
 *    Lifted this source file from ch01 longestline.c
 *
 *    Needed to change the function name getline to getaline to avoid
 *    a conflict with the standard library function called getline
 *
 */

# define MAXLINE 1000    /* maximum input line size */

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
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }

    if (max > 0)          /* there was a line */
        printf("%s", longest);

    return 0;
}

/* getline
 *
 *    read a line into s, return length
 */
int getaline(char s[], int lim)
{
  int c, i, j;

  /* This is a bit subtle.  In order to avoid using && or || we need
   * to use an additional int variable j which keeps track of where i is
   * up to and can be used instead of i to properly terminate the string.
   * This is necessary since i is modified to facilitate termination of
   * the loop.
   */
  for (i=0, j=0; i < lim - 1; ++i, ++j) 
    if((c = getchar()) != '\n') 
      if (c != EOF) 
	s[i] = c; 
      else 
	i = lim - 1; /* terminate  loop */
    else
      i = lim - 1;   /* terminate loop */

  /* Note that i may have been modified to facilitate exit from the
   * loop so we will use the variable j instead to terminate the
   * string and return the number of characters in the line.
   */
  --j;            /* for loop leaves j incremented by one to many */
  if (c == '\n')
    {
      s[j] = c;
      ++j;
    }
  s[j] = '\0';
  return j;
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
