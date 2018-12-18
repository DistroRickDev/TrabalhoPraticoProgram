/*
 * Projecto em linguagem C
 * Autor: Ricardo Duarte
 * Copyright © 2018 Ricardo Duarte.  All rights reserved.
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

void user_setup();
char *tokenGenerator(char token[]);
void check_Admin();
void writeAdm();
void readAdm();

int main()
{
    //int regis = 0;
    while(1) {
        if (adm_header == NULL) {
            user_setup();
        } else if (adm_header != NULL) {
            check_Admin();
        }
    }
    //printf("The token is :%s\n", tokenGenerator(token));

}


void user_setup(){
    admin *new_Adm =(admin*)malloc(sizeof(admin));
    char token[20];
    printf("There is no user set up yet\n");
    printf("Register your user name (max. of 20 chars.):\n");
    scanf("%s",new_Adm->user);
    printf("Register your password (max. of 20 chars.):\n");
    scanf("%s",new_Adm->password);
    printf("You have 60 seconds take not of your token in case you wan't to restart your password\n");
    printf("REFTOKEN: %s\n", tokenGenerator(token));
    //writeAdm();
    new_Adm->next = adm_header;
    adm_header = new_Adm;
    }

void check_Admin(){
    char adm[20];
    char psswd[20];
    int valve = 1;
    printf("Let\'s check your identity\n");
    printf("User:\n");
    scanf("%s",adm);
    printf("Password:\n");
    scanf("%s",psswd);
    while(valve != 2)
    if(strcmp(adm , adm_header->user) == 0 && strcmp(psswd, adm_header->password)==0){
            printf("Acess Granted\n");
            printf("Welcome back %s\n", adm_header->user);
            valve = 2;
        }
        else{
            printf("Wrong user or password\n");
            valve = 1;
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

void writeAdm(){
    admin *pt = adm_header;
    FILE *fptr;
    fptr = fopen ("admins.b","wb");

    if(fptr == NULL){
        printf("Error no such file found\n");
        return;
    }
    while(pt != NULL){
        fwrite(pt, sizeof(admin), 1, fptr);
        pt = pt->next;
    }

    fclose(pt);

}

void readAdm(){
    FILE *fptr;
    fptr = fopen ("admins.b","rb");

    if(fptr == NULL){
        printf("Error no such file found\n");
        return;
    }

    while (1){
        admin *newadmin = malloc(sizeof(admin));
        if (fread(newadmin, sizeof(admin),1,fptr)==0 ){
            fclose(fptr);
            return;
        }
        newadmin->next = adm_header;
        adm_header = newadmin;
    }
    fclose(fptr);
}



