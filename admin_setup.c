#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "serial_communication.h"
#include "admin_setup.h"
#include "admin_menu.h"
#define ENTER 13 //posição 13 na tabela ascii para enter
#define BKSC 8 //posição 8 na tabela para o backspace

typedef struct {
    char user[20];
    char password[20];
    struct admin *next;
}admin;

admin *head = NULL;

void adminSetup(int *reg){
    admin *newadmin = (admin*)malloc(sizeof(admin));
    if(*reg == 0) {
        printf("There is not admin setup yet\n");
        printf("Please type in your new admin username(20 char max.):\n");
        scanf("%s", newadmin->user);
        printf("Please enter your new password (20 char max.):\n");
        scanf("%s", newadmin->password);

        newadmin->next = head;
        head = newadmin;
        writeAdm();
        *reg = 1;
        writeReg(reg);
        system("cls");
        adminMenu(reg);
    }
    else{
        checkAdmin(reg);
    }
}

void checkAdmin(int *reg){
    readAdm();
    char adm[20]="";
    char psswd[20]="";
    printf("Let\'s check your identity\n");
    printf("User:\n");
    scanf("%s", adm);
    printf("Password:\n");
    scanf("%s", psswd);
    system("cls");
    while (*reg == 1) {
        if (strcmp(adm, head->user) == 0 && strcmp(psswd, head->password) == 0) {
            printf("Acess Granted\n");
            system("cls");
            printf("Welcome back %s\n", head->user);
            *reg = 2;
            adminMenu(reg);

        } else {
            printf("Wrong user or password\n");
            checkAdmin(reg);
        }
    }
}



void writeAdm(){
    admin *pt = head;
    FILE *fptr;
    fptr = fopen ("administrator.b","wb");

    if(fptr == NULL){
        printf("Error\n");
        return;
    }
    while(pt != NULL){
        fwrite(pt, sizeof(admin), 1, fptr);
        pt = pt->next;
    }

    fclose(fptr);

}

void readAdm(){
    FILE *fptr;
    fptr = fopen ("administrator.b","rb");

    if(fptr == NULL){
        printf("Error\n");
        return;
    }

    while (1){
        admin *newadmin = malloc(sizeof(admin));
        if (fread(newadmin, sizeof(admin),1,fptr)==0 ){
            fclose(fptr);
            return;
        }
        newadmin->next = head;
        head = newadmin;
    }

    fclose(fptr);

}

void listAdm(){
    admin *ptr =  head;

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
    fptr = fopen("regis.bin", "wb");
    if(fptr == NULL){
        printf("No such file found\n");
        *reg = 0;
        return *reg;
    }
    fwrite(reg, sizeof(reg), 1, fptr);
    fclose(fptr);
}

int readReg(int *reg)
{
    FILE *fptr;
    fptr = fopen("regis.bin", "rb");
    if(fptr == NULL){
        printf("No such file found\n");
        *reg = 0;
        adminSetup(reg);
    }
    fread(reg, sizeof(reg), 1, fptr);
    fclose(fptr);
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
        adminSetup(reg);
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
    return id;
}