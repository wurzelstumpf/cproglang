/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.5 Character Pointers and Functions
 *
 * Exercise 5-3
 *
 *    Write a pointer version of the function strcat that we showed in
 *    Chapter 2: strcat(s, t) copies the string t to the end of s.
 *
 */
#include <stdio.h>

#define MAX_SIZE 1000

void strcat2(char *, char *);

int main()
{
    char s[MAX_SIZE] = { 's', 't', 'a', 'r', 't', '\0'};
    char *t = " end";

    printf("strcat2(%s, %s) results in", s, t);
    strcat2(s, t);
    printf(" '%s'\n", s);

    s[0] = '\0';
    t = "hi";    
    printf("strcat2(%s, %s) results in", s, t);
    strcat2(s, t);
    printf(" '%s'\n", s);

    s[0] = 'h';
    s[1] = 'i';
    s[2] = '\0';
    t = "";    
    printf("strcat2(%s, %s) results in", s, t);
    strcat2(s, t);
    printf(" '%s'\n", s);


    return 0;
}

/* strcat - concatenate t to end of s; s must be big enough 
 */
void strcat2(char *s, char *t)
{
    while (*s != '\0')
        s++;                /* move to end of s */

    while ((*s++ = *t++) != '\0')
        ;
}
