#include <stdio.h>
#include <string.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.8 Increment and Decrement Operators
 *
 * Exercise 2-5
 *
 *    Write the function any(s1, s2), which returns the first location
 *    in the string s1 where any character from the string s2 occurs,
 *    or -1 if s1 contains no characters from s2.
 *
 */

#define TRUE  1
#define FALSE 0

int any(char s1[], char s2[]);

int main()
{

	char s00[] = "11100asdb1slkd22";
	char s01[] = "12aa";
	printf("%s%s%s%s%s => %d\n", "any(", s00 ,",", s01, ")", any(s00, s01));

	char s02[] = "11100asdb1slkd22";
	char s03[] = "";
	printf("%s%s%s%s%s => %d\n", "any(", s02 ,",", s03, ")", any(s02, s03));

	char s04[] = "11100asdb1slkd22";
	char s05[] = "2";
	printf("%s%s%s%s%s => %d\n", "any(", s04 ,",", s05, ")", any(s04, s05));


}

/* Function
 *
 *    Return the first location in the string s1 where any character
 *    from the string s2 occurs.
 * 
 */
int any(char s1[], char s2[])
{
	int i, j, k;

	j = -1;
	for (i = 0; s1[i] != '\0'; i++)
	{
		for(k = 0; s2[k] != '\0'; k++)
			if (s1[i] == s2[k])
				return i;
	}
	return j;
}
