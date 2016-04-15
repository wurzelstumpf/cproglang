/* The C Programming Language, Kernighan and Ritchie, 2nd Edition 1988
 *
 * 5.9 Pointers vs. Multi-dimensional Arrays
 *
 * Exercise 5-9
 *
 *    Rewrite the routines day_of_year and month_day with pointers instead of
 *    indexing.
 *
 * Notes
 *
 *    This is the code from p111 to p112
 */
#include <stdio.h>

static char daytab[][13] =
{
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
        
/* main program
 */
int main()
{
    /* note that the variables year, month and day are used by both
     * the day_of_year and month_day functions below
     */
    int year, month, day, yearday;

    /* --------------------------------------------------------------------- */
    year = 2000;
    month = 1;
    day = 1;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month, day));

    month = 12;
    day = 31;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month, day));


    yearday = 1;
    month_day(year, yearday, &month, &day);
    printf("year: %4i  yearday: %03i  month: %02i  day: %02i\n",
           year, yearday, month, day);
        
    yearday = 31;
    month_day(year, yearday, &month, &day);
    printf("year: %4i  yearday: %03i  month: %02i  day: %02i\n",
           year, yearday, month, day);
        
    yearday = 32;
    month_day(year, yearday, &month, &day);
    printf("year: %4i  yearday: %03i  month: %02i  day: %02i\n",
           year, yearday, month, day);
        
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    year = 2016;
    month = 1;
    day = 1;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month,day));

    month = 12;
    day = 31;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month,day));

    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    year = 2017;
    month = 1;
    day = 1;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month, day));

    month = 12;
    day = 31;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month, day));
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    year = -120;
    month = 18;
    day = 115;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month, day));

    month = 0;
    day = -31;
    printf("year: %4i  month: %02i  day: %02i  %12s: %i\n",
           year, month, day, "day of year", day_of_year(year, month, day));

    yearday = 367;
    month_day(year, yearday, &month, &day);
    printf("year: %4i  yearday: %03i  month: %02i  day: %02i\n",
           year, yearday, month, day);
        

    yearday = 0;
    month_day(year, yearday, &month, &day);
    printf("year: %4i  yearday: %03i  month: %02i  day: %02i\n",
           year, yearday, month, day);
        
/* --------------------------------------------------------------------- */

    return 0;
}

/* function: validate year returns 1 if valid, 0 otherwise
 */
int valid_year(int y)
{
    return (y >= 0) ? 1: 0;
}


/* function: validate month returns 1 if valid, 0 otherwise
 */
int valid_month(int m)
{
    return (m >= 1 && m <= 12) ? 1: 0;
}


/* function: validate month day returns 1 if valid, 0 otherwise
 */
int valid_monthday(int d)
{
    return (d >= 1 && d <= 31) ? 1: 0;
}

/* function: validate year day returns 1 if valid, 0 otherwise
 */
int valid_yearday(int d)
{
    return (d >= 1 && d <= 366) ? 1: 0;
}


/* function: isleap returns 1 for true, 0 otherwise
 */
int isleap(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}


/* function: find day of year
 *           return the day of year either 1-365 or 1-366 for leap years
 *                  or -1 if year, month or day is invalid
 */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (!valid_year(year) || !valid_month(month) || !valid_monthday(day))
        return -1;
    leap = isleap(year);
    for (i = 1; i < month; i++)
        day += (*((*(daytab + leap)) + i));
    return day;
}

/* function: set month and day from given day of year and year
 *                  or to -1 if year or yearday is invalid
 */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (!valid_year(year) || !valid_yearday(yearday))
        *pmonth = *pday = -1;
    else
    {
        leap = isleap(year);
        for (i = 1; yearday > (*(*((daytab +leap)) + i)); i++)
            yearday -= (*((*(daytab + leap)) + i));
        *pmonth = i;
        *pday = yearday;
    }
}

