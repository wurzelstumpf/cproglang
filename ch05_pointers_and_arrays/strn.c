/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.5 Character Pointers and Functions
 *
 * Exercise 5-5
 *
 *    Write versions of the library functions strncpy, strncat, and
 *    strncmp, which operate on at most the first n characters of
 *    their argument strings. For example strncpy(s,t,n) copies at
 *    most n characters of t to s.
 *
 */
#include <stdio.h>

const unsigned int max_str = 1000;

char *strncpy_m(char *s, const char *ct, size_t n);
char *strncat_m(char *s, const char *ct, size_t n);
int strncmp_m(const char *cs, const char *ct, size_t n);

void printdiv(int c, int n);

int main()
{
    char buf[max_str];
    char *s;
    char *t;
    int dw = 70;
    int n = 0;

    printdiv('=', dw);
    s = buf;
    *s = 'a';
    *(s + 1) = 'b';
    *(s + 2) = 'c';
    *(s + 3) = '\0';
    printf("s = \"%s\" ", s);
    t = "sksdf";
    printf("t = \"%s\" ", t);
    n = 6;
    printf("strncpy_m(s, t, %i) returns \"%s\"\n", n, strncpy_m(s, t, n));
    printdiv('-', dw);

    printdiv('=', dw);
    s = buf;
    *s = 'a';
    *(s + 1) = 'b';
    *(s + 2) = 'c';
    *(s + 3) = '\0';
    printf("s = \"%s\" ", s);
    t = "sksdf";
    printf("t = \"%s\" ", t);
    n = 10;
    printf("strncat_m(s, t, %i) returns \"%s\"\n", n, strncat_m(s, t, n));
    printdiv('-', dw);

    printdiv('=', dw);
    s = buf;
    *s = 'a';
    *(s + 1) = 'b';
    *(s + 2) = 'c';
    *(s + 3) = '\0';
    printf("s = \"%s\" ", s);
    t = "sksdf";
    printf("t = \"%s\" ", t);
    n = 10;
    printf("strncmp_m(s, t, %i) returns \"%i\"\n", n, strncmp_m(s, t, n));

    s = buf;
    *s = 's';
    *(s + 1) = 'k';
    *(s + 2) = 's';
    *(s + 3) = '\0';
    printf("s = \"%s\" ", s);
    t = "sksdf";
    printf("t = \"%s\" ", t);
    n = 3;
    printf("strncmp_m(s, t, %i) returns \"%i\"\n", n, strncmp_m(s, t, n));

    s = buf;
    *s = 's';
    *(s + 1) = 'k';
    *(s + 2) = 's';
    *(s + 3) = '\0';
    printf("s = \"%s\" ", s);
    t = "sksdf";
    printf("t = \"%s\" ", t);
    n = 4;
    printf("strncmp_m(s, t, %i) returns \"%i\"\n", n, strncmp_m(s, t, n));
    
    s = buf;
    *s = 's';
    *(s + 1) = 'k';
    *(s + 2) = 's';
    *(s + 3) = 'd';
    *(s + 4) = 'f';
    *(s + 5) = '\0';
    printf("s = \"%s\" ", s);
    t = "sksdf";
    printf("t = \"%s\" ", t);
    n = 5;
    printf("strncmp_m(s, t, %i) returns \"%i\"\n", n, strncmp_m(s, t, n));
    
    s = buf;
    *s = 's';
    *(s + 1) = 'k';
    *(s + 2) = 's';
    *(s + 3) = 'd';
    *(s + 4) = 'f';
    *(s + 5) = ' ';
    *(s + 6) = '\0';
    printf("s = \"%s\" ", s);
    t = "sksdf";
    printf("t = \"%s\" ", t);
    n = 6;
    printf("strncmp_m(s, t, %i) returns \"%i\"\n", n, strncmp_m(s, t, n));
    
    printdiv('-', dw);

    return 0;
}

/* strncpy_m - copy ct to s, at most n chars, return s, s must be big enough
 *             pad with null chars if strlen(ct) < n
 *           
 */
char *strncpy_m(char *s, const char *ct, size_t n)
{
    char *sp = s;
    for (;n > 0 && *ct != '\0'; n--)
        *sp++ = *ct++;

    for (;n > 0; n--)
        *sp++ = '\0';    /* pad with null chars if n > strlen(ct) */
    
    return s;
}

/* strncat_m - copy ct to end of s, at most n chars, return s, s must be big enough
 */
char *strncat_m(char *s, const char *ct, size_t n)
{
    char *sp = s;
    while (*sp != '\0')
        sp++;             /* advance to end of s */

    while (n != 0 && *ct != '\0')
    {
        *sp++ = *ct++;
        n--;
    }
    *sp = '\0';
    return s;
}

/* strncmp_m - compare ct to s, at most n chars, return < 0 if cs < ct,
 *             0 if cs == ct, >0 if cs > ct
 */
int strncmp_m(const char *cs, const char *ct, size_t n)
{
    if (n == 0)         /* handle silly requests with grace */
        return 0;
    
    while (*cs != '\0' && *ct != '\0' && n > 0)
    {
        if (*cs == *ct)
        {
            cs++;
            ct++;
            n--;
            continue;
        }
        
        if (*cs < *ct)
            return -1;

        if (*cs > *ct)
            return 1;
    }

    if (*cs == '\0' && *ct != '\0' && n != 0)         /* cs shorter than ct */
        return -1;

    if (*cs != '\0' && *ct == '\0' && n != 0)         /* cs longer than ct */
        return 1;

    return 0;       /* (n == 0 || (*cs == '\0' && *ct == '\0')) */
}

/* printdiv - print a one line divider
 */
void printdiv(int c, int n)
{
    while (n-- != 0)
        printf("%c", c);
    printf("\n");
}
        
