/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.10. Command-line Arguments
 *
 * Exercise 5-10
 *
 *    Write the program expr, which evaluates a reverse Polish expression from
 *    the command line, where each operator or operand is a separate
 *    argument. For example, expr 2 3 4 + * evaluates 2 x (3+4).
 *
 * Note
 *
 *    Chose to modify the reverse polish calculator from p76 to p79
 *
 *    When using the mulitplication operator * on the command line you will need
 *    to escape it from interpretation as a glob file matching pattern by the
 *    shell.  (eg  polexpr 2 3 + 4 5 - \* )
 *
 */
#include <stdio.h>
#include <stdlib.h>          /* for atof() */

#define MAXOP  100         /* max size of operand or operator */
#define NUMBER '0'         /* signal that a number was found */

int getop(int, char**, char[]);
void push(double);
double pop(void);

int main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(argc, argv, s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}


/* Stack
 */
#define MAXVAL 100    /* maximum depth of val stack */

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* stack of values */

/* Function - push - push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* Function - pop - pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* Operators and operands
 */
#include <ctype.h>

int getch(int argc, char **argv);
void ungetch(int);

/* Function - getop - get next operator or numeric operand */
int getop(int argc, char **argv, char s[])
{
    int i, c;

    /* skip space and horizontal tabs 
     */
    while ((s[0] = c = getch(argc, argv)) == ' ' || c == '\t')  
        ;
    s[1] = '\0';                        /* terminate string */
    if (!isdigit(c) && c != '.')
        return c;                       /* not a number or period */
    i = 0;
    if (isdigit(c))                     /* collect integer part */
        while (isdigit(s[++i] = c = getch(argc, argv)))
            ;
    if (c == '.')                      /* collect fraction part */
        while (isdigit(s[++i] = c = getch(argc, argv)))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}


/* Character handlers
 */
#define BUFSIZE 100

char buf[BUFSIZE];        /* buffer for ungetch */
int bufp = 0;             /* next free position in buf */

/* Function - getch - get a (possibly pushed back) character */
int getch(int argc, char **argv)
{
    static int ai = 1;
    static int i = 0;
    int c;

    /* return (bufp > 0) ? buf[--bufp] : getchar();  */
    if (bufp > 0)
    {
        c = buf[--bufp];
        return c;
    }

    if (ai >= argc)
        return EOF;

    c = (*((*(argv + ai)) + i));

    /* printf("getch: char c: %c int: %i\n", c, c); */

    if (c == '\0')
    {
        ai++;                       /* next argument */
        i = 0;                      /* first char of next argument */
        /*
         * need to return a newline after the last argument for the result to be printed
         * otherwise we just need to return a space to emulate an input string
         */
        c = (ai >= argc) ? '\n': ' ';   
    }
    else
    {
        i++;                    /* next char of current argument */
    }

    return c;
}

/* Function - ungetch - push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: to many characters\n");
    else
        buf[bufp++] = c;
}
    

