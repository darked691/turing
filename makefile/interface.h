#ifndef H_IN_NOUVELLE_MACHINE
#define H_IN_NOUVELLE_MACHINE
	#include <stdlib.h>
	#include <gtk/gtk.h>
	#include <stdio.h>
	#include <string.h>
	#include "definition.h"
	#define NBR_TRANSITION 1024												//Nombre de transition max autorisées
	//remember : mettre les mots dans string[NR]

	//Structure globale contenant les champs à changer lors d'un changement de transition
	typedef struct
	{
		GtkWidget* lu1;
		GtkWidget* lu2;
		GtkWidget* lu3;
		GtkWidget* ecrit1;
		GtkWidget* ecrit2;
		GtkWidget* ecrit3;
		GtkWidget* direction1;
		GtkWidget* direction2;
		GtkWidget* direction3;
		GtkWidget* liste_etat_actuel;
		GtkWidget* liste_etat_suivant;
		GtkWidget* mot_ruban1;
		GtkWidget* mot_ruban2;
		GtkWidget* mot_ruban3;
		
	}Transition_widgets;

	Info_machine G_IM;
	Transition_widgets G_widgets;
	int G_transition_actuelle;

	//retire les caractères en double d'une chaine ( afin d'éviter les doublons dans l'alphabet )
	char* retirer_duplicatas(char *str);
	
	// !! Cette fonction écrit dans la variable globale NT !!
	// Envoit les informations au gestionnaires ES pour sauvegarder
	void in_save(GtkWidget *button, gpointer data);
	
	//Ouvre une boite de dialogue permettant de changer l'alphabet courant
	void in_changer_alphabet(GtkWidget *button, gpointer data);
	
	//Initialise un "info machine" vide et le renvoi. Les champs sont initialisés à 0 avec calloc.
	Info_machine in_init_info_machine_vide();
	
	//Fenêtre regroupant toutes les opérations possible après création d'une nouvelle machine
	void in_ecran_nouvelle_machine();
	
	T_machine charger_fichier(T_machine T,char* path);
	int mdt_Initialisation(T_machine* T);
	void conversion_donne_fichier(char* path, Info_machine I);
#endif

