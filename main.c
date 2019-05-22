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

/**
 * @brief verifie si une date est plus petite qu'une autre
 * @param lhs 
 * @param rhs 
 * @return true si lhs < rhs
 * @return false si lhs == rhs ou lhs > rhs
 */
bool plusPetit(Date lhs, Date rhs);

/**
 * @brief verifie si une date est plus grande qu'une autre
 * 
 * @param lhs 
 * @param rhs 
 * @return true si lhs > rhs
 * @return false si lhs == rhs ou lhs < rhs
 */
bool plusGrand(Date lhs,Date rhs);

/**
 * @brief effectue un tri par sélection sur un tableau de date
 * 
 * @param date pointeur vers la collection de date
 * @param size taille du tableau de date
 * @param fct pointeur vers fonction qui permet d'exécuter les comparaisons
 */
void trier(Date* date,int size,bool (*fct)(Date,Date));

/**
 * @brief echange deux elements
 * 
 * @param lhs 
 * @param rhs 
 */
void swap(Date* lhs, Date*rhs);

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


void swap(Date* lhs, Date*rhs)
{
    Date temp = *lhs;
    *lhs=*rhs;
    *rhs=temp;
}
//retourne la date la plus petite
bool plusPetit(Date lhs,Date rhs)
{
    if(lhs.year == rhs.year&& lhs.month == rhs.month  &&  lhs.day == rhs.day)
        return false;
    
    if(lhs.year < rhs.year || lhs.month < rhs.month || lhs.day < rhs.day)
        return true;
    
    return false;
}

//retourne la date la plus grande
bool plusGrand(Date lhs,Date rhs)
{
    return !plusPetit(lhs,rhs);
}



//POINTEUR SUR FONCTION 
void trier(Date* date,int size,bool (*fct)(Date,Date))
{    
    int to_swap;
    for (int i = 0; i < size - 1; i++)
    {
        to_swap = i;
        for (int j = i + 1; j < size; j++)
        {
            if (fct(date[j], date[to_swap]))
            {
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
