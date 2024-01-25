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
         state[26], 
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
// comando LOAD
int loadCaches(char filename[], Cache array[], int maxLength);
// comando CLEAR
void clearCache(Cache *arrayOfCaches, int arrayLength);
// comando LIST
void listCache(Cache *arrayOfCaches, int arrayLength);
// comando FOUNDP
void listFOUNDP(Cache *arrayOfCaches, int arrayLength);
// comando SEARCH
int searchCache(char *cacheCode, Cache *arrayOfCaches, int arrayLength);
void printSearchCache(Cache *cacheSearched);
// comando EDIT
int findEditCache(char *cacheCode, Cache *arrayOfCaches, int arrayLength);
void editCache(Cache *cacheToEdit);
// comando AGE
void getCacheAge(Cache *arrayOfCaches, int arrayLength);
// comando SORT
void cacheSortByAltitude(Cache *arrayOfCaches, int arrayLength);
void cacheSortByState(Cache *arrayOfCaches, int arrayLength);
void cacheSortByDate(Cache *arrayOfCaches, int arrayLength);
void sortCache(Cache *cacheToSort, int arrayLength);
// comando CENTER
void centerLatitude(Cache *arrayOfCaches, int arrayLength);
void centerLongitude(Cache *arrayOfCaches, int arrayLength);
// comando STATEC
void getCacheStateC(Cache *arrayOfCaches, int arrayLength);
// comando M81
void getCacheM81(Cache *arrayOfCaches, int arrayLength);
// comando SAVE
bool existsFilename(char *filenameToSave);
bool saveCachesToFile(char *fileNameToSave, Cache *arrayOfCaches, int arrayLength);