/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4.3 Exernal Variables
 *
 * Exercise 4-10
 *
 *    An alernate organization uses getline to read an entire input
 *    line; this makes getch and ungetch unnecessary. Revise the
 *    calculator to use this approach.
 *
 *    Hmmmm
 *
 *        The function using getch and ungetch is getop.  Approach
 *        will be to modify getop to read lines into a char array and
 *        use an index into the array to access characters.  This
 *        approach will allow for the bulk of the logic in getop to
 *        remain unchanged.  Both the index and the char array will be
 *        defined as global variables so that they will be persistant
 *        between calls to getop.
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

#define MAX_LINE 1000      /* max chars read by getaline */

char line[MAX_LINE];       /* global for storing line for getop */
int lp = -1;               /* current index pointer into line */
int newline = 1;           /* boolean to control reading a line */

int getaline(char s[], int lim);

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

    if (newline)
    {
        if (getaline(line, MAX_LINE) <= 0)
            return EOF;
        newline = 0;                       /* don't need another line */
    }

    /* skip space and horizontal tabs 
     */
    while ((s[0] = c = line[++lp]) == ' ' || c == '\t')
        ;

    if (c == '-' || c == '+')
    {
        /* need to decide if the plus or minus specifies
         * the sign of a number or is itself an operator
         */
        s[1] = c = line[++lp];          /* get next char */
        if (isdigit(c))                 /* is a sign */
        {
            s[2] = '\0';                    /* terminate string */
            i = 1;                          /* prep index into s */
        }
        else
        {
            lp--;
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
    {
        if (c == '\n' || c == '\0')  
        {
            newline = 1;                /* need a new line */
            lp = -1;                    /* reset pointer */
        }
        return c;                       /* must be an operator or variable */
    }

    /* collect integer part 
     */    
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[++lp]))
            ;
    /* collect fraction part 
     */    
    if (c == '.')
        while (isdigit(s[++i] = c = line[++lp]))
            ;
    s[i] = '\0';                        /* terminate string */
    
    if (c != '\n' || c != '\0')
         lp--; 

    return NUMBER;
}


/* Function
 *
 *    get line into s, return length
 *
 *    line is terminated by either '\n''\0' or just '\0' for line > lim
 *
 *    note: named function getaline to avoid conflict with getline
 *    library function
 *
 */
int getaline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

