/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4.3 Exernal Variables
 *
 * Exercise 4-9
 *
 *    Our getch and ungetch do not handle a pushed-back EOF
 *    correctly. Decide what their properties ought to be if an EOF is
 *    pushed back, then implement your design.
 *
 *    Hmmmm
 *
 *        Once getch has encountered an EOF from getchar() it should
 *        only return EOF if subsequently queried. Once ungetch has
 *        received an EOF it should flag this so that getch will only
 *        return EOF.
 *
 */
#include <stdio.h>
#include <stdlib.h>          /* for atof() */
#include <math.h>            /* for sin(), cos(), tan(), exp(), pow(), ... */
#include <string.h>

#define MAXOP  100         /* max size of operand or operator */
#define NUMBER '0'         /* signal that a number was found */

int isvar(int);
double getvar(int);
double setvar(int, double);
int getop(char[]);
void clear(void);
void swap(void);
void duplicate(void);
double top(void);
void push(double);
double pop(void);
void ungets(char[]);

int main()
{
    int type;
    int v = 0;          /* to record variable a-z for = op */
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
        case 'v': case 'w': case 'x': case 'y': case 'z': case '$':
            /*
             * note: When a variable is reset using the = operator this could
             *       lead to an unused value on the stack.  This is why the
             *       stack is cleared when a newline is encountered.
             */
            if (isvar(type))
            {
                push(getvar(type));
            }
            else if (type == '$')
            {
                printf("error: no previously printed value\n");
            }
            v = type;            /* record for = op below */
            break;
        case '=':
            if (v)
            {
                setvar(v, pop());
                v = 0;
            }
            else
            {
                printf("error: no previous variable specified\n");
            }
            break;
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
            printf("\t%.8g\n", setvar('$', top()));
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
        case '|':                            /* test command for ungets() */
            ungets(" 23 4 + ");
            break;
        case '\n':
            printf("\t%.8g\n", setvar('$', pop()));
            clear();                                    /* clear the stack */
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

/* Variables
 */
#define VARNUM 27     /* number of variables: a-z and $ */

double var[VARNUM];
unsigned int vbit = 0;    /* works if unsigned int is at least 32 bits */

/* isvar - return 1 if the variable has been set, 0 otherwise 
 */
int isvar(int c)
{
    int i;

    if (c == '$')
        i = 26;
    else
        i = c - 'a';   /* from 0 to 25 */

    unsigned int mask = 1;      /* 00000001 */
    mask <<= i;                 /* 00001000 if i = 3 */
    /* check if varible has been previously set 
     */
    return (vbit & mask) ? 1 : 0;
}

/* getvar - return the value of the variable, if not set then return 0.0 
 */
double getvar(int c)
{
    int i;

    if (c == '$')
        i = 26;
    else
        i = c - 'a';   /* from 0 to 25 */

    unsigned int mask = 1;      /* 00000001 */
    mask <<= i;                 /* 00001000 if i = 3 */
    if (vbit & mask)            /* varible has been previously set */
        return var[i];
    else
        printf("error: variable %c has not been set\n", c);

    return 0.0;
}

/* setvar - set the variable and return the value it was set to
 */
double setvar(int c, double d)
{
    int i;

    if (c == '$')
        i = 26;
    else
        i = c - 'a';   /* from 0 to 25 */

    unsigned int mask = 1;      /* 00000001 */
    mask <<= i;                 /* 00001000 if i = 3 */
    vbit |= mask;               /* record set */
    var[i] = d;                 /* set var */
    return d;                   /* return value of var */
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
 *    variables a-z and $ for last printed value
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
        return c;                       /* must be an operator or variable */

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
int eof = 0;              /* did getch return an eof */

/* getch - get a (possibly pushed back) character */
int getch(void)
{
    int c;

    if (eof)
    {
        return EOF;
    }
    else if (bufp > 0)
    {
        return buf[--bufp];
    }
    else
    {
        c = getchar();
        if (c == EOF)
        {
            ++eof;
        }
        return c;
    }
}

/* ungetch - push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: to many characters\n");
    else
    {
        if (c == EOF)
        {
            ++eof;
        }
        buf[bufp++] = c;
    }
}
    
void ungets(char s[])
{
    /* need to start at end of string to be able to read from beginning */
    for (int i = strlen(s) - 1; i >= 0 ; i--)
        ungetch(s[i]);
}
