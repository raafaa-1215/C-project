#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "date.h"

Date dateCreate(int year, int month, int day) {
    Date date;
    
    date.year = year;
    date.month = month;
    date.day = day;

    return date;
}