#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stringutils.h"
#include "input.h"
#include "date.h"
#include "cache.h"

#define MAX_CACHE 2001

// Imprime a lista de comandos disponíveis correspondente à fase 1 do projeto
void printCommands(char (*commandsList)[10]) {
    printf("\nAll available commands are: \n");
    
    for (int i = 0; i < 5; i++)
    {
        printf("  - %s\n", commandsList[i]);
    }
    
    printf("\n\n");
}

// Solicita o comando ao utilizador e devolve o index do mesmo
int getCommand(char *str, char (*commandsList)[10], int *size) {
    int i;

    do
    {
        printf("Insert the command ('help' to list commands):\n");
        gets(str);

        for (i = 0; str[i] != '\0' ; i++)
        {
            str[i] = toupper((unsigned char)str[i]);
        }

        if (strcmp(str, "HELP") == 0)
        {
            printCommands(commandsList);
            continue;
        }
        
        for (i = 0; i < *size; i++)
        {   
            if (strcmp(str, commandsList[i]) == 0)
            {
                goto endCheck;
            }
        }

        if (i == *size)
        {
            printf("\n<Invalid command, try again>\n\n");
        }
    } while (1);
    
    endCheck:

    return i;
}

int main() {
    Cache arrayOfCache[MAX_CACHE];
    char commandsList[][10] = {"LOAD", "CLEAR", "QUIT", "LIST", "FOUNDP"},
         res[10],
         confirmRes,
         fileName[21],
         uniqueCache[MAX_CACHE][11];
    int size, 
        commandIndex,
        numCache = 0,
        numUniqueCache = 0;

    size = sizeof(commandsList) / sizeof(commandsList[0]);

    interpretCommand:

    fflush(stdin);

    commandIndex = getCommand(res, commandsList, &size);

    switch (commandIndex)
    {
        case 0: // comando LOAD
            if (arrayOfCache[0].code[0] == '\0')
            {
                do
                {
                    printf("\nInsert file name: ");
                    gets(fileName);

                    numCache = loadCaches(fileName, arrayOfCache, MAX_CACHE);

                    if (numCache == 0)
                    {
                        printf("\n<File not found>\n\n");
                    }
                    else
                    {
                        for (int i = 1; i < numCache; ++i) 
                        {
                            int isUnique = 1;

                            for (int j = 0; j < numUniqueCache; ++j) 
                            {
                                if (strcmp(arrayOfCache[i].code, uniqueCache[j]) == 0) 
                                {
                                    isUnique = 0;
                                    break;
                                }
                            }

                            if (isUnique) 
                            {
                                strcpy(uniqueCache[numUniqueCache], arrayOfCache[i].code);
                                numUniqueCache++;
                            }
                        }
                        
                        printf("\n<%d unique caches loaded>\n\n", numUniqueCache);

                        goto interpretCommand;
                    }
                } while (1);
            }
            else
            {
                printf("\n<Cache data exists. Please clear it first.>\n\n");
                goto interpretCommand;
            }
        break;
        case 1: // comando CLEAR
            if (arrayOfCache[0].code[0] != '\0')
            {
                do
                {
                    printf("\nAre you sure you want to clear the caches? (Y/N)\n");
                    scanf(" %c", &confirmRes);

                    confirmRes = toupper(confirmRes);

                    if (confirmRes == 'Y')
                    {
                        clearCache(arrayOfCache, numCache);
                        
                        if (arrayOfCache[0].code[0] == '\0')
                        {
                            printf("\n<Cache data cleared>\n\n");
                        }
                        else
                        {
                            printf("\n<Error clearing cache data>\n\n");
                        }
                        
                        goto interpretCommand;
                    }
                    else if (confirmRes == 'N')
                    {
                        goto interpretCommand;
                    }
                    else
                    {
                        printf("\n<Invalid anwser, try again>\n\n");
                    }
                } while (1);   
            }
            else
            {
                printf("\n<Cache data is already clear>\n\n");
                goto interpretCommand;
            }
        break;
        case 2: // comando QUIT
            do
            {
                printf("\nAre you sure you want to quit? (Y/N)\n");
                scanf(" %c", &confirmRes);

                confirmRes = toupper(confirmRes);

                if (confirmRes == 'Y')
                {
                    return 0;
                }
                else if (confirmRes == 'N')
                {
                    goto interpretCommand;
                }
                else
                {
                    printf("\n<Invalid answer, try again>\n\n");
                }
            } while (1);
        break;
        case 3: // comando LIST
            if (arrayOfCache[0].code[0] != '\0')
            {
                listCache(arrayOfCache, numCache);
            }
            else
            {
                printf("\n<Data not loaded>\n\n");
            }

            goto interpretCommand;
        break;
        case 4: // comando FOUNDP
            if (arrayOfCache[0].code[0] != '\0')
            {
                listFOUNDP(arrayOfCache, numCache);
            }
            else
            {
                printf("\n<Data not loaded>\n\n");
            }

            goto interpretCommand;
        break;
    }
}

