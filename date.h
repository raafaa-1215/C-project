#pragma once

typedef struct date {
    int day, month, year;
} Date;

Date dateCreate(int day, int month, int year);
void datePrint(Date date);
