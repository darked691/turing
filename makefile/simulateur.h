#include "definition.h"
#ifndef H_GL_SIMULATEUR
#define H_GL_SIMULATEUR
int mdt_Analyse_du_contexte(T_machine* T); //Changement de signature vis à vis des specs

int mdt_Transition(T_machine* T);

int mdt_Initialisation(T_machine* T);

int mdt_Hash(char* A, Ruban** R);

void mdt_Cadencement(int* TE);

int test_alpha(char symbole, char* A);

Ruban* ajouter_fin(Ruban* r, char symbole);

Ruban* init_vide(Ruban* r, char* A);

Ruban* ajouter_case(Ruban* r, char symbole, char dep);
#endif
