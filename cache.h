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
    VIRTUAL,
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