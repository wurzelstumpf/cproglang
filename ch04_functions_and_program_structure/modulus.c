/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4. Exernal Variables
 *
 * Exercise 4-3
 *
 *    Given the basic framework, it's straightforward to extend the
 *    calculator. Add the modulus (%) operator and provisions for
 *    negative numbers.
 */
#include <stdio.h>
#include <stdlib.h>          /* for atof() */

#define MAXOP  100         /* max size of operand or operator */
#define NUMBER '0'         /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
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
                printf("error: zero divisor for operator '/'\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
            {
                /* In C the modulus operator only works on shorts,
                 * integers, longs, ... but not when the operands
                 * are floats or doubles.  Thus we have to emulate a
                 * modulus operation for operands of type double.
                 */
                double d = pop();
                if (d < op2)
                    push(d);
                else if (d == op2)
                    push(0.0);
                else
                {
                    while ((d -= op2) > op2)
                        ;
                    if (d == op2)
                        push(0.0);
                    else
                        push(d);
                }
            }
            else
                printf("error: zero divisor for operator '%%'\n");
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

int getch(void);
void ungetch(int);

/* Function - getop - get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    /* skip space and horizontal tabs 
     */
    while ((s[0] = c = getch()) == ' ' || c == '\t')  
        ;

    if (c == '-' || c == '+')
    {
        /* need to decide if the plus or minus specifies
         * the sign of a number or is itself an operator
         */
        s[1] = c = getch();             /* get next char */
        if (isdigit(c))                 /* is a sign */
        {
            s[2] = '\0';                    /* terminate string */
            i = 1;                          /* prep index into s */
        }
        else
        {
            ungetch(c);
            c = s[0];                       /* must be an operator */
            s[1] = '\0';                    /* terminate string */
            i = 0;                          /* prep index into s */
        }
    }
    else
    {
        s[1] = '\0';                    /* terminate string */
        i = 0;                          /* prep index into s */
    }

    if (!isdigit(c) && c != '.')        /* not a number or period */
        return c;                       /* must be an operator */

    /* collect integer part 
     */    
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    /* collect fraction part 
     */    
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';                        /* terminate string */
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
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Function - ungetch - push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: to many characters\n");
    else
        buf[bufp++] = c;
}
    

