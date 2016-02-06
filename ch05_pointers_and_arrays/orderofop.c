/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.5 Character Pointers and Functions
 *
 * Exploration
 *
 *    Just exploring order of operations when operators * ++ --
 *    are applied to pointers
 *
 */
#include <stdio.h>

void printdiv(int);

int main()
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int digit[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    char *cp;
    char c;
    int i;
    int w;
    int *ip;
    int w1 = 18;

    w = printf("digit array is '");
    for(i = 0; i <= 9; i++, w++)
        printf("%i", digit[i]);
    printf("'\n");
    printdiv(w);

    ip = digit;
    w = printf("op is %*s and *ip is '%i'\n", w1, "ip = digit", *ip);
    
    ip = &digit[0];
    w = printf("op is %*s and *ip is '%i'\n", w1, "ip = &digit[0]", *ip);
    
    ip++;
    w = printf("op is %*s and *ip is '%i'\n", w1, "ip++", *ip);
    
    ++ip;
    w = printf("op is %*s and *ip is '%i'\n", w1, "++ip", *ip);
    
    ip--;
    w = printf("op is %*s and *ip is '%i'\n", w1, "ip--", *ip);
    
    --ip;
    w = printf("op is %*s and *ip is '%i'\n", w1, "--ip", *ip);
    
    i = *ip++;
    w = printf("op is %*s and *ip is '%i' and i is '%i'\n", w1, "i = *ip++", *ip, i);
    
    i = ++*ip;
    w = printf("op is %*s and *ip is '%i' and i is '%i'\n", w1, "i = ++*ip", *ip, i);
    
    i = *++ip;
    w = printf("op is %*s and *ip is '%i' and i is '%i'\n", w1, "i = *++ip", *ip, i);
    
    i = ++(*ip);
    w = printf("op is %*s and *ip is '%i' and i is '%i'\n", w1, "i = ++(*ip)", *ip, i);
    
    i = *ip--;
    w = printf("op is %*s and *ip is '%i' and i is '%i'\n", w1, "i = *ip--", *ip, i);
    
    i = --*ip;
    w = printf("op is %*s and *ip is '%i' and i is '%i'\n", w1, "i = --*ip", *ip, i);
    
    i = --(*ip);
    w = printf("op is %*s and *ip is '%i' and i is '%i'\n", w1, "i = --(*ip)", *ip, i);
    
    printdiv(--w);
    
    cp = &alphabet[0];
    w = printf("op is %*s and *cp is '%c'\n", w1, "cp = &alphabet[0]", *cp);

    cp = alphabet;
    w = printf("op is %*s and *cp is '%c'\n", w1, "cp = alphabet", *cp);

    cp++;
    w = printf("op is %*s and *cp is '%c'\n", w1, "cp++", *cp);

    ++cp;
    w = printf("op is %*s and *cp is '%c'\n", w1, "++cp", *cp);

    cp--;
    w = printf("op is %*s and *cp is '%c'\n", w1, "cp--", *cp);

    --cp;
    w = printf("op is %*s and *cp is '%c'\n", w1, "--cp", *cp);

    c = *cp++;
    w = printf("op is %*s and *cp is '%c' and c is '%c'\n", w1, "c = *cp++", *cp, c);

    /* causes core dump */
    /* c = ++*cp; */
    /* printf("op is %*s and *cp is '%c' and c is '%c'\n", w1, "c = ++*cp", *cp, c); */
    w = printf("op is %*s !!! causes core dump\n", w1, "c = ++*cp");

    c = *++cp;
    printf("op is %*s and *cp is '%c' and c is '%c'\n", w1, "c = *++cp", *cp, c);

    c = *cp--;
    w = printf("op is %*s and *cp is '%c' and c is '%c'\n", w1, "c = *cp--", *cp, c);

   /* causes core dump */
    /* c = --*cp; */
    /* printf("op is %*s and *cp is '%c' and c is '%c'\n", w1, "c = --*cp", *cp, c); */
    w = printf("op is %*s !!! causes core dump\n", w1, "c = --*cp");

    printdiv(--w);

    printf("Morale of tale appears to be that; \n" \
           "    ++*var *++var --*var and *--var \n" \
           "should be avoided.\n");
    return 0;
}

/* printdiv - print a divider */
void printdiv(int w)
{
    int i;
    char c = '-';

    for (i = 0; i < w; i++)
        printf("%c", c);
    printf("\n");
}
