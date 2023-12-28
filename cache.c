#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "date.h"
#include "cache.h"

#define MAX_CACHE 2001

Cache cacheCreate(char code[], char name[], char state[], char owner[], char latitude[], char longitude[], Kind kind, Size size, float difficulty, float terrain, Status status, int year, int month, int day, int founds, int not_founds, int favourites, char altitude[]) {
    Cache cache;

    strncpy(cache.code, code, sizeof(cache.code) - 1);
    strncpy(cache.name, name, sizeof(cache.name) - 1);
    strncpy(cache.state, state, sizeof(cache.state) - 1);
    strncpy(cache.owner, owner, sizeof(cache.owner) - 1);
    strncpy(cache.latitude, latitude, sizeof(cache.latitude) - 1);
    strncpy(cache.longitude, longitude, sizeof(cache.longitude) - 1);
    cache.kind = kind;
    cache.size = size;
    cache.difficulty = difficulty;
    cache.terrain = terrain;
    cache.status = status;
    cache.hidden_date = dateCreate(year, month, day);
    cache.founds = founds;
    cache.not_founds = not_founds;
    cache.favourites = favourites;
    strncpy(cache.altitude, altitude, sizeof(cache.altitude) - 1);

    return cache;
}

int loadCaches(char filename[], Cache array[], int maxLength) {
    FILE* stream = fopen(filename, "r");

    int count = 0;
    char line[MAX_CACHE];

    fgets(line, MAX_CACHE, stream);
    while (fgets(line, MAX_CACHE, stream))
    {
        if(count >= maxLength) break;

        char* tmp = strdup(line);
        
        char** tokens = splitString(tmp, 16, ";");
        
        Kind kind;
        switch (tokens[6][0])
        {
            case 'E':
                kind = EARTHCACHE;
            break;
            case 'L':
                kind = LETTERBOX;
            break;
            case 'M':
                kind = MULTI;
            break;
            case 'P':
                kind = PUZZLE;
            break;
            case 'T':
                kind = TRADITIONAL;
            break;
            case 'V':
                kind = VIRTUAL;
            break;
            case 'W':
                kind = WEBCAM;
            break;
        }

        Size size;
        switch (tokens[7][0])
        {
            case 'M':
                size = MICRO;
            break;
            case 'S':
                size = SMALL;
            break;
            case 'R':
                size = REGULAR;
            break;
            case 'L':
                size = LARGE;
            break;
            case 'O':
                size = OTHER_SIZE;
            break;
            case 'V':
                size = VIRTUAL_SIZE;
            break;
            default:
                size = NOT_CHOSEN;
            break;
        }

        float difficulty = atof(tokens[8]);
        int terrain = atof(tokens[9]);
        
        Status status = (tokens[10][0] == 'A') ? AVAILABLE : DISABLED;

        int day, month, year;
        sscanf(tokens[11], "%d/%d/%d", &year, &month, &day);
        Date date = dateCreate(year, month, day);
        
        int founds = atoi(tokens[12]);
        int not_founds = atoi(tokens[13]);
        int favourites = atoi(tokens[14]);
        
        array[count++] = cacheCreate(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], kind, size, difficulty, terrain, status, date.year, date.month, date.day, founds, not_founds, favourites, tokens[15]);

	    free(tokens);
        free(tmp);
    }

    fclose(stream);

    return count;
}

void clearCache(Cache arrayOfCaches[], int arrayLength) {
    Date emptyDate = dateCreate(0000, 00, 00);
    Cache emptyCache = cacheCreate("\0", "\0", "\0", "\0", "\0", "\0", EARTHCACHE, NOT_CHOSEN, 1, 1, DISABLED, emptyDate.year, emptyDate.month, emptyDate.day, 0, 0, 0, "-9999999");

    for (int i = 0; i < arrayLength; i++)
    {
        arrayOfCaches[i] = emptyCache;
    }
}