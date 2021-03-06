#include "simulateur.h"

int mdt_Hash(char* A, Ruban** R)
{

	int i,j,y,z,tmp,ER; // Soit i et j des indices , tmp une variable temporaire, ER l'état des rubans

	tmp = 0;

	ER = 0;

	z=1;



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

		for (y = 0; y < j; y++)

		{

			z*= NC;

		}

		ER += tmp * z;

	}

	return ER;

}

int mdt_Analyse_du_contexte(T_machine* T)
{
	if (T->derniere_transition != -1)
	{
		ecrire_log(T);
	}
	T->etat_rubans = mdt_Hash(T->alphabet , T->rubans);
	if (T->matrice_transition[T->etat_courant][T->etat_rubans] == -1 || T->etat_courant == EF)
	{
		if (T->etat_courant != EF)
		{
			return -2;
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

	char code[2];
	code[0] = symbole;
	code[1] = '\0';
	//err_caractere_indefini(strcat("?\0",code));
	return 0;
}

Ruban* ajouter_fin(Ruban* r, char symbole) //Ajoute une case au ruban (avant la derniere case vide)
{
	Ruban* new = malloc(sizeof(Ruban));
	new->valeur = symbole;
	Ruban* tmp = malloc(sizeof(Ruban));
	tmp = r;
	
	while(tmp->droite->droite != NULL)
	{
		tmp = tmp->droite;
	}
	new->droite = tmp->droite;
    new->gauche = tmp;
    tmp->droite->gauche = new;
	tmp->droite = new;
	return r;
}

Ruban* init_vide(Ruban* r, char* A) //Initialise un ruban vide (deux case contenant le caractère vide
{

	////printf("j'entre dans init_vide\n");
	Ruban* tmp = malloc(sizeof(Ruban));
	Ruban* tmp2 = malloc(sizeof(Ruban));
	
	tmp->valeur = A[NC -1];
	tmp2->valeur = A[NC -1];
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
	T->etat_courant = 0;

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
			else 
			{
				return 0; //Le symbole n'est pas dans l'alphabet Echec de l'initialisation
			}
			j++;
		}
		T->rubans[i] = T->rubans[i]->droite;
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
		new->droite = NULL;	
	}
	if (r->gauche == NULL && dep == 'g')
	{
		Ruban* new = malloc(sizeof(Ruban));
		new->valeur = symbole;
		r->gauche = new;
		new->droite = r;
		new->gauche = NULL;	
	}
	return r;
}

int mdt_Transition(T_machine *T)
{
	int trans = mdt_Analyse_du_contexte(T);
	int i;
	
	if (trans == -1)
	{
		for (i = 0; i < NR; i++)
		{
			while (T->rubans[i]->gauche != NULL)
			{
				T->rubans[i] = T->rubans[i]->gauche;
			}
		}
		ecrire_ruban(T->rubans,1);
		return 0; //La machine est dans l'état final
	}
	if (trans == -2)
	{
		for (i = 0; i < NR; i++)
		{
			while (T->rubans[i]->gauche != NULL)
			{
				T->rubans[i] = T->rubans[i]->gauche;
			}
		}
		ecrire_ruban(T->rubans,0);
		return -1; //La machine est bloqué dans un état non accepteur
	}
	for (i = 0; i < NR; i++)
	{
		T->rubans[i]->valeur = T->table_transition[trans].symbole_suivant[i];
		////printf("direction %c\n",T->table_transition[trans].direction[i]);
		if (T->table_transition[trans].direction[i] == 'd') //Si on va a droite
		{
			T->rubans[i] = ajouter_case(T->rubans[i], '#', 'd');
			T->rubans[i] = T->rubans[i]->droite;
		}

		if (T->table_transition[trans].direction[i] == 'g') //Si on va a gauche
		{
			T->rubans[i] = ajouter_case(T->rubans[i], '#', 'g');
			T->rubans[i] = T->rubans[i]->gauche;
		}

		if (T->table_transition[trans].direction[i] == 'c') //Si on ne bouge pas
		{
			T->rubans[i] = T->rubans[i];
		}
	}
	T->etat_courant = T->table_transition[trans].etat_suivant;
	T->derniere_transition = trans;
	return 1; //La transition est effectuée
}

void mdt_Cadencement(int T)
{
	sleep(T*30);
}

