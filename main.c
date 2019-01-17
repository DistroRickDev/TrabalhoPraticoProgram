/*
 * Projecto de grupo em linguagem C
 * Disciplina: Programação
 * Curso: SEC 1º Ano
 * Autores: Ricardo Duarte, Pedro Lima e Luis Moreira
 */

#include <stdio.h>
#include "serial_communication.h"
#include "admin_setup.h"
#include "admin_menu.h"

int main()
{

    readAdm();
    int reg = 0;
    reg = readReg(&reg);
    //adminMenu(&reg);
    //checkAdmin(&reg);
    //listAdm();
    //serialRead();
    //admReset(&reg);
    //listAdm();
    return 0;
}






