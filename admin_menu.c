#include <stdio.h>
#include <stdlib.h>
#include "admin_setup.h"

void initialScreen(){
    printf( " _    ____________   _                   _____           _\n");
    printf( "| |   | ___ \\ ___ \\ | |                 /  ___|         | |\n");
    printf( "| |   | |_/ / |_/ / | |     ___   __ _  \\ `--. _   _ ___| |_ ___ _ __ ___ \n");
    printf( "| |   |  __/|    /  | |    / _ \\ / _` |  `--. \\ | | / __| __/ _ \\ '_ ` _ \\\n");
    printf( "| |___| |   | |\\ \\  | |___| (_) | (_| | /\\__/ / |_| \\__ \\ ||  __/ | | | | |\n");
    printf( "\\_____|_|   \\_| \\_| \\_____/\\___/ \\__, | \\____/ \\__, |___/\\__\\___|_| |_| |_|\n");
    printf( "                                  __/ |         __/ |                      \n");
    printf( "                                 |___/         |___/                       \n");
    printf("\n");
}

void initialMenu(int *reg)
{
    fflush(stdin);
    printf("******************************\n");
    printf("**** Log In/Sign Up Menu: ****\n");
    printf("******************************\n");
    printf("1- Register Admin:\n");
    printf("2- Log in as Admin\n");
    printf("3- Log in as worker\n");
    printf("4- Reset Admin:\n");
    printf("5- Exit to desktop\n");
    int option = -1;
    scanf("%d", &option);
    switch (option){
        default:{
            printf("Please select a valid a option");
            system("cls");
            initialScreen();
            initialMenu(reg);
            break;
        }
        case 1:{
            system("cls");
            initialScreen();
            adminSetup(reg);
            break;
        }
        case 2:{
            system("cls");
            initialScreen();
            checkAdmin(reg);
            break;
        }
        case 3:{
            system("cls");
            initialScreen();
            break;
        }
        case 4:{
            system("cls");
            initialScreen();
            admReset(reg);
            break;
        }

        case 5:{
            system("cls");
            initialScreen();
            printf("Exiting ...\n");
            initialScreen();
            exit(0);
        }
    }
}

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
        fflush(stdin);
        scanf("%c", &opc);
        switch (opc){
            default:{
                printf("Please select a valid option");
                adminMenu(reg);
                break;
            }
            case '0':{
                system("cls");
                fflush(stdin);
                initialScreen();
                printf("Logging you out...\n");
                printf("Exiting ...\n");
                initialScreen();
                exit(0);
            }
        }
    }
    else if(*reg == 1){
        checkAdmin(reg);
    } else{
        adminSetup(reg);
    }
}