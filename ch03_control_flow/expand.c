#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 3.5 Loops - While and For
 *
 * Exercise 3-3
 *
 *    Write a function expand(s1, s2) that expands shorthand notations
 *    like a-z in th string s1 into the equivalent complete list
 *    abc....xyz in s2. Allow for letters of either case and digits,
 *    and be prepared to handle cases like a-b-c and a-z0-9 and
 *    -a-z. Arrange that a leading or trailing - is taken literally.
 *
 */

const short max = 1000;         /* max length of string arrays */

int expand(char s1[], char s2[]);

int main()
{
    char s[max];
    char ss[max];
    int nc = 0;
    int w1 = 4;
    int w2 = 30;

    strncpy(s, "a-z", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "a-b-c", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "I wonder what a-b-c m-wwill do", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "a-a", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "-k-z-j-k-", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "A-Z", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "A-B-C", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "I wonder what A-B-C M-WWill do", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "A-A", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "-K-Z-J-K-", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "0-9", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "0-1-2", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "I wonder what 0-1-2 3-77ill do", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "5-5", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "-3-9-4-5-", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);

    strncpy(s, "-a-l3-9-K-c-gH-W-4-o-r-S", max);
    nc = expand(s, ss);
    printf("chars added: %*i | %*s ..... %s\n", w1, nc, w2, s, ss);


    return 0;
}

/* Function
 *
 *    Expand shorthand notations like a-z in th string s1 into the
 *    equivalent complete list abc....xyz in s2. It allows for letters
 *    of either case and digits, will handle cases like a-b-c and
 *    a-z0-9 and -a-z. A leading or trailing - is taken literally.
 *
 *    Assumes char array s2 is large enough to hold expanded char string
 *
 *    Returns the number of characters added to the expansion.
 *
 *    Notes
 *
 *      consecutive dash characters are interpreted as a single dash
 *
 */
int expand(char s1[], char s2[])
{
    int nc = 0;
    short expanding = 0;         /* not expanding */
    int lead = 0;                /* lead char */

    int i, j;                    /* array indices */

    for (i = 0, j = 0; i < strlen(s1); ++i)
    {
        int c = s1[i];          /* assign a convenient variable */
        
        if (isalnum(c))
        {
            if (lead && expanding)
            {
                if ((islower(lead) && islower(c)) ||
                    (isupper(lead) && isupper(c)) ||
                    (isdigit(lead) && isdigit(c)) )
                {
                    if (lead >= c)
                    {
                        s2[j++] = '-';     /* add trailing dash */
                    }
                    else                   /* expand */
                    {
                        for (int k = ++lead; k < c ; k++)
                        {
                            ++nc;
                            s2[j++] = k;
                        }
                    }

                    lead = c;              /* reset lead */
                    expanding = 0;         /* not expanding */
                }
                else
                {
                    lead = c;
                    expanding = 0;
                    s2[j++] = '-';     /* add trailing dash */
                }
            }
            else
                lead = c;
        }

        if (c == '-')
        {
            if (lead)
            {
                expanding = 1;
                continue;
            }
        }

        s2[j++] = c;
    }

    if (expanding)
        s2[j++] = '-';     /* print trailing dash */

    s2[j] = '\0';          /* terminate string */

    return nc;
}

