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
    readAdm();
    initialScreen();
    int reg = 0;
    reg = readReg(&reg);
    initialMenu(&reg);
    //listAdm();
    /*
    char *timestamp;
    checkForDB();
    insertWorker("Adolf Hitler","911911911","roast",911);
    snprintf(timestamp, sizeof(timestamp),"%s",time(NULL));
    insertLog("selectrfid",(long int)time, 1);
    */

    return 0;
}






