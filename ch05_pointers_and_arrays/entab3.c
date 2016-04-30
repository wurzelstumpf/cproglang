/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.10 Command-line Arguments
 *
 * Exercise 5-12
 *
 *    Extend entab and detab to accept the shorthand
 *    
 *      entab -m +n
 *
 *    to mean tab stops every n columns, starting at column m. Choose convenient
 *    (for the user) default behaviour.
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
 *    First parse command line arguments.  If +n is given set the number of
 *    columns in a tabstop to the integer n. If -m is given begin handling
 *    tabs from column m onwards.
 *
 *    Since a tabstop may not be set to the default terminal tabstop (ie usually
 *    8 columns) spaces are printed using underscores (ie '_') or circumflex
 *    characters (ie '^') if before the start column and any columns traversed
 *    by a tab are printed using plus characters (ie '+').  So when testing
 *    don't use these characters in the input otherwise you will be confused
 *    (!:^*@).
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEF_TAB_STOP  4              /* default number of columns in a tab */
#define MAX_TAB_STOPS 20             /* max number of tab stops on a line */
static int tabstop[MAX_TAB_STOPS];   /* defined tab stops */
static int start_column = 0;         /* from which column are tabs considerd */

enum space { IN, OUT };              /* indicate if reading spaces or not */
void initabstop(int, char**);        /* initialise tab stops for a line */
int col2nts(int);                    /* determine columns to next tab stop */
void print_char(int, int);

int main(int argc, char **argv)
{
    int c;                     /* character */
    int nc = 0;                /* number of character columns read in current line */
    int ns = 0;                /* number of consecutive spaces read */
    int pt = 0;                /* column pointer */
    enum space state = OUT;    /* not reading spaces at the moment */

    initabstop(argc, argv);    /* initialise the global tab stop array */
    while ((c = getchar()) != EOF)
    {
        ++nc;                   /* count characters in line */
        if (c == ' ')
        {
            ++ns;               /* count spaces */
            state = IN;
            continue;           /* get next char from stdin */
        }
        /* read char is not a space but did we just read one of more spaces?
         */
        if (state == IN)
        {
            state = OUT;

            /* position in line where space or spaces began
             * need to subtract one since nc has been incremented by current char
             */
            pt = (nc - 1) - ns;

            for ( ;(pt < start_column) && (pt < (nc -1)) ; pt++)
                print_char('^', 1);

            if (pt >= start_column)
            {
                int ct = col2nts(pt);  /* find columns to next tab stop */

                if (ct < 0)         /* no tab stops left so just output spaces */
                {
                    print_char('_', ns);
                }
                else      /* output an appropriate number of tabs and spaces */
                {
                    while ((ct > 0) && ((pt + ct) < nc))
                    {
                        print_char('+', ct); /* simulate tab with some number of chars */
                        pt += ct;
                        ct = col2nts(pt);
                    }
                    if (pt < (nc - 1))
                        print_char('_', ((nc - 1) - pt)); /* print any remaining spaces */
                }
            }
            ns = 0;             /* set space count to zero */
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
    int i;                          /* for loop index */
    int tab_width = DEF_TAB_STOP;   /* number of columns spanned by a tab */

    /* process command line arguments 
     * this may overwrite all or none of the above default settings
     * we expect something like:  entab -20 +8
     * or just nothing at all:    entab
     * single arguments are also supported:  entab -20   or entab +8
     * if multiple entries for integer arguments preceded by + or -
     * then the last ones will override earlier ones so:
     *    entab -34 -23 -8 +12 +6 +2  is equivalent to entab -8 +2
     *
     */
    for (i = 1; i < argc; i++)
    {
        switch(*argv[i])
        {
        case '-':
            if (strlen(argv[i]) > 1)
                start_column = atoi(argv[i] + 1);
            break;
        case '+':
            if (strlen(argv[i]) > 1)
                tab_width = atoi(argv[i] + 1);
            break;
        default:
            fprintf(stderr, "Unrecognised argument: %s\n", argv[i]);
            break;
        }
    }

    /* initialise global array with default tab stop setting
     */
    for (i = 0; i < MAX_TAB_STOPS; i++)
        tabstop[i] = tab_width;

    /* debugging start */
    printf("start column: %i  tab width: %i\n", start_column, tab_width);
    printf("%s: ", "tabstops");
    for (int i = 0; i < MAX_TAB_STOPS; i++)
        printf(" %i", tabstop[i]);
    printf("\n");
    /* debugging end */
}
