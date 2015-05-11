#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>



void imprimir_prompt();
void eliminar_salto_linea(char *cad);
void leer_linea_ordenes(char *buf);

void menu_inicial();

#endif
