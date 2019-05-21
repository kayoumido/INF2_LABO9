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

int main() {

    Date tab[] = {{1,  JAN, 2013},
                  {21, MAY, 2019},
                  {28, FEB, 2002}};
    
    return 0;
}