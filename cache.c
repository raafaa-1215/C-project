#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "date.h"
#include "cache.h"

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

int importcaches(char filename[], Cache array[], int maxLength) {

    FILE* stream = fopen(filename, "r");

    int count = 0;
    char line[2000];

    fgets(line, 2000, stream);
    while (fgets(line, 2000, stream))
    {
        if(count >= maxLength) break;

        char* tmp = strdup(line);
        
        char** tokens = splitString(tmp, 16, ",");
        
        Kind kind;
        switch (*tokens[6])
        {
            case 'EARTHCACHE':
                kind = EARTHCACHE;
            break;
            case 'LETTERBOX':
                kind = LETTERBOX;
            break;
            case 'MULTI':
                kind = MULTI;
            break;
            case 'PUZZLE':
                kind = PUZZLE;
            break;
            case 'TRADITIONAL':
                kind = TRADITIONAL;
            break;
            case 'VIRTUAL':
                kind = VIRTUAL;
            break;
            case 'WEBCAM':
                kind = WEBCAM;
            break;
        }

        Size size;
        switch (*tokens[7])
        {
            case 'MICRO':
                size = MICRO;
            break;
            case 'SMALL':
                size = SMALL;
            break;
            case 'REGULAR':
                size = REGULAR;
            break;
            case 'LARGE':
                size = LARGE;
            break;
            case 'OTHER_SIZE':
                size = OTHER_SIZE;
            break;
            case 'VIRTUAL':
                size = VIRTUAL;
            break;
            default:
                size = NOT_CHOSEN;
            break;
        }

        float difficulty = atof(tokens[8]);
        int terrain = atof(tokens[9]);
        
        Status status = (tokens[10] == "AVAILABLE") ? AVAILABLE : DISABLED;

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