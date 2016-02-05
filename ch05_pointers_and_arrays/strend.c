/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.5 Character Pointers and Functions
 *
 * Exercise 5-4
 *
 *    Write the function strend(s,t), which returns 1 if the string t
 *    occurs at the end of the string s, and zero otherwise.
 *
 */
#include <stdio.h>

int strend(char*, char*);

int main()
{
    char *s;
    char *t;

    s = "";
    t = "s";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "short";
    t = "t";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "short";
    t = "rt";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "longer";
    t = "";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "longer too";
    t = "o";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "longer too";
    t = "z";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "shorter";
    t = "is longer";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "shorter";
    t = "!shorter";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    s = "shorter";
    t = "shorter";
    printf("strend('%s', '%s') returns %i\n", s, t, strend(s, t));

    return 0;
}

/* strend - return 1 if string t occurs at end of s, 0 otherwise 
 */
int strend(char *s, char *t)
{
    /* handle null strings gracefully */
    if (*t == '\0')
        return 1;

    if (*s == '\0')
        return 0;

    /* from now on we know the function arguments are not empty strings
     */
    char *sb = s;          /* s beginning */
    char *tb = t;          /* t beginning */

    /* move to end of each function argument
     */
    while (*s != '\0')
        s++;
    
    while (*t != '\0')
        t++;
    
    for (; (*s == *t) && (tb <= t) && (sb <= s); s--, t--)
        ;

    return (t < tb) ? 1 : 0;
}
