/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 4.11 The C Preprocessor
 *
 * Exercise 4-14
 *
 *    Define a macro swap(t,x,y) that interchanges two arguments of
 *    type t. (Block structure will help)
 *
 */
#include <stdio.h>

#define swap(t, x, y)  { t c; c = x; x = y ; y = c; }

int main()
{
    char a = 'a';
    char b = 'b';

    swap(char, a, b);

    printf("a is now %c and b is now %c\n", a, b);

    return 0;
}

