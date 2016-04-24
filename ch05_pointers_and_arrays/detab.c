/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.10 Command-line Arguments
 *
 * Exercise 5-11
 *
 *    Modify the programs entab and detab (written as exercises in Chapter 1) to
 *    accept a list of tab stops as arguments. Use the default tab settings if
 *    there are no arguments.
 *
 * Design (from original version)
 *
 *    Read a character and output it.  If the character is a space
 *    we need to keep a count of the the number of consecutive spaces
 *    and see if we reach a tab stop.  If so we can replace the spaces
 *    with a tab.
 *
 *    Convention has it that tabstops are expected to occur every 8
 *    columns. Hence n = 8 for our program and we will write the
 *    initial version using a symbolic constant.  It should actually
 *    be possible to modify this by providing a command line option
 *    and in a future version it would make more sense to use a
 *    variable to represent n.
 *
 *    As we are adding tabs a tab should be used instead of a single
 *    space to reach a tab stop.
 *
 * Design (extension for this exercise)
 *
 *    First parse command line arguments.  If a list of tab stops is provided
 *    then store them in an array of integers.  This will require some maximum
 *    number of elements.  Then a function will use the elements of this array
 *    to calculate the columns to the next tab stop. 
 *
 *    Since a tabstop may not be set to the default terminal tabstop (ie usually
 *    8 columns) spaces are printed using underscores (ie '_') instead.  So when
 *    testing don't use these characters in the input otherwise you will be
 *    confused (!:^*@).
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEF_TAB_STOP  4             /* default number of columns in a tab */
#define MAX_TAB_STOPS 20             /* max number of tab stops on a line */
static int tabstop[MAX_TAB_STOPS];   /* defined tab stops */

void initabstop(int, char**);        /* initialise tab stops for a line */
int col2nts(int);                    /* determine columns to next tab stop */
void print_char(int, int);

int main(int argc, char **argv)
{
    int c;                     /* character */
    int nc = 0;                /* number of character columns read in current line */

    initabstop(argc, argv);    /* initialise the global tab stop array */
    while ((c = getchar()) != EOF)
    {
        ++nc;                   /* count characters in line */
        if (c == '\t')
        {
            int ct = col2nts(nc - 1);
            print_char('_', ct);
            nc += ct - 1;
            continue;
        }
        if (c == '\n')
        {
            nc = 0;             /* reset column counter for end of lines */
        }
        putchar(c);
    }
    return 0;
}

/* function -- print out a character some number of times
 */
void print_char(int c, int n)
{
    for (int i = 0; i < n; i++)
        putchar(c);
}

/* function -- return number of columns to next tab stop, or -1 if no tab stops
 */
int col2nts(int cc)
{
    int sum = 0;
    for (int i = 0; i < MAX_TAB_STOPS && sum <= cc; i++)
        sum += tabstop[i];
    int cols = sum - cc;
    return (cols >= 0) ? cols : -1;
}
   
    
/* function -- initialise the global tab stop array either from the command line
 *             or use the default defined setting
 */
void initabstop(int argc, char **argv)
{
    int i;                      /* for loop index */
    int tab_index = 0;          /* index to global tabstop array */

    /* initialise global array with default tab stop setting
     */
    for (i = 0; i < MAX_TAB_STOPS; i++)
        tabstop[i] = DEF_TAB_STOP;

    /* process command line arguments 
     * this may overwrite all or none of the above default settings
     * we expect something like:  entab -t 4,5,3,5,12,2
     * or just nothing at all:    entab
     * this is also supported:    entab -t 2,6 -t 8 -t 4,10,12 -t 16
     *
     * note it misses last tabstop in something like: entab -t 2,4,6
     * this is probably to do with strtok()
     */
    for (i = 1; i < argc; i++)
    {
        /* this is a bit rough but to the point 
         */
        if (strncmp("-t", *(argv + i), strlen("-t")) == 0)
        {
            if (++i < argc)     /* if another argument exists */
            {
                char *delim = ",";
                char *token = strtok(*(argv + i), delim);
                while (token != NULL && tab_index < MAX_TAB_STOPS)
                {
                    /* turn string into int and add to tabstop 
                     */
                    int num = atoi(token);
                    tabstop[tab_index] = num;
                    tab_index++;
                    token = strtok(NULL, delim); /* get next token */
                }
            }
        }
    }

    /* debugging start */
    printf("%s: ", "tabstops");
    for (int i = 0; i < MAX_TAB_STOPS; i++)
        printf(" %i", tabstop[i]);
    printf("\n");
    /* debugging end */
}
