#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "date.h"
#include "cache.h"

#define MAX_CACHE 2000

void printCommands(char (*commandsList)[10]) {
    printf("\nOs comandos disponiveis sao: \n");
    
    for (int i = 0; i < 5; i++)
    {
        printf("  - %s\n", commandsList[i]);
    }
    
    printf("\n\n");
}

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
         confirmQuit,
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
        case 0:
            if (arrayOfCache[0].code[0] == '\0')
            {
                do
                {
                    printf("\nIntroduza o nome do ficheiro: ");
                    gets(fileName);

                    numCache = importCaches(fileName, arrayOfCache, MAX_CACHE);

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
        case 1:
            
        break;
        case 2:
            do
            {
                printf("\nTem a certeza que pretende sair? (S/N)\n");
                scanf(" %c", &confirmQuit);

                confirmQuit = toupper(confirmQuit);

                if (confirmQuit == 'S')
                {
                    return 0;
                }
                else if (confirmQuit == 'N')
                {
                    goto interpretCommand;
                }
                else
                {
                    printf("Resposta invalida, tente novamente\n\n");
                }
            } while (1);
        break;
        default:

        break;
    }
}

