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

int main() {
    int reg = 0;
    reg = readReg(&reg);
    1initialMenu(&reg);

    //listAdm();


    return 0;
}

