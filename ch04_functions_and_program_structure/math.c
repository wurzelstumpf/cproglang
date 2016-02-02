/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4. Exernal Variables
 *
 * Exercise 4-5
 *
 *    Add access to library functions like sin, exp, and pow. See
 *    <math.h> in Appendix B, Section 4.
 *
 */
#include <stdio.h>
#include <stdlib.h>          /* for atof() */
#include <math.h>            /* for sin(), cos(), tan(), exp(), pow(), ... */

#define MAXOP  100         /* max size of operand or operator */
#define NUMBER '0'         /* signal that a number was found */

int getop(char[]);
void clear(void);
void swap(void);
void duplicate(void);
double top(void);
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
        case 'S':
            push(sin(pop()));
            break;
        case 'C':
            push(cos(pop()));
            break;
        case 'T':
            push(tan(pop()));
            break;
        case 'X':
            push(exp(pop()));
            break;
        case 'L':
            push(log10(pop()));
            break;
        case 'E':
            push(exp(pop()));
            break;
        case 'R':
            push(sqrt(pop()));
            break;
        case 'P':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case '!':
            clear();
            break;
        case '@':
            swap();
            break;
        case '#':
            duplicate();
            break;
        case '&':
            printf("\t%.8g\n", top());
            break;
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
                /* In C the modulus operator only works on short,
                 * integer, long, ... but not when the operands
                 * are float or double.  Thus we have to emulate a
                 * modulus operation for operands of type double.
                 *
                 * note: <math.h> has the function fmod() for this
                 *
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

/* clear - clear the stack */
void clear(void)
{
    sp = 0;
}

/* swap - the top two elements of the stack, do nothing if less than 2 */
void swap(void)
{
    if (sp > 1)
    {
        double d;
        d = val[sp - 2];
        val[sp - 2] =  val[sp - 1];
        val[sp - 1] = d;
    }
}

/* duplicate - the top element of the stack, do nothing if none */
void duplicate(void)
{
    if (sp > 0)
    {
        val[sp] =  val[sp - 1];
        sp++;
    }
}

/* top - return the value at the top of the stack, 0.0 otherwise */
double top(void)
{
    if (sp > 0)
        return val[sp - 1];
    else
        printf("error: stack empty\n");
    return 0.0;
}

/* push - push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop - pop and return top value from stack */
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

/* getop - get next operator or numeric operand 
 *
 *    numbers and operators are separated by white space:
 *        2 3 + 3.4 5.3 * %
 *
 *    numbers may be prefixed by an optional plus or minus sign:
 *        -2.34 7.1 / +23.1 -3 - *
 *
 *    operators are followed by a white space character
 *        standard --> + - * / %
 *           stack --> ! (clear)  @ (swap)  # (duplicate)  & (print)
 *            math --> S (sin) C (cos) T (tan)  X (exp) L (log10) 
 *                     E (log) R (sqrt) P (pow)
 *        
 */
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

/* getch - get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch - push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: to many characters\n");
    else
        buf[bufp++] = c;
}
    

