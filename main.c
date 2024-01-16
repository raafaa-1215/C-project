#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stringutils.h"
#include "input.h"
#include "date.h"
#include "cache.h"

#define MAX_CACHE 2001

// Imprime a lista de comandos disponíveis correspondente à fase 2 do projeto
void printCommands(char (*commandsList)[10], int *size) {
    printf("\nAll available commands are: \n");
    
    for (int i = 0; i < *size; i++)
    {
        printf("  - %s\n", commandsList[i]);
    }
}

// Solicita o comando ao utilizador e devolve o index do mesmo
int getCommand(char *str, char (*commandsList)[10], int *size) {
    int i;

    do
    {
        printf("\nInsert the command ('help' to list commands):\n");
        gets(str);

        for (i = 0; str[i] != '\0' ; i++)
        {
            str[i] = toupper((unsigned char)str[i]);
        }

        if (strcmp(str, "HELP") == 0)
        {
            printCommands(commandsList, size);
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
            printf("\n<Invalid command, try again>\n");
        }
    } while (1);
    
    endCheck:

    return i;
}


// Corpo principal, onde a execução do comando é decidida
int main() {
    Cache arrayOfCache[MAX_CACHE];
    char commandsList[][10] = {"LOAD", "CLEAR", "QUIT", "LIST", "FOUNDP", "SEARCH", "EDIT", "CENTER", "AGE", "SORT", "STATEC", "M81", "SAVE"},
         res[10],
         findCode[11],
         confirmRes,
         fileName[21];
    int size = sizeof(commandsList) / sizeof(commandsList[0]), 
        commandIndex,
        editIndex,
        numCache = 0;

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
                        printf("\n<%d unique caches loaded>\n", numCache);
                        goto interpretCommand;
                    }
                } while (1);
            }
            else
            {
                printf("\n<Cache data exists. Please clear it first.>\n");
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
                            printf("\n<Cache data cleared>\n");
                            break;
                        }
                        else
                        {
                            printf("\n<Error clearing cache data>\n");
                        } 
                    }
                    else if (confirmRes == 'N')
                    {
                        break;
                    }
                    else
                    {
                        printf("\n<Invalid anwser, try again>\n");
                    }
                } while (1); 

                goto interpretCommand;  
            }
            else
            {
                printf("\n<Cache data is already clear>\n");
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
                    printf("\n<Invalid answer, try again>\n");
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
                printf("\n<Data not loaded>\n");
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
                printf("\n<Data not loaded>\n");
            }

            goto interpretCommand;
        break;
        case 5: // comando SEARCH
        break;
        case 6: // comando EDIT
            if (arrayOfCache[0].code[0] != '\0')
            {
                editStart:
                
                printf("\nInsert the cache code: ");
                gets(findCode);

                editIndex = findEditCache(findCode, arrayOfCache, numCache);
                
                if (editIndex == -1)
                {
                    printf("\n<Cache not found>\n");
                    goto editStart;
                }
                else
                {
                    editCache(&arrayOfCache[editIndex]);
                }
            }
            else
            {
                printf("\n<Data not loaded>\n");
            }

            goto interpretCommand;
        break;
        case 7: // comando CENTER
        break;
        case 8: // comando AGE
        break;
        case 9: // comando SORT
        break;
        case 10: // comando STATEC
        break;
        case 11: // comando M81
        break;
        case 12: // comando SAVE
        break;
    }
}

