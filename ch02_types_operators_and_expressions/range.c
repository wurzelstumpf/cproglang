#include <stdio.h>
#include <limits.h>
#include <float.h>

/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 2.1 Data Types and Sizes
 *
 * Exercise 2-1
 *
 *    Write a program to determine the ranges of char, short, int and
 *    long variables, both signed and unsigned, by printing
 *    appropriate values from standard headers and by direct
 *    computation.  Harder if you compute them: determine the ranges
 *    of the various floating-point types.
 *
 * Notes
 *
 *    When including <math.h> need to link with math library during
 *    compilation. In this case add "-lm" to CFLAGS variable in
 *    Makefile.
 *
 *    The sizeof() operator takes a datatype and returns the number of
 *    char size storage units required for that type.  Thus the
 *    construct sizeof(char) is guaranteed to return 1. The number of
 *    bits in a char is given by CHAR_BITS in <limit.h>. The sizeof()
 *    operator returns an unsigned integral type denoted by size_t.
 *    Thus mulitplying the return value of sizeof() by CHAR_BITS gives
 *    the number of bits required for that type.
 *
 *    
 */ 

int main()
{
  /* Widths for formatting output
   */
  int w1 = 19;
  int w2 = 16;
  int w3 = 0;

  /* Number of bits in type char
   */
  unsigned char ch_bits = CHAR_BIT;

  /* 
   * signed   char
   * unsigned char
   */
  signed char s_char_min = SCHAR_MIN;
  signed char s_char_max = SCHAR_MAX;
  unsigned char u_char_min = 0;
  unsigned char u_char_max = UCHAR_MAX;

  printf("%*s: %*s: %*lu bits \n", w1, "unsigned char", w2, "size", w3, ch_bits * sizeof(unsigned char));
  printf("%*s: %*s: %*i --> %hhu \n", w1, "unsigned char", w2, "range", w3, u_char_min, u_char_max);
  printf("%*s: %*s: %*i + 1  =  %hhu \n", w1, "unsigned char", w2, "overflow", w3, u_char_max,  u_char_max + 1);
  printf("%*s: %*s: %*i - 1  =  %hhu \n", w1, "unsigned char", w2, "underflow", w3, u_char_min,  u_char_min - 1);

  printf("%*s: %*s: %*lu bits \n", w1, "signed char", w2, "size", w3, ch_bits * sizeof(signed char));
  printf("%*s: %*s: %*i --> %hhu \n", w1, "signed char", w2, "range", w3, s_char_min, s_char_max);
  printf("%*s: %*s: %*hhi + 1  =  %hhi \n", w1, "signed char", w2, " overflow", w3, s_char_max,  s_char_max + 1);
  printf("%*s: %*s: %*hhi - 1  =  %hhi \n", w1, "signed char", w2, "underflow", w3, s_char_min,  s_char_min - 1);


  /* 
   * signed   short
   * unsigned short
   */
  signed short s_short_min = SHRT_MIN;
  signed short s_short_max = SHRT_MAX;
  unsigned short u_short_min = 0;
  unsigned short u_short_max = USHRT_MAX;
    
  printf("%*s: %*s: %*lu bits \n", w1, "unsigned short", w2, "size", w3, ch_bits * sizeof(unsigned short));
  printf("%*s: %*s: %*i --> %hu \n", w1, "unsigned short", w2, "range", w3, u_short_min, u_short_max);
  printf("%*s: %*s: %*hu + 1  =  %hu \n", w1, "unsigned short", w2, " overflow", w3, u_short_max,  u_short_max + 1);
  printf("%*s: %*s: %*hu - 1  =  %hu \n", w1, "unsigned short", w2, "underflow", w3, u_short_min,  u_short_min - 1);
 
  printf("%*s: %*s: %*lu bits \n", w1, "signed short", w2, "size", w3, ch_bits * sizeof(signed short));
  printf("%*s: %*s: %*i --> %hu \n", w1, "signed short", w2, "range", w3, s_short_min, s_short_max);
  printf("%*s: %*s: %*hi + 1  =  %hi \n", w1, "signed short", w2, " overflow", w3, s_short_max,  s_short_max + 1);
  printf("%*s: %*s: %*hi - 1  =  %hi \n", w1, "signed short", w2, "underflow", w3, s_short_min,  s_short_min - 1);

  /*
   * signed   int
   * unsigned int
   */
  signed int s_int_min = INT_MIN;
  signed int s_int_max = INT_MAX;
  unsigned int u_int_min = 0;
  unsigned int u_int_max = UINT_MAX;
    
  printf("%*s: %*s: %*lu bits \n", w1, "unsigned int", w2, "size", w3, ch_bits * sizeof(unsigned int));
  printf("%*s: %*s: %*i --> %u \n", w1, "unsigned int", w2, "range", w3, u_int_min, u_int_max);
  printf("%*s: %*s: %*u + 1  =  %u \n", w1, "unsigned int", w2, " overflow", w3, u_int_max,  u_int_max + 1);
  printf("%*s: %*s: %*u - 1  =  %u \n", w1, "unsigned int", w2, "underflow", w3, u_int_min,  u_int_min - 1);

  printf("%*s: %*s: %*lu bits \n", w1, "signed int", w2, "size", w3, ch_bits * sizeof(signed int));
  printf("%*s: %*s: %*i --> %i \n", w1, "signed int", w2, "range", w3, s_int_min, s_int_max);
  printf("%*s: %*s: %*i + 1  =  %i \n", w1, "signed int", w2, " overflow", w3, s_int_max,  s_int_max + 1);
  printf("%*s: %*s: %*i - 1  =  %i \n", w1, "signed int", w2, "underflow", w3, s_int_min,  s_int_min - 1);

  /*
   * signed   long
   * unsigned long
   */
  signed long s_long_min = LONG_MIN;
  signed long s_long_max = LONG_MAX;
  unsigned long u_long_min = 0;
  unsigned long u_long_max = ULONG_MAX;
    
  printf("%*s: %*s: %*lu bits \n", w1, "unsigned long", w2, "size", w3, ch_bits * sizeof(unsigned long));
  printf("%*s: %*s: %*li --> %lu \n", w1, "unsigned long", w2, "range", w3, u_long_min, u_long_max);
  printf("%*s: %*s: %*lu + 1  =  %lu \n", w1, "unsigned long", w2, " overflow", w3, u_long_max,  u_long_max + 1);
  printf("%*s: %*s: %*lu - 1  =  %lu \n", w1, "unsigned long", w2, "underflow", w3, u_long_min,  u_long_min - 1);

  printf("%*s: %*s: %*lu bits \n", w1, "signed long", w2, "size", w3, ch_bits * sizeof(signed long));
  printf("%*s: %*s: %*li --> %li \n", w1, "signed long", w2, "range", w3, s_long_min, s_long_max);
  printf("%*s: %*s: %*li + 1  =  %li \n", w1, "signed long", w2, " overflow", w3, s_long_max,  s_long_max + 1);
  printf("%*s: %*s: %*li - 1  =  %li \n", w1, "signed long", w2, "underflow", w3, s_long_min,  s_long_min - 1);

  /*
   * signed   long long
   * unsigned long long
   */
  signed long long s_llong_min = LLONG_MIN;
  signed long long s_llong_max = LLONG_MAX;
  unsigned long long u_llong_min = 0;
  unsigned long long u_llong_max = ULLONG_MAX;
    
  printf("%*s: %*s: %*lu bits \n", w1, "unsigned long long", w2, "size", w3, ch_bits * sizeof(unsigned long long));
  printf("%*s: %*s: %*lli --> %llu \n", w1, "unsigned long long", w2, "range", w3, u_llong_min, u_llong_max);
  printf("%*s: %*s: %*llu + 1  =  %llu \n", w1, "unsigned long long", w2, " overflow", w3, u_llong_max,  u_llong_max + 1);
  printf("%*s: %*s: %*llu - 1  =  %llu \n", w1, "unsigned long long", w2, "underflow", w3, u_llong_min,  u_llong_min - 1);

  printf("%*s: %*s: %*lu bits \n", w1, "signed long long", w2, "size", w3, ch_bits * sizeof(signed long long));
  printf("%*s: %*s: %*lli --> %lli \n", w1, "signed long long", w2, "range", w3, s_llong_min, s_llong_max);
  printf("%*s: %*s: %*lli + 1  =  %lli \n", w1, "signed long long", w2, " overflow", w3, s_llong_max,  s_llong_max + 1);
  printf("%*s: %*s: %*lli - 1  =  %lli \n", w1, "signed long long", w2, "underflow", w3, s_llong_min,  s_llong_min - 1);


  /*
   * float
   * double
   * long double
   */
  float float_min = FLT_MIN;
  float float_max = FLT_MAX;
  float float_epsilon = FLT_EPSILON;   /* smallest value of x such that 1.0 + x != 1.0 */
  double double_min = DBL_MIN;
  double double_max = DBL_MAX;
  double double_epsilon = DBL_EPSILON;    /* smallest value of x such that 1.0 + x != 1.0 */
  long double ldouble_min = LDBL_MIN;
  long double ldouble_max = LDBL_MAX;
  long double ldouble_epsilon = LDBL_EPSILON;     /* smallest value of x such that 1.0 + x != 1.0 */
    
  printf("%*s: %*s: %*lu bits \n", w1, "float", w2, "size", w3, ch_bits * sizeof(float));
  printf("%*s: %*s: %*e \n", w1, "float", w2, "  epsilon", w3, float_epsilon);
  printf("%*s: %*s: %*g --> %g \n", w1, "float", w2, "pos range", w3, float_min, float_max);
  printf("%*s: %*s: %*e + 0.000001e+38  =  %f \n", w1, "float", w2, " pos overflow", w3, float_max,  float_max + 0.000001e+38F);
  printf("%*s: %*s: %*e - 0.000001e-38  =  %f \n", w1, "float", w2, " pos underflow", w3, float_min,  float_min - 0.000001e-38F);
  printf("%*s: %*s: %*g --> %g \n", w1, "float", w2, "neg range", w3, -float_max, -float_min);
  printf("%*s: %*s: %*e - 0.000001e+38  =  %f \n", w1, "float", w2, " neg overflow", w3, -float_max,  -float_max - 0.000001e+38F);
  printf("%*s: %*s: %*e + 0.000001e-38  =  %f \n", w1, "float", w2, " neg underflow", w3, -float_min,  -float_min + 0.000001e-38F);

  printf("%*s: %*s: %*lu bits \n", w1, "double", w2, "size", w3, ch_bits * sizeof(double));
  printf("%*s: %*s: %*e \n", w1, "double", w2, "  epsilon", w3, double_epsilon);
  printf("%*s: %*s: %*g --> %g \n", w1, "double", w2, "pos range", w3, double_min, double_max);
  printf("%*s: %*s: %*e + 0.000001e+308  =  %e \n", w1, "double", w2, " pos overflow", w3, double_max,  double_max + 0.000001e+308);
  printf("%*s: %*s: %*e - 0.000001e-308  =  %e \n", w1, "double", w2, " pos underflow", w3, double_min,  double_min - 0.000001e-308);
  printf("%*s: %*s: %*g --> %g \n", w1, "double", w2, "neg range", w3, -double_max, -double_min);
  printf("%*s: %*s: %*e - 0.000001e+308  =  %e \n", w1, "double", w2, " neg overflow", w3, -double_max,  -double_max - 0.000001e+308);
  printf("%*s: %*s: %*e + 0.000001e-308  =  %e \n", w1, "double", w2, " neg underflow", w3, -double_min,  -double_min + 0.000001e-308);

  printf("%*s: %*s: %*lu bits \n", w1, "long double", w2, "size", w3, ch_bits * sizeof(long double));
  printf("%*s: %*s: %*Le \n", w1, "long double", w2, "  epsilon", w3, ldouble_epsilon);
  printf("%*s: %*s: %*Lg --> %Lg \n", w1, "long double", w2, "pos range", w3, ldouble_min, ldouble_max);
  printf("%*s: %*s: %*Le + 0.000001e+4932  =  %Le \n", w1, "long double", w2, " pos overflow", w3, ldouble_max, ldouble_max + 0.000001e+4932L);
  printf("%*s: %*s: %*Le - 0.000001e-4932  =  %Le \n", w1, "long double", w2, " pos underflow", w3, ldouble_min, ldouble_min - 0.000001e-4932L);
  printf("%*s: %*s: %*Lg --> %Lg \n", w1, "long double", w2, "neg range", w3, -ldouble_max, -ldouble_min);
  printf("%*s: %*s: %*Le - 0.000001e+4932  =  %Le \n", w1, "long double", w2, " neg overflow", w3, -ldouble_max, -ldouble_max - 0.000001e+4932L);
  printf("%*s: %*s: %*Le + 0.000001e-4932  =  %Le \n", w1, "long double", w2, " neg underflow", w3, -ldouble_min, -ldouble_min + 0.000001e-4932L);

  return 0;
}
