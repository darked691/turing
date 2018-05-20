#include "simulateur.h"
int mdt_Hash(char* A, Ruban** R)
{
	int i,j,tmp,ER; // Soit i et j des indices , tmp une variable temporaire, ER l'état des rubans
	tmp = 0;
	ER = 0;
	for (j = 0; j < NR; j++) // Pour tout les rubans
	{
		for (i = 0; i < NC; i++) // On parcourt l'alphabet
		{
			if (R[j]->valeur == A[i]) // Si le symbole est dans l'alphabet
			{
				tmp = i; // Tmp prend la valeur du symbole
				break; // On met fin à la boucle
			}
		}
		ER += tmp * (NC^(j)); //On assigne le résultat à ER
	}
	return ER;
}
/* 
Cette fonction recherche la place dans l'alphabet du symbole sur chaque tête de
lecture la présence de ces symboles dans l'alphabet est assurée par l'initialisation
une seconde vérification n'est donc pas nécessaire
*/

int mdt_Analyse_du_contexte(T_machine* T)
{
	//es_ecriture_log();
	T->etat_rubans = mdt_Hash(T->alphabet , T->rubans);
	
	if (T->matrice_transition[T->etat_courant][T->etat_rubans] == -1)
	{
		if (T->etat_rubans != EF)
		{
			return -2;
			//err_transition();
		}
		else
		{
			return -1; // La machine est dans l'état final
		}
	}
	return T->matrice_transition[T->etat_courant][T->etat_rubans]; // Retourne le numéro de la prochaine transition
	
}

int test_alpha(char symbole, char* A) //Teste si le symbole donné est dans l'alphabet A
{
	int i;
	for (i = 0; i < NC; i++)
	{
		if (symbole == A[i])
		{
			return 1;
		}
	}
	// err_carac_indefini();
	return 0;
}

Ruban* ajouter_fin(Ruban* r, char symbole) //Ajoute une case au ruban (avant la derniere case vide)
{
	Ruban* new = malloc(sizeof(Ruban));
	new->valeur = symbole;
	
	Ruban* tmp = r;
	while(tmp->droite->droite != NULL)
	{
		tmp = tmp->droite;
	}
	tmp->droite->gauche = new;
	tmp->gauche->droite = new;
	new->gauche = tmp->gauche;
	new->droite =tmp;
	
	return r;
}

Ruban* init_vide(Ruban* r, char* A) //Initialise un ruban vide (deux case contenant le caractère vide
{
	Ruban* tmp = malloc(sizeof(Ruban));
	Ruban* tmp2 = malloc(sizeof(Ruban));
	
	tmp->valeur = A[0];
	tmp2->valeur = A[0];
	
	tmp->droite = tmp2;
	tmp->gauche = NULL;
	tmp2->droite = NULL;
	tmp2->gauche = tmp;
	
	return tmp;
}

int mdt_Initialisation(T_machine* T) //Initialise les rubans avec le mot recu en entrée
{
	int i,j;
	T->derniere_transition = -1;
	for (i = 0; i < NR; i++)
	{
		T->rubans[i] = init_vide(T->rubans[i], T->alphabet);
		j=0;
		while (mot_a_lire[i][j] != '\0')
		{
			if (test_alpha(mot_a_lire[i][j],T->alphabet))
			{
				ajouter_fin(T->rubans[i],mot_a_lire[i][j]);
			}
			else return 0; //Le symbole n'est pas dans l'alphabet Echec de l'initialisation
			j++;
		}
	}
	return 1; //Initialisation réussie
}

Ruban* ajouter_case(Ruban* r, char symbole, char dep)
{
	if (r->droite == NULL && dep == 'd')
	{
		Ruban* new = malloc(sizeof(Ruban));
		new->valeur = symbole;
		r->droite = new;
		new->gauche = r;	
	}
	if (r->gauche == NULL && dep == 'g')
	{
		Ruban* new = malloc(sizeof(Ruban));
		new->valeur = symbole;
		r->gauche = new;
		new->droite = r;
	}
	return r;
	
}

int mdt_Transition(T_machine *T)
{
	int trans = mdt_Analyse_du_contexte(T);
	int i;
	
	if (trans == -1)
	{
		return 0; //La machine est dans l'état final
	}
	if (trans == -2)
	{
		return -1; //La machine est bloqué dans un état non accepteur
	}
	
	for (i = 0; i < NR; i++)
	{
		T->rubans[i]->valeur = T->table_transition[trans].symbole_suivant[i];
		
		if (T->table_transition[trans].direction[i] == 'd') //Si on va a droite
		{
			T->rubans[i] = ajouter_case(T->rubans[i], T->alphabet[0], 'd');
			T->rubans[i] = T->rubans[i]->droite;
		}
		if (T->table_transition[trans].direction[i] == 'g') //Si on va a gauche
		{
			T->rubans[i] = ajouter_case(T->rubans[i], T->alphabet[0], 'g');
			T->rubans[i] = T->rubans[i]->gauche;
		}
		if (T->table_transition[trans].direction[i] == 'c') //Si on ne bouge pas
		{
			T->rubans[i] = T->rubans[i];
		}
	}
	
	T->derniere_transition = trans;
	return 1; //La transition est effectuée
}

