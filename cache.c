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
        
        int founds = atoi(tokens[3]);
        int day, month, year;
        sscanf(tokens[11], "%d/%d/%d", &year, &month, &day);
        Date date = dateCreate(year, month, day);

        array[count++] = cacheCreate(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], date.year, date.month, date.day);

	    free(tokens);
        free(tmp);
    }

    fclose(stream);

    return count;
}