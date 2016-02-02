/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4.2 Functions Returning Non-integers
 *
 * Exercise 4-2
 *
 *    Extend atof to handle scientific notation of the form
 *    
 *        123.45e-6
 *
 *    where a floating-point number may be followed by e or E and an
 *    optionally signed exponent.
 *
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 1000         /* maximum line length */

double atof(char s[]);
double a2f(char s[]);

int main()
{
    char s[MAX_LEN];
    int w1 = 5;
    int w2 = 12;

    strncpy(s, "123.456", MAX_LEN);
    printf("%*s: %*g  string: %s\n", w1, "atof", w2, atof(s), s);
    printf("%*s: %*g  string: %s\n", w1, "a2f", w2, a2f(s), s);

    strncpy(s, "+123.456", MAX_LEN);
    printf("%*s: %*g  string: %s\n", w1, "atof", w2, atof(s), s);
    printf("%*s: %*g  string: %s\n", w1, "a2f", w2, a2f(s), s);

    strncpy(s, "-123.456", MAX_LEN);
    printf("%*s: %*g  string: %s\n", w1, "atof", w2, atof(s), s);
    printf("%*s: %*g  string: %s\n", w1, "a2f", w2, a2f(s), s);

    strncpy(s, "+123e-4", MAX_LEN);
    printf("%*s: %*g  string: %s\n", w1, "atof", w2, atof(s), s);
    printf("%*s: %*g  string: %s\n", w1, "a2f", w2, a2f(s), s);

    strncpy(s, "+13.0e4", MAX_LEN);
    printf("%*s: %*g  string: %s\n", w1, "atof", w2, atof(s), s);
    printf("%*s: %*g  string: %s\n", w1, "a2f", w2, a2f(s), s);

    strncpy(s, "-23.00001E+5", MAX_LEN);
    printf("%*s: %*g  string: %s\n", w1, "atof", w2, atof(s), s);
    printf("%*s: %*g  string: %s\n", w1, "a2f", w2, a2f(s), s);

}

/* Function
 *
 *    convert string s to double and allow for e or E and an
 *    optionally signed exponent
 *
 *    some cases to consider:
 *
 *        123.45e-6   -1.0234E+23   +0.233E23  3e-453  23.e-9
 *
 */
double a2f(char s[])
{
    double val, power;
    int i, sign, exp_sign, exp;

    for (i = 0; isspace(s[i]); i++)    /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;     /* note sign */
    if (s[i] == '+' || s[i] == '-')    /* skip leading sign */
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = val * 10 + (s[i] - '0');

    if (s[i] == '.')                   /* decimal point */
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = val * 10 + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E')    /* exponent */
        i++;

    exp_sign = (s[i] == '-') ? -1 : 1; /* note exponent sign */

    if (s[i] == '+' || s[i] == '-')    /* skip leading sign */
        i++;

    for (exp = 0; isdigit(s[i]); i++)  /* get exponent */
        exp = exp * 10 + (s[i] - '0');

    if (exp_sign > 0)
    {
        for (i = 0; i < exp ; i++)
            val *= 10;
    }
    else
    {
        for (i = 0; i < exp; i++)
            val *= 0.1;
    }

    return sign * val / power;
}

/* Function
 *
 *    convert string s to double
 *
 *    from p71
 */
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)    /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = val * 10 + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = val * 10 + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}
