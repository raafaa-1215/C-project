#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringutils.h"
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

    int count = 0,
        numUniqueCache = 0;
    char line[MAX_CACHE],
         uniqueCache[MAX_CACHE][11];

    fgets(line, MAX_CACHE, stream);
    while (fgets(line, MAX_CACHE, stream))
    {
        if(count >= maxLength) break;

        char* tmp = strdup(line);
        
        char** tokens = splitString(tmp, 16, ";");
        
        rtrim(tokens[0]);
        rtrim(tokens[1]);
        rtrim(tokens[2]);
        rtrim(tokens[3]);
        rtrim(tokens[4]);
        rtrim(tokens[6]);

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

        rtrim(tokens[15]);
        
        for (int i = 0; i <= count; ++i) 
        {
            int isUnique = 1;

            for (int j = 0; j < numUniqueCache; ++j) 
            {
                if (strcmp(tokens[0], uniqueCache[j]) == 0) 
                {
                    isUnique = 0;
                    break;
                }
            }

            if (isUnique) 
            {
                strcpy(uniqueCache[numUniqueCache], tokens[0]);
                numUniqueCache++;
                array[count++] = cacheCreate(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], kind, size, difficulty, terrain, status, date.year, date.month, date.day, founds, not_founds, favourites, tokens[15]);
            }
        }

	    free(tokens);
        free(tmp);
    }

    fclose(stream);

    return count;
}

void clearCache(Cache *arrayOfCaches, int arrayLength) {
    Date emptyDate = dateCreate(0000, 00, 00);
    Cache emptyCache = cacheCreate("\0", "\0", "\0", "\0", "\0", "\0", EARTHCACHE, NOT_CHOSEN, 1, 1, DISABLED, emptyDate.year, emptyDate.month, emptyDate.day, 0, 0, 0, "-9999999");

    for (int i = 0; i < arrayLength; i++)
    {
        arrayOfCaches[i] = emptyCache;
    }
}

void listCache(Cache *arrayOfCaches, int arrayLength) {
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-8s | %-50s | %-22s | %-22s | %-10s | %-10s | %-12s | %-12s | %-11s | %-8s | %-9s | %-11s | %-6s | %-10s | %-10s | %-9s |",
    "CODE", "NAME", "STATE", "OWNER", "LATITUDE", "LONGITUDE", "KIND", "SIZE", "DIFFICULTY", "TERRAIN", "STATUS", "HIDDEN_DATE", "FOUNDS", "NOT_FOUNDS", "FAVOURITES", "ALTITUDE");
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < arrayLength; i++) {

        char kind[12], size[12];

        switch (arrayOfCaches[i].kind)
        {
            case 0:
                strcpy(kind, "EARTHCACHE");
            break;
            case 1:
                strcpy(kind, "LETTERBOX");
            break;
            case 2:
                strcpy(kind, "MULTI");
            break;
            case 3:
                strcpy(kind, "PUZZLE");
            break;
            case 4:
                strcpy(kind, "TRADITIONAL");
            break;
            case 5:
                strcpy(kind, "VIRTUAL");
            break;
            default:
                strcpy(kind, "WEBCAM");
            break;
        }

        switch (arrayOfCaches[i].size)
        {        
            case 0:
                strcpy(size, "MICRO");
            break;
            case 1:
                strcpy(size, "SMALL");
            break;
            case 2:
                strcpy(size, "REGULAR");
            break;
            case 3:
                strcpy(size, "LARGE");
            break;
            case 4:
                strcpy(size, "OTHER_SIZE");
            break;
            case 5:
                strcpy(size, "VIRTUAL_SIZE");
            break;
            default:
                strcpy(size, "NOT_CHOSEN");
            break;
        }

        printf("| %-8s | %-50s | %-22s | %-22s | %-10s | %-10s | %-12s | %-12s | %11.1f | %8.1f | %-9s | %04d/%02d/%02d  | %6d | %10d | %10d | %9s |",
            arrayOfCaches[i].code,
            arrayOfCaches[i].name,
            arrayOfCaches[i].state,
            arrayOfCaches[i].owner,
            arrayOfCaches[i].latitude,
            arrayOfCaches[i].longitude,
            kind,
            size,
            arrayOfCaches[i].difficulty,
            arrayOfCaches[i].terrain,
            (arrayOfCaches[i].status == AVAILABLE) ? "AVAILABLE" : "DISABLED",
            arrayOfCaches[i].hidden_date.year,
            arrayOfCaches[i].hidden_date.month,
            arrayOfCaches[i].hidden_date.day,
            arrayOfCaches[i].founds,
            arrayOfCaches[i].not_founds,
            arrayOfCaches[i].favourites,
            arrayOfCaches[i].altitude
        );

        printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}

