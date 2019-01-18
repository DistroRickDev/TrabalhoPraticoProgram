#include <stdio.h>
#include <time.h>
#include "db_interaction.h"
#include "serial_communication.h"
#include "admin_setup.h"
#include "admin_menu.h"

void userMenu (){
    char opc = ' ';

        printf("******************************\n");
        printf("**** User Menu: **************\n");
        printf("******************************\n");
        printf("1- User Login:\n");
        printf("2- Check entrance logs:\n");
        printf("3- Check exit logs:\n");
        printf("0- Logout and exit:\n");
        fflush(stdin);
        scanf("%c", &opc);

        switch(opc){
            default:{
                printf("Please select a valid option!\n");
                userMenu();
                break;
            }
            case '1':{
                char rfid[] = "";
                printf("Please place card in front of receiver!\n");
                serialRead();
                readRFID(rfid);
                insertLog(rfid,0);
                userMenu();
                break;
            }

            case '2':{
                initialScreen();
                char rfid[] = "";
                printf("Please place card in front of receiver!\n");
                serialRead();
                readRFID(rfid);
                printf("Saídas\n");
                listLogs(rfid,1);
                printf("Entradas\n");
                listLogs(rfid,0);
                userMenu();
                break;
            }

            case '3':{
                initialScreen();
                char rfid[] = "";
                printf("Please place card in front of receiver!\n");
                serialRead();
                readRFID(rfid);
                insertLog(rfid,1);
                userMenu();
                break;
            }
            case '0':{
                initialScreen();
                printf("Logging you out\n");
                time(1000);
                return;
            }

        }
}
