/*
-----------------------------------------------------------------------------------
Laboratoire : Labo09 - Structure et Pointeurs
Fichier     : main.c
Auteur(s)   : Emmanuel Janssens, Doran Kayoumi
Date        : 22.05.2019
But         : Mettre en place un programme simple afin de mettre en pratique l'utilisation
              des pointeurs et structs
Remarque(s) : -
Compilateur : gcc <8.3.0>
-----------------------------------------------------------------------------------
 */

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

/**
 * @brief Display a date
 *
 * @param date
 */
void displayDate(Date *date);

/**
 * @brief Increase a date
 *
 * @param date
 */
void nextDay(Date *date);

/**
 * @brief Decrease a date
 *
 * @param date
 */
void prevDay(Date *date);

/**
 * @brief Loop through a collection of dates
 *
 * @param dates
 * @param size
 * @param action function that accepts the pointer of a Date as an argument and returns nothing
 */
void loopDates(Date *dates, size_t size, void (*action)(Date *));

/**
 * @brief Get the number of days in a month
 *
 * @param month
 * @param year
 * @return the number of days of the month
 */
unsigned getMonthLength(Mois month, unsigned year);

/**
 * @brief Check if a given year is leap
 *
 * @param year to check
 * @return true if it's a leap year otherwise false
 */
bool isLeapYear(unsigned year);

/**
 * @brief Check if lhs date is lower than the rhs one
 *
 * @param lhs 
 * @param rhs 
 * @return true if lhs < rhs otherwise false
 */
bool lowerThan(Date lhs, Date rhs);

/**
 * @brief Check if lhs date is greater than the rhs one
 * 
 * @param lhs 
 * @param rhs 
 * @return true if lhs > rhs otherwise false
 */
bool greaterThan(Date lhs, Date rhs);

/**
 * @brief Perform a selection sort on a collection of Dates
 * 
 * @param date pointer to a collection of Dates
 * @param size of the collection
 * @param comp Binary function that accepts two elements in the as arguments, and reeturns a bool
 */
void sort(Date *date, int size, bool (*comp)(Date, Date));

/**
 * @brief Swap two dates
 * 
 * @param lhs 
 * @param rhs 
 */
void swap(Date *lhs, Date *rhs);

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
    sort(tab, 3, greaterThan);
    loopDates(tab, 3, displayDate);

    printf("\n");
    loopDates(tab, 3, prevDay);
    loopDates(tab, 3, displayDate);


    return 0;
}

void swap(Date *lhs, Date *rhs) {
    Date temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

bool lowerThan(Date lhs, Date rhs) {

    if (lhs.year < rhs.year) return true;

    if (lhs.year == rhs.year) {

        if (lhs.month < rhs.month) return true;

        if (lhs.month == rhs.month) {
            if (lhs.day < rhs.day) return true;
        }
    }

    return false;
}

bool greaterThan(Date lhs, Date rhs) {
    return lowerThan(rhs, lhs);
}

void sort(Date *date, int size, bool (*comp)(Date, Date)) {
    int to_swap;
    for (int i = 0; i < size - 1; i++) {
        to_swap = i;
        for (int j = i + 1; j < size; j++) {
            if (comp(date[j], date[to_swap])) {
                to_swap = j;
            }
        }
        swap(&date[to_swap], &date[i]);
    }
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
