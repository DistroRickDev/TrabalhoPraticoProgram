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
    char *timestamp;
    checkForDB();
    insertWorker("Adolf Hitler","911911911","roast",911);
    snprintf(timestamp, sizeof(timestamp),"%s",time(NULL));
    insertLog("selectrfid",(long int)time, 1);


    //int reg = 0;
    //reg = readReg(&reg);
    //adminMenu(&reg);
    //checkAdmin(&reg);
    //listAdm();
    //serialRead();
    //admReset(&reg);
    //listAdm();
    return 0;
}






