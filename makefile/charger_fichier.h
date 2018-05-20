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
	
void init_NC_(void);
void init_NE();
void init_NT(T_machine T);
void init_NR(T_machine T);

T_machine fill_alphabet(T_machine T);
T_machine fill_transition(T_machine T);
T_machine fill_matrice_t(T_machine T);

T_machine charger_fichier(T_machine T,char* path);

void liberation_de_la_memoire(T_machine T,Info_machine I);


#endif

