/*
 * Projecto de grupo em linguagem C
 * Disciplina: Programação
 * Curso: SEC 1º Ano
 * Autores: Ricardo Duarte, Pedro Lima e Luis Moreira
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char *user;
    char *password;
    struct admin *next;
}admin;

admin * adm_header = NULL;

void user_setup(int *reg);
char *tokenGenerator(char token[]);
void check_Admin(int *reg);


int main()
{
    int regis = 0;
    user_setup(&regis);
    //check_Admin(&regis);
    //printf("The token is :%s\n", tokenGenerator(token));
}


void user_setup(int *reg){
    admin *new_Adm =(admin*)malloc(sizeof(admin));
    char token[20];
    printf("There is no user set up yet\n");
    printf("Register your user name (max. of 20 chars.):\n");
    scanf("%s",new_Adm->user);
    printf("Register your password (max. of 20 chars.):\n");
    scanf("%s",new_Adm->password);
    //printf("You have 60 seconds take not of your token in case you wan't to restart your password\n");
    //printf("REFTOKEN: %s\n", tokenGenerator(token));
    new_Adm->next = adm_header;
    adm_header = new_Adm;
    *reg = 1;
    }

void check_Admin(int *reg){
    char adm[20];
    char psswd[20];
    printf("Let\'s check your identity\n");
    printf("User:\n");
    scanf("%s",adm);
    printf("Password:\n");
    scanf("%s",psswd);
    while(reg != 2)
    if(strcmp(adm , adm_header->user) == 0 && strcmp(psswd, adm_header->password)==0){
            printf("Acess Granted\n");
            printf("Welcome back %s\n", adm_header->user);
            *reg = 2;
        }
    else{
            printf("Wrong user or password\n");
            check_Admin(reg);
        }
    }

char *tokenGenerator(char token[])
{
    srand(time(NULL));
    int index = 0;
    while (index < 20)
    {
        int limit = rand()%(127 + 1 - 48) + 48;
        token[index] = (char)limit;
        index++;
    }
    return token;
}




