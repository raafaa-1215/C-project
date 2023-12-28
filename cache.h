#pragma once
#include "date.h"

typedef enum {
    EARTHCACHE, 
    LETTERBOX, 
    MULTI, 
    PUZZLE, 
    TRADITIONAL,
    VIRTUAL,
    WEBCAM
} Kind;

typedef enum {
    MICRO, 
    SMALL, 
    REGULAR, 
    LARGE, 
    OTHER_SIZE,
    VIRTUAL_SIZE,
    NOT_CHOSEN
} Size;

typedef enum {
    AVAILABLE,
    DISABLED
} Status;

typedef struct cache {
    char code[11], 
         name[101], 
         state[21], 
         owner[51], 
         latitude[26],
         longitude[26];
    Kind kind;
    Size size;
    float difficulty,
          terrain;
    Status status;
    Date hidden_date;
    int founds,
        not_founds,
        favourites;
    char altitude[8];
} Cache; 

Cache cacheCreate(char code[], char name[], char state[], char owner[], char latitude[], char longitude[], Kind kind, Size size, float difficulty, float terrain, Status status, int year, int month, int day, int founds, int not_founds, int favourites, char altitude[]);
int loadCaches(char filename[], Cache array[], int maxLength);
void clearCache(Cache arrayOfCaches[], int arrayLength);