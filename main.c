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

const char* correspondance_Mois[12] = {"JAN","FEB","MAR","APR","MAY","JUN","AUG","SEP","OCT","NOV","DEC"};

//printDate
//nextDay
//prevDay
//incrementAllDay
//sortDates

//display single date
void printDate(Date date)
{
    printf("%02d/%s/%d\n",date.day,correspondance_Mois[date.month],date.year);
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