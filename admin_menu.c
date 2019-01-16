#include <stdio.h>
#include "admin_setup.h"

void adminMenu(int *reg) {
    char opc = ' ';
    if (*reg == 2) {
        printf("******************************\n");
        printf("**** Administrator Menu: *****\n");
        printf("******************************\n");
        printf("1- Register new employee:\n");
        printf("2- Delete employee:\n");
        printf("3- Print list of employees:\n");
        printf("4- Check entrance logs:\n");
        printf("5- Check exit logs:\n");
        printf("0- Logout and exit:\n");
        scanf("%c", &opc);
        switch (opc){
            default:{
                printf("Please select a valid option");
                adminMenu(reg);
            }
        }
    }
    else{
        adminSetup(reg);
    }
}