#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 1.6 Arrays
 *
 * Exercise 1-13
 *
 *     Write a program to print a histogram of the lengths
 *     of words in it's input.
 *
 */

#define MAX_WORD_LEN 10

#define  IN  1    /* inside a word */
#define  OUT 0    /* outside a word */

int main()
{
    int i, c, nl, nw ,nc, wl, state;

    /* We want array index to equal word length so add 1
     *
     * Note than arrays in c index from 0 so the definition; int ar[20]
     * refers to an array of 20 elements indexed from ar[0] to ar[19]
     *
     * Note also that since a word must consist of 1 or more characters
     * this will mean that the value of the first element in the array
     * will always be zero
     */
    int len = MAX_WORD_LEN + 1;

    int wordlen[len]; 

    nl = nw = nc = wl = 0;

    for (i = 0; i < len; ++i)
        wordlen[i] = 0;
    
    state = OUT;

    while ((c = getchar()) != EOF)
    {
        ++nc;                /* count characters */
        if (c == '\n')       /* count newlines */
            ++nl;

        if (c == ' ' || c == '\n' || c == '\t')  /* whitespace */
        {
            if (state == IN)   /* were we in a word? */
            {
                if (wl >= MAX_WORD_LEN)
                    ++wordlen[MAX_WORD_LEN];
                else
                    ++wordlen[wl];

                wl = 0;    /* reset word length counter */
            }
            state = OUT;
        }
        else    /* must be a word */
        {
            if (state == OUT)  
            {
                state = IN;
                ++nw;        /* count words */
            }
            ++wl;            /* count word length */
        }
    }

    /* Print out the histogram
     */
    printf("%s   %s   %s\n", "Len", "Num", "Histogram");
    for (i = 1; i < len ; ++i)
    {
        printf("%3d   %3d   ", i, wordlen[i]);

        for(int j = 0; j < wordlen[i]; ++j)
            printf("%c", 'x');

        printf("\n");
    }

    /* Print out a summary of lines, words and characters read
     */
    printf("\nTotal number of lines: %d  words: %d  characters: %d\n", nl, nw, nc);
}
