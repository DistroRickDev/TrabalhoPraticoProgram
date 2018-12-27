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

int main()
{
    char token[20];
    int regis = 0;
    user_setup(&regis);
    check_Admin(&regis);
    //printf("The token is :%s\n", tokenGenerator(token));
}






