#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.6 Arrays
 *
 * Exercise 1.14
 *
 *     Write a program to print a histogram of the frequencies of
 *     different characters in it's input.
 *
 *
 * Design
 *
 *     In the days when this text was written the character set of 
 *     a system was probably always going to be ASCII and one character
 *     was always going to be represented by at most 7 bits of one
 *     byte (Note that one byte contains 8 bits).
 *
 *     These days most systems use UTF-8 as their character set and
 *     characters, particularly from non-western languages, may be
 *     represented by 2, 3 or 4 bytes according to the UTF-8 encoding
 *     scheme.
 *   
 *     In order to stay with the spirit of the original task this
 *     program will assume that all known characters can be represented
 *     by one byte.  Thus there are 2^8 or 256 possibilities.
 *
 */

#define ARRAY_LEN 256

int main()
{
    int i, j, c, nl, nw ,nc, wl, state;

    /* We want array index to equal the ascii number of the character.
     *
     */
    int character[ARRAY_LEN]; 

    for (i = 0; i < ARRAY_LEN; ++i)
        character[i] = 0;
    
    while ((c = getchar()) != EOF)
    {
        ++character[c];
    }

    /* Print out the histogram
     */
    printf("%s   %s   %s   %s\n", "Hex", "Char", "Num", "Histogram");
    for (i = 0; i < ARRAY_LEN ; ++i)
    {
        if (character[i] > 0)
        {
            /* Handle special characters such as newlines
             * (ie carriage returns), tabs and spaces 
             */
            if (i == '\0')
                printf("%3x   %4s   %3d   ", i, "NULL", character[i]);
            else if (i == '\b')
                printf("%3x   %4s   %3d   ", i, "BS", character[i]);
            else if (i == '\n')
                printf("%3x   %4s   %3d   ", i, "CR", character[i]);
            else if (i == '\t')
                printf("%3x   %4s   %3d   ", i, "TAB", character[i]);
            else if (i == ' ')
                printf("%3x   %4s   %3d   ", i, "SPC", character[i]);
            else if (i == '\x7f')
                printf("%3x   %4s   %3d   ", i, "DEL", character[i]);
            else
            {
                printf("%3x   %4c   %3d   ", i, i, character[i]);
            }
            for(j = 0; j < character[i]; ++j)
                printf("%c", 'x');
            printf("\n");
        }
    }
}
