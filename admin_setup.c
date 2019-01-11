#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "admin_setup.h"

typedef struct{
    char user[20];
    char password[20];
    struct admin *next;
}admin;

admin * adm_header = NULL;

void userSetup(int *reg) {
    if (*reg == 0){
        admin *new_Adm = (admin *) malloc(sizeof(admin));
        //char token[21] = "";
        //token[21] = tokenGenerator(token);
        printf("There is no user set up yet\n");
        printf("Register your user name (max. of 20 chars.):\n");
        scanf("%s", new_Adm->user);
        printf("Register your password (max. of 20 chars.):\n");
        scanf("%s", new_Adm->password);
        new_Adm->next = adm_header;
        adm_header = new_Adm;
        admWrite();
        *reg = 1;
        writeReg(reg);
        //printf("You have 30 seconds take not of your token in case you wan't to restart your password\n");
        //printf("REFTOKEN: %s\n", token);
        (long)time(30);//it will wait 30 seconds
        system("cls");
    }
    else{
            checkAdmin(reg);
        }
}


void checkAdmin(int *reg) {
    char adm[20];
    char psswd[20];
    printf("Let\'s check your identity\n");
    printf("User:\n");
    scanf("%s", adm);
    printf("Password:\n");
    scanf("%s", psswd);
    while (*reg != 2) {
        if (strcmp(adm, adm_header->user) == 0 && strcmp(psswd, adm_header->password) == 0) {
            printf("Acess Granted\n");
            printf("Welcome back %s\n", adm_header->user);
            *reg = 2;

        } else {
            printf("Wrong user or password\n");
            checkAdmin(reg);
        }
    }
}

void admWrite()
{
    admin *newadm = adm_header;
    FILE *fptr;
    fptr = fopen("admin.bin", "wb");
    if(fptr == NULL){
        printf("No such file found\n");
        return;
    }
    while(newadm != NULL){
        fwrite(newadm, sizeof(admin), 1, fptr);
        newadm = newadm->next;
    }
    fclose(fptr);
}

void readAdm()
{
    FILE *fptr;
    fptr = fopen("admin.bin", "rb");
    if(fptr == NULL){
        printf("No such file found\n");
        return;
    }
    while (1){
        admin *newadm = malloc(sizeof(admin));
        if (fread(newadm, sizeof(admin),1,fptr)==0 ){
            fclose(fptr);
            return;
        }
        newadm->next = adm_header;
        adm_header = newadm;
    }
    fclose(fptr);
}

void listAdm(){
    admin *ptr =  adm_header;

    printf("Admin:\tPassword\n");
    while (ptr != NULL) {
        printf("%s \t%s\n",
               ptr->user,
               ptr->password
             );

        ptr = ptr->next;
    }
}

int writeReg(int *reg)
{
    FILE *fptr;
    fptr = fopen("reg.bin", "wb");
    if(fptr == NULL){
        printf("No such file found\n");
        return *reg;
    }
    fwrite(reg, sizeof(reg), 1, fptr);
    return *reg;
}

int readReg(int *reg)
{
    FILE *fptr;
    fptr = fopen("reg.bin", "rb");
    if(fptr == NULL){
        printf("No such file found\n");
        *reg = 0;
        return *reg;
    }
    fread(reg, sizeof(reg), 1, fptr);
    return *reg;
}

/*
char tokenGenerator(char token[])
{
    srand(time(0));
    int index = 0;
    while (index < 20)
    {
        int limit = rand()%122;
            if(limit >=48 && limit<=57)
            {
                token[index] = (char)limit;
                index++;
            }
            else if(limit >=65 && limit<=90)
            {
                token[index] = (char)limit;
                index++;
            }
            else if(limit >=97 && limit<=122)
            {
                token[index] = (char)limit;
                index++;
            }
            else{
            continue;
            }
    }
    return *token;
}


char *writeToken(char token[])
{
    FILE *fptr;
    fptr = fopen("token.bin", "wb");
    if(fptr == NULL){
        printf("No such file found\n");
        return(NULL);
    }
    fwrite(token, strlen(token), 1, fptr);
    return token;
}

char *readToken(char token[])
{
    FILE *fptr;
    fptr = fopen("token.bin", "rb");
    if(fptr == NULL){
        printf("No such file found\n");
        return 0;
    }
    fread(token, strlen(token), 1, fptr);
    return token;
}
 */