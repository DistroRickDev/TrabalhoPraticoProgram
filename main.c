/*
 * Projecto de grupo em linguagem C
 * Disciplina: Programação
 * Curso: SEC 1º Ano
 * Autores: Ricardo Duarte, Pedro Lima e Luis Moreira
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "admin_setup.h"
#include "admin_menu.h"
int main()
{
    int reg = 0;
    adminMenu(&reg);
    reg = readReg(&reg);
    readAdm();
    listAdm();
    //userSetup(&reg);

    return 0;
}






