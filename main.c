#include <stdio.h>
#include <stdbool.h>

typedef enum {
    JAN, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC
} Mois;

const char *MONTH_TEXT[12] = {
        "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
        "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

const Mois FISRT_MONTH = JAN;
const Mois LAST_MONTH = DEC;

typedef struct {
    unsigned day;
    Mois month;
    unsigned year;
} Date;


void displayDate(Date *date);

void nextDay(Date *date);

void prevDay(Date *date);

void loopDates(Date *dates, size_t size, void (*action)(Date *));

unsigned getMonthLength(Mois month, unsigned year);

bool isLeapYear(unsigned year);


int main() {

    Date tab[] = {{1,  JAN, 2013},
                  {21, MAY, 2019},
                  {28, FEB, 2002}};

    loopDates(tab, 3, displayDate);

    printf("\n");
    loopDates(tab, 3, nextDay);
    loopDates(tab, 3, displayDate);

    printf("\n");
    loopDates(tab, 3, prevDay);
    loopDates(tab, 3, displayDate);

    printf("\n");
    loopDates(tab, 3, prevDay);
    loopDates(tab, 3, displayDate);


    return 0;
}

unsigned getMonthLength(Mois month, unsigned year) {
    unsigned totalDaysInMonth;

    if (month == FEB) {
        if (isLeapYear(year)) {
            totalDaysInMonth = 29;
        } else {
            totalDaysInMonth = 28;
        }
    } else if ((((unsigned) month + 1) % 2 == 0 && month < JUL) ||
               (((unsigned) month + 1) % 2 == 1 && month > JUL)) {
        totalDaysInMonth = 30;
    } else {
        totalDaysInMonth = 31;
    }

    return totalDaysInMonth;
}

bool isLeapYear(unsigned year) {
    return ((year % 4 == 0) && year % 100 != 0) || year % 400 == 0;;
}

void nextDay(Date *date) {
    ++date->day;

    if (date->day > getMonthLength(date->month, date->year)) {
        date->day = 1;

        ++date->month;

        if (date->month > LAST_MONTH) {
            date->month = FISRT_MONTH;
            ++date->year;
        }
    }
}

void prevDay(Date *date) {
    --date->day;

    if (date->day == 0) {
        --date->month;
        date->day = getMonthLength(date->month, date->year);

        // if the FIRST_MONTH was decreased, the value will loop back to the max value of an unsigned
        if (date->month > LAST_MONTH) {
            --date->year;
            date->month = LAST_MONTH;
        }
    }
}

void loopDates(Date *dates, size_t size, void (*action)(Date *)) {
    for (size_t i = 0; i < size; ++i) {
        action(&dates[i]);
    }
}

void displayDate(Date *date) {
    printf("%02d/%s/%d\n", date->day, MONTH_TEXT[date->month], date->year);
}
