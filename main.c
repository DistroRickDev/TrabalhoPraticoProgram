/*
 * Projecto de grupo em linguagem C
 * Disciplina: Programação
 * Curso: SEC 1º Ano
 * Autores: Ricardo Duarte, Pedro Lima e Luis Moreira
 */

#include <stdio.h>
#include <time.h>
#include "serial_communication.h"
#include "admin_setup.h"
#include "admin_menu.h"
#include "db_interaction.h"

int main()
{
    //testaru
    listWorkers("Adolf");
    listLogs ("TESTE", 1); // RFID, TYPE
    medTempo ("TESTE");
    //insertLog("TESTE",1);
    //initialScreen();
    int reg = 0;
    reg = readReg(&reg);
    initialMenu(&reg);
    //listAdm();

    /*
    char *timestamp;
    checkForDB();


    snprintf(timestamp, sizeof(timestamp),"%s",time(NULL));
    insertLog("selectrfid",(long int)time, 1);
    */

    return 0;
}


/*
 * readAdm();
    char something[]="";
    readRFID(something);
    printf("%s\n", something);
 */



