#include <stdio.h>
#include <string.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.8 Increment and Decrement Operators
 *
 * Exercise 2-4
 *
 *    Write an alternate version of squeeze(s1, s2) that deletes each
 *    character in s1 that matches any character in the string s2.
 *
 */

#define TRUE  1
#define FALSE 0

void squeeze(char s1[], char s2[]);

int main()
{

	char buffer[1000] = "";

	char s00[] = "11100asdb1slkd22";
	char s01[] = "12aa";

	snprintf(buffer, sizeof(buffer), "%s%s%s%s%s => ", "squeeze(", s00 ,",", s01, ")");
	squeeze(s00, s01);
	printf("%s %s\n", buffer, s00);

}

/* Function
 *
 *    Delete each character in s1 that matches any character in s2
 * 
 */
void squeeze(char s1[], char s2[])
{
	int i, j, k;

	for (j = i = 0; s1[i] != '\0'; i++)
	{
		unsigned short match = FALSE;
		for(k = 0; s2[k] != '\0'; k++)
			if (s1[i] == s2[k])
				match = TRUE;
		if (!match)
			s1[j++] = s1[i];
	}
	s1[j] = '\0';
}
