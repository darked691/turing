#ifndef H_GL_DEFINITION
#define H_GL_DEFINITION
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#define TRUE 1

#define FALSE 0
int NC;
int NT;
int NR;
int NE;

typedef struct
{
	int etat_actuel;
	
	int etat_suivant;
	
	char *symbole_actuel;
	
	char *symbole_suivant;
	
	char *direction;
	
} Transition;

typedef struct 
{
  char *alpabet;
  
  Transition *table_transition;
  
  int **matrice_transition;
  
} T_machine;

typedef struct
{
	char* alphabet;
	
	int nb_etats;
	
	Transition* transition;
	
}Info_machine;	
#endif
