#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

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
    char commandsList[][10] = {"LOAD", "CLEAR", "QUIT", "LIST", "FOUNDP"};
    int size, commandIndex;
    char res[10];

    size = sizeof(commandsList) / sizeof(commandsList[0]);

    // TODO: implement menu and call subprograms for each operation

    commandIndex = getCommand(res, commandsList, &size);
    
}

