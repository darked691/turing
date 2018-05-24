#ifndef H_GL_DEFINITION
#define H_GL_DEFINITION
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

int NC;
int NT;
int NR;
int NE;
int EF; //Etat final
char** mot_a_lire;


typedef struct Ruban
{
	struct Ruban* droite;
	struct Ruban* gauche;
	char valeur;
}Ruban;

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
  char *alphabet;
  int etat_courant;
  Transition *table_transition;
  int **matrice_transition;
  Ruban** rubans;
  int derniere_transition;
  int etat_rubans;
  int temps_execution;
  
} T_machine;

typedef struct
{
	char* alphabet;
	int nb_etats;
	Transition* transition;
	
}Info_machine;	
#endif
