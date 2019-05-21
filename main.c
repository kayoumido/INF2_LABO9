#include <stdio.h>

typedef enum {
    JAN, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC
} Mois;

typedef struct {
    unsigned day;
    Mois month;
    unsigned year;
} Date;

//display single date
void printDate(Date date)
{
    printf("%02d/%02d/%d\n",date.day,date.month+1,date.year);
}

//display array of dates
void printDates(Date* date,int size)
{
    for(int i = 0; i < size; i++)
    {
        printDate(*(date+i));
    }
}

int main() {

    Date tab[] = {{1,  JAN, 2013},
                  {21, MAY, 2019},
                  {28, FEB, 2002}};
    
    Date date = {28,JUN,2019};
    printDate(date);
    printDates(tab,3);

    return 0;
}