void listFOUNDP(Cache *arrayOfCaches, int arrayLength) {
    long foundp;
    
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %s | %-8s | %-50s | %-22s | %-22s | %-10s | %-10s | %-12s | %-12s | %-11s | %-8s | %-9s | %-11s | %-6s | %-10s | %-10s | %-9s |",
    "FOUNDP", "CODE", "NAME", "STATE", "OWNER", "LATITUDE", "LONGITUDE", "KIND", "SIZE", "DIFFICULTY", "TERRAIN", "STATUS", "HIDDEN_DATE", "FOUNDS", "NOT_FOUNDS", "FAVOURITES", "ALTITUDE");
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < arrayLength; i++) {

        char kind[12], size[12];

        switch (arrayOfCaches[i].kind)
        {
            case 0:
                strcpy(kind, "EARTHCACHE");
            break;
            case 1:
                strcpy(kind, "LETTERBOX");
            break;
            case 2:
                strcpy(kind, "MULTI");
            break;
            case 3:
                strcpy(kind, "PUZZLE");
            break;
            case 4:
                strcpy(kind, "TRADITIONAL");
            break;
            case 5:
                strcpy(kind, "VIRTUAL");
            break;
            default:
                strcpy(kind, "WEBCAM");
            break;
        }

        switch (arrayOfCaches[i].size)
        {        
            case 0:
                strcpy(size, "MICRO");
            break;
            case 1:
                strcpy(size, "SMALL");
            break;
            case 2:
                strcpy(size, "REGULAR");
            break;
            case 3:
                strcpy(size, "LARGE");
            break;
            case 4:
                strcpy(size, "OTHER_SIZE");
            break;
            case 5:
                strcpy(size, "VIRTUAL_SIZE");
            break;
            default:
                strcpy(size, "NOT_CHOSEN");
            break;
        }

        foundp = ((float)arrayOfCaches[i].founds * 100) / (arrayOfCaches[i].founds + arrayOfCaches[i].not_founds);


        printf("| %5ld%% | %-8s | %-50s | %-22s | %-22s | %-10s | %-10s | %-12s | %-12s | %11.1f | %8.1f | %-9s | %04d/%02d/%02d  | %6d | %10d | %10d | %9s |",
            foundp,
            arrayOfCaches[i].code,
            arrayOfCaches[i].name,
            arrayOfCaches[i].state,
            arrayOfCaches[i].owner,
            arrayOfCaches[i].latitude,
            arrayOfCaches[i].longitude,
            kind,
            size,
            arrayOfCaches[i].difficulty,
            arrayOfCaches[i].terrain,
            (arrayOfCaches[i].status == AVAILABLE) ? "AVAILABLE" : "DISABLED",
            arrayOfCaches[i].hidden_date.year,
            arrayOfCaches[i].hidden_date.month,
            arrayOfCaches[i].hidden_date.day,
            arrayOfCaches[i].founds,
            arrayOfCaches[i].not_founds,
            arrayOfCaches[i].favourites,
            arrayOfCaches[i].altitude
        );

        printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}