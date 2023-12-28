#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "date.h"
#include "cache.h"

#define MAX_CACHE 2001

// Imprime a lista de comandos disponíveis correspondente à fase 1 do projeto
void printCommands(char (*commandsList)[10]) {
    printf("\nOs comandos disponiveis sao: \n");
    
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
        printf("Introduza o comando ('help' para listar comandos):\n");
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
            printf("Comando nao encontrado, tente novamente.\n\n");
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
                    printf("\nIntroduza o nome do ficheiro: ");
                    gets(fileName);

                    numCache = loadCaches(fileName, arrayOfCache, MAX_CACHE);

                    if (numCache == 0)
                    {
                        printf("\n<File not found>\n");
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
                        
                        printf("\n<%d unique caches loaded>\n", numUniqueCache);

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
                    printf("\nTem a certeza que pretende limpar as caches? (S/N)\n");
                    scanf(" %c", &confirmRes);

                    confirmRes = toupper(confirmRes);

                    if (confirmRes == 'S')
                    {
                        clearCache(arrayOfCache, MAX_CACHE);
                        
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
                        printf("Resposta invalida, tente novamente\n\n");
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
                printf("\nTem a certeza que pretende sair? (S/N)\n");
                scanf(" %c", &confirmRes);

                confirmRes = toupper(confirmRes);

                if (confirmRes == 'S')
                {
                    return 0;
                }
                else if (confirmRes == 'N')
                {
                    goto interpretCommand;
                }
                else
                {
                    printf("Resposta invalida, tente novamente\n\n");
                }
            } while (1);
        break;
        case 3:
            printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
            "CODE", "NAME", "STATE", "OWNER", "LATITUDE", "LONGITUDE", "KIND", "SIZE", "DIFFICULTY", "TERRAIN", "STATUS", "HIDDEN_DATE", "FOUNDS", "NOT_FOUNDS", "FAVOURITES", "ALTITUDE");

            for (int i = 0; i < numCache; i++) {
                printf("%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t%f\t%s\t%04d/%02d/%02d\t%d\t%d\t%d\t%s\n",
                    arrayOfCache[i].code,
                    arrayOfCache[i].name,
                    arrayOfCache[i].state,
                    arrayOfCache[i].owner,
                    arrayOfCache[i].latitude,
                    arrayOfCache[i].longitude,
                    arrayOfCache[i].kind,
                    arrayOfCache[i].size,
                    arrayOfCache[i].difficulty,
                    arrayOfCache[i].terrain,
                    (arrayOfCache[i].status == AVAILABLE) ? "AVAILABLE" : "DISABLED",
                    arrayOfCache[i].hidden_date.year,
                    arrayOfCache[i].hidden_date.month,
                    arrayOfCache[i].hidden_date.day,
                    arrayOfCache[i].founds,
                    arrayOfCache[i].not_founds,
                    arrayOfCache[i].favourites,
                    arrayOfCache[i].altitude
                );
            }
        default:

        break;
    }
}

