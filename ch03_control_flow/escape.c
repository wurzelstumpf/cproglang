#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 3.4 Switch
 *
 * Exercise 3-2
 *
 *    Write a function escape(s, t) that converts characters like
 *    newline and tab into visible escape sequnces like \n and \t as it
 *    copies the string t to s. Use a switch. Write a function for the
 *    other direction as well, converting escape sequences into the real
 *    characters.
 *
 */
#define MAX_STR 1000

int escape(char s[], char t[]);
int descape(char s[], char t[]);

int main()
{
    char to[MAX_STR];

    char from[] = "Hi there\t\ns";
    int num = escape(to, from);
    printf("from: '%s'  \n  to: '%s'\n num: %i \n", from, to, num);

    char desc[14];
    desc[0] = 'H';
    desc[1] = 'i';
    desc[2] = ' ';
    desc[3] = 't';
    desc[4] = 'h';
    desc[5] = 'e';
    desc[6] = 'r';
    desc[7] = 'e';
    desc[8] = '\\';
    desc[9] = 't';
    desc[10] = '\\';
    desc[11] = 'n';
    desc[12] = 's';
    desc[13] = '\0';
    num = descape(to, from);
    printf("from: '%s'  \n  to: '%s'\n num: %i \n", desc, to, num);
}

/* Function
 *
 *    Convert escape sequences like \n and \t into their corresponding
 *    characters as the string t is copied to s
 *
 *    Return the number of escape sequences converted
 *
 * Note
 *
 *    Despite explicitly setting each character in the string in main
 *    the loop in descape still interprets a two character sequence
 *    such as '\','t' as '\t'. Hence the return value for the number
 *    of characters de-escaped is 0.  This is probably due to some
 *    optimisation in the compiler.
 */
int descape(char s[], char t[])
{
    int nc = 0;
    int i, j;

    for (i = 0, j = 0; t[i] != '\0' && j < MAX_STR ; ++i, ++j)
        switch (t[i])
        {
        case '\\':
            ++i;              /* look ahead */
            switch (t[i])
            {
            case 't':
                s[j] = '\t';
                ++nc;
                break;
            case 'n':
                s[j] = '\n';
                ++nc;
                break;
            default:
                --i;
                s[j] = t[i];
                break;
            }
            break;
        default:
            s[j] = t[i];
            break;
        }

    s[j] = '\0';    /* terminate string */

    return nc;
}

/* Function
 *
 *    Convert characters line newline and tab into visible escape
 *    sequences like \n and \t as the string t is copied to s
 *
 *    Return the number of characters escaped
 *
 */
int escape(char s[], char t[])
{
    int nc = 0;
    int i, j;

    for (i = 0, j = 0; t[i] != '\0' && j < MAX_STR ; ++i, ++j)
        switch (t[i])
        {
        case '\t':
            s[j++] = '\\';
            s[j] = 't';
            ++nc;
            break;
        case '\n':
            s[j++] = '\\';
            s[j] = 'n';
            ++nc;
            break;
        default:
            s[j] = t[i];
            break;
        }

    s[j] = '\0';    /* terminate string */

    return nc;
}
