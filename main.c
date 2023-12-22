#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include <ctype.h>

void printCommands(char *commandsList) {
    printf("\n Os comandos disponiveis sao: \n");
    
    for (int i = 0; i < 5; i++)
    {
        printf("- %s\n", commandsList[i]);
    }
    
    printf("\n\n");
}



int getCommand(char *str, char *commandsList, int *size) {
    int i;

    do
    {
        printf("Introduza o comando: \n");
        gets(str);

        for (i = 0; str != '\0' ; i++)
        {
            str[i] = toupper(str[i]);
        }
        
        for (i = 0; i < size; i++)
        {   
            if (strcmp(str, commandsList[i]))
            {
                break;
            }
        }

    } while (1);
    
    return i;
}

int main() {
    char commandsList[5] = {"LOAD", "CLEAR", "QUIT", "LIST", "FOUNDP"};
    int size = 5;
    char response[10];

    // TODO: implement menu and call subprograms for each operation

    printf("I'm missing a menu! :( \n");

    return EXIT_SUCCESS;
}

