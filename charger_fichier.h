
#ifndef H_GL_CHARGER
#define H_GL_CHARGER
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include "definition.h"
	
void init_NC_(char* path);
void init_NE(char* path);
void init_NT(char* path);
void init_NR(char* path);
void init_EF(char* path);

T_machine fill_alphabet(T_machine T,char *path);
T_machine fill_transition(T_machine T,char* path);
T_machine fill_matrice_t(T_machine T);

T_machine charger_fichier(T_machine T,char* path);

void liberation_de_la_memoire(T_machine T);


#endif
