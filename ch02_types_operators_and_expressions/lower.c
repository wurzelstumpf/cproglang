#include <stdio.h>
#include <limits.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.11 Conditional Expressions
 *
 * Exercise 2-10
 *
 *    Rewrite the function lower (on p43), which converts upper case
 *    letters to lower case, with a condition expression instead of
 *    if-else.
 *
 */

int lower(int c);
void test(char s[]);

int main()
{
    char lo[] = "abcdefghijklmnopqrstuv!@#$%^&*()_+{}\":?><,./;'[]=-|";
    char up[] = "ABCDEFGHIJKLMNOPQRSTUV!@#$%^&*()_+{}\":?><,./;'[]=-|";

    test(lo);
    test(up);

}

/* Function
 *
 *    Test the function lower on the given string
 *
 */
void test(char s[])
{
    int i;
    printf("%s --> ", s);
    for (i = 0; s[i] != '\0'; i++)
	printf("%c", lower(s[i]));
    printf("\n");
}

/* Function
 *
 *    Convert upper case letters to lower case
 *
 */
int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
