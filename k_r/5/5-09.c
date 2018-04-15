/*
 * Rewrite the routines day_of_year and month_day with
 * pointers instead of indexing.
 */

#include <stdio.h>

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
  int i, leap;

  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

  printf("%d\n", *(*daytab + leap) + month);

  if (month > 13 || day > *(*daytab + leap) + month) {
    printf("Invalid date %d-%d-%d\n", year, month, day);
    return -1;
  }

  for (i = 1; i < month; i++)
    day += *(*daytab + leap) + i;
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;

  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

  if (yearday > (leap ? 364 : 365)) {
    printf("Invalid yearday %d\n", yearday);
  } else {
    for (i = 1; yearday > *(*daytab + leap) + i; i++)
      yearday -= *(*daytab + leap) + i;
    *pmonth = i;
    *pday = yearday;
  }
}

int main() {
  // happy paths
  printf("%d\n", day_of_year(1979, 3, 1)); // 60
  printf("%d\n", day_of_year(1980, 3, 1)); // 61

  int month;
  int day;

  month_day(1979, 60, &month, &day);
  printf("%d-%d\n", month, day); // 3-1

  month_day(1980, 60, &month, &day);
  printf("%d-%d\n", month, day); // 2-29

  // unhappy paths
  printf("%d\n", day_of_year(1979, 32, 1)); // invalid
  printf("%d\n", day_of_year(1979, 3, 32)); // invalid


  month_day(1979, 366, &month, &day); // invalid
  month_day(1980, 365, &month, &day); // invalid
}

