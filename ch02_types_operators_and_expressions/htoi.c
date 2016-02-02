#include <stdio.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.7 Type Conversions
 *
 * Exercise 2-3
 *
 *    Write the function htoi(s) which converts a string of
 *    hexadecimal digits (including an optional 0x or 0X) into its
 *    equivalent integer value.  The allowable digits are 0 through 9,
 *    a through f, and A through F.
 *
 * Notes
 *
 */

int htoi(char s[]);

int main()
{
	char s00[] = "0";
	char s01[] = "1";
	char s02[] = "2";
	char s03[] = "3";
	char s04[] = "4";
	char s05[] = "5";
	char s06[] = "6";
	char s07[] = "7";
	char s08[] = "8";
	char s09[] = "9";
	char s10[] = "a";
	char s11[] = "b";
	char s12[] = "c";
	char s13[] = "d";
	char s14[] = "e";
	char s15[] = "f";

	printf("%12s   %d\n", s00, htoi(s00));
	printf("%12s   %d\n", s01, htoi(s01));
	printf("%12s   %d\n", s02, htoi(s02));
	printf("%12s   %d\n", s03, htoi(s03));
	printf("%12s   %d\n", s04, htoi(s04));
	printf("%12s   %d\n", s05, htoi(s05));
	printf("%12s   %d\n", s06, htoi(s06));
	printf("%12s   %d\n", s07, htoi(s07));
	printf("%12s   %d\n", s08, htoi(s08));
	printf("%12s   %d\n", s09, htoi(s09));
	printf("%12s   %d\n", s10, htoi(s10));
	printf("%12s   %d\n", s11, htoi(s11));
	printf("%12s   %d\n", s12, htoi(s12));
	printf("%12s   %d\n", s13, htoi(s13));
	printf("%12s   %d\n", s14, htoi(s14));
	printf("%12s   %d\n", s15, htoi(s15));

	char s16[] ="0x34";
	printf("%12s   %d\n", s16, htoi(s16));

	char s17[] ="0X34";
	printf("%12s   %d\n", s17, htoi(s17));

	char s18[] ="e3a";
	printf("%12s   %d\n", s18, htoi(s18));

	char s19[] ="0xe3a";
	printf("%12s   %d\n", s19, htoi(s19));

	char s20[] ="abcdef";
	printf("%12s   %d\n", s20, htoi(s20));

	char s21[] ="ABCDEF";
	printf("%12s   %d\n", s21, htoi(s21));

}

/* Function
 *
 *    Converts a string of hexadecimal digits (including an optional
 *    0x or 0X) into its equivalent integer value.  The allowable
 *    digits are 0 through 9, a through f, and A through F.
 * 
 */
int htoi(char s[])
{
  int i;
  int d = 0;
  short int n = -1;

  for (i = 0; s[i] != '\0'; i++)
  {
	  if (s[i] >= '0' && s[i] <= '9')
		  n =  s[i] - '0';
	  else if (s[i] >= 'a' && s[i] <= 'f')
		  n = 10 + (s[i] - 'a');
	  else if (s[i] >= 'A' && s[i] <= 'F')
		  n = 10 + (s[i] - 'A');
	  else if (i == 1 && (s[i] == 'x' || s[i] == 'X') && s[0] == '0')
	  {
		  d = 0;
		  n = 0;
	  }
	  else
		  n = -1;    /* skip invalid hex chars */

	  if (n <= 15 && n >= 0)
		  d = d * 16  + n;
  }
  return d;
}
