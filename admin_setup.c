#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "serial_communication.h"
#include "admin_setup.h"
#include "admin_menu.h"
#define ENTER 13 //posição 13 na tabela ascii para enter
#define BKSC 8 //posição 8 na tabela para o backspace

typedef struct{
    char user[20];
    char password[20];
    struct admin *next;
}admin;

admin * adm_header = NULL;

void adminSetup(int *reg) {
    if (*reg == 0){
        admin *new_Adm = (admin *) malloc(sizeof(admin));
        printf("There is no user set up yet\n");
        printf("Register your user name (max. of 20 chars.):\n");
        scanf("%s", new_Adm->user);
        if(strlen(new_Adm->user) > 20){
            printf("Username must be maximum of 20 chars\n");
            adminSetup(reg);
        }
        printf("Register your password (max. of 20 chars.):\n");
        scanf("%s", new_Adm->password);
        if(strlen(new_Adm->password) > 20){
            printf("Password must be maximum of 20 chars\n");
            adminSetup(reg);
        }
        new_Adm->next = adm_header;
        adm_header = new_Adm;
        admWrite();
        *reg = 1;
        writeReg(reg);
        system("cls");
    }
    else{
            checkAdmin(reg);
        }
}


void checkAdmin(int *reg) {
    readAdm();
    char adm[20];
    char psswd[20];
    printf("Let\'s check your identity\n");
    printf("User:\n");
    scanf("%s", adm);
    printf("Password:\n");
    scanf("%s", psswd);
    system("cls");
    while (*reg == 1) {
        if (strcmp(adm, adm_header->user) == 0 && strcmp(psswd, adm_header->password) == 0) {
            printf("Acess Granted\n");
            system("cls");
            printf("Welcome back %s\n", adm_header->user);
            *reg = 2;
            adminMenu(reg);

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
        *reg = 0;
        return *reg;
    }
    fwrite(reg, sizeof(reg), 1, fptr);
    if (*reg == 1) {
        return *reg;
    }
    else{
        *reg = 0;
        return *reg;
    }
}

int readReg(int *reg)
{
    FILE *fptr;
    fptr = fopen("reg.bin", "rb");
    if(fptr == NULL){
        printf("No such file found\n");
        *reg = 0;
        adminSetup(reg);
    }
    fread(reg, sizeof(reg), 1, fptr);
    return *reg;
}

void admReset(int *reg) {
    serialRead();
    int var;
    var = readToken();
    if (var == 0) {
        /*if (ptr != NULL) {
            while (ptr != NULL) {
                if (ptr == adm_header) {
                    aux = ptr->next; // guardo posição do next do ptr
                    free(ptr); //
                    ptr->next = adm_header;
                    adm_header = aux;
                    ptr = adm_header;
                }
                ptr = ptr->next;
            }
        }*/ // nao remover de comentario
        remove("admin.bin");
        remove("reg.bin");
        remove("id.txt");
        *reg = 0;
        writeReg(reg);
        printf("Adminstrator cleared\n");
        printf("%d", var);
    }
}


void writeToken(char id[]) {
    FILE *fptr;
    fptr = fopen("id.txt", "w");
    if (fptr == NULL) {
        printf("No such file found\n");
    }
    fprintf(fptr, "%s", id);
    fclose(fptr);
}

/*
 char *readToken(char id[]){
    FILE *fptr;
    fptr = fopen("id.txt", "r");
    if(fptr == NULL){
        printf("No such file found\n");
    }
    fscanf(fptr, "%s", id);
    fclose(fptr);
    return id;
}
 */

int readToken(){
    char resetToken[] = "DA:59:CD:73";
    char id[strlen(resetToken)];
    int token = 0;
    FILE *fptr;
    fptr = fopen("id.txt", "r");
    if(fptr == NULL){
        printf("No such file found\n");
    }
    fscanf(fptr, "%s", id);
    token = strcmp(resetToken, id);
    //printf("%d\n FILE: %s\n RESETTOKEN:: %s\n", token, id, resetToken);
    fclose(fptr);
    return token;
}

char *readRFID(char id[]){
    FILE *fptr;
    fptr = fopen("id.txt", "r");
    if(fptr == NULL){
        printf("No such file found\n");
    }
    fscanf(fptr, "%s", id);
    fclose(fptr);
    return *id;
}