#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#define NBR_TRANSITION 1024												//Nombre de transition max autorisées
//remember : mettre les mots dans string[NR]

char* retirer_duplicatas(char *str)
{
    char marqueur[256] = {0}; 
    int  i = 0;
    int  j = 0;

    for(i=0; str[i] != '\0'; i++)
    {
        if(0 == marqueur[str[i]]) 
        {
            marqueur[str[i]] = 1;
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
    return str;
}

void in_save(GtkWidget *button, gpointer data)
{
	
	GtkWidget* explorateur;
	int action;
	explorateur = gtk_file_chooser_dialog_new (	"Séléctionnez le fichier .mdt",
												NULL,
												GTK_FILE_CHOOSER_ACTION_OPEN,
												GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
												GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
												NULL);
	action = gtk_dialog_run(GTK_DIALOG (explorateur));
	if( action == GTK_RESPONSE_ACCEPT)
	{
		char* chemin = "tmp";
		printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (explorateur)));
		chemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (explorateur));
		gtk_widget_destroy(explorateur);
		NT = NBR_TRANSITION;
		conversion_donne_fichier(chemin, G_IM);
	}
	else if (action == GTK_RESPONSE_CANCEL)
	{
		gtk_widget_destroy(explorateur);
	}

}

void in_changer_alphabet(GtkWidget *button, gpointer data)
{
	int action;
	
	//Création et propriété/flags de la boite de dialogue
	GtkWidget* choix_alphabet = gtk_dialog_new_with_buttons("Choisissez l'alphabet", 
															NULL, 
															GTK_DIALOG_MODAL,
															GTK_STOCK_OK,GTK_RESPONSE_OK,
															GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
															NULL);
															
	//Préparation de la boite de dialogue														
	GtkWidget* saisie = gtk_entry_new_with_max_length(127); //Les cases de 0 à 126 peuvent être remplies, mais on garde 127 pour le caractère blanc
	gtk_window_set_default_size(GTK_WINDOW(choix_alphabet), 300, 100);
    gtk_entry_set_text(GTK_ENTRY(saisie), G_IM.alphabet);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(choix_alphabet)->vbox), saisie, TRUE, FALSE, 0);
    gtk_widget_show_all(GTK_DIALOG(choix_alphabet)->vbox);
    
    //Ouverture de la boite et attente d'une action de l'utilisateur
	action = gtk_dialog_run(GTK_DIALOG(choix_alphabet));
	if(action == GTK_RESPONSE_OK)
	{
		G_IM.alphabet = retirer_duplicatas(strdup(gtk_entry_get_text(GTK_ENTRY(saisie))));
		strcat(G_IM.alphabet, "#");
		gtk_widget_destroy(choix_alphabet);
	}
	else if(action == GTK_RESPONSE_CANCEL)
	{
		gtk_widget_destroy(choix_alphabet);
	}
}

void in_executer(GtkWidget *button, gpointer data)
{
	;
}
//écrit dans "G_transition_actuelle"
void in_change_transition(GtkWidget *combo, gpointer data)
{
	char char_tmp[1];
	int int_tmp;

	G_transition_actuelle = atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo)));
	if(G_transition_actuelle >= 0 && G_transition_actuelle < NBR_TRANSITION)
	{
		//Remplissage des symboles lus
		char_tmp[0] = G_IM.transition[G_transition_actuelle].symbole_actuel[0];
		gtk_entry_set_text(GTK_ENTRY(widgets.lu1), char_tmp);
		char_tmp[0] = G_IM.transition[G_transition_actuelle].symbole_actuel[1];
		gtk_entry_set_text(GTK_ENTRY(widgets.lu2), char_tmp);
		char_tmp[0] = G_IM.transition[G_transition_actuelle].symbole_actuel[2];
		gtk_entry_set_text(GTK_ENTRY(widgets.lu3), char_tmp);
		
		//Remplissage des symboles à écrire
		char_tmp[0] = G_IM.transition[G_transition_actuelle].symbole_suivant[0];
		gtk_entry_set_text(GTK_ENTRY(widgets.ecrit1), char_tmp);
		char_tmp[0] = G_IM.transition[G_transition_actuelle].symbole_suivant[1];
		gtk_entry_set_text(GTK_ENTRY(widgets.ecrit2), char_tmp);
		char_tmp[0] = G_IM.transition[G_transition_actuelle].symbole_suivant[2];
		gtk_entry_set_text(GTK_ENTRY(widgets.ecrit3), char_tmp);
		
		//Remplissage des directions à prendre
		char_tmp[0] = G_IM.transition[G_transition_actuelle].direction[0];
		gtk_entry_set_text(GTK_ENTRY(widgets.direction1), char_tmp);
		char_tmp[0] = G_IM.transition[G_transition_actuelle].direction[1];
		gtk_entry_set_text(GTK_ENTRY(widgets.direction2), char_tmp);
		char_tmp[0] = G_IM.transition[G_transition_actuelle].direction[2];
		gtk_entry_set_text(GTK_ENTRY(widgets.direction3), char_tmp);
		
		//Actualisation des états correspondant à la transition
		int_tmp = G_IM.transition[G_transition_actuelle].etat_actuel;
		gtk_combo_box_set_active(GTK_COMBO_BOX(widgets.liste_etat_actuel), int_tmp);
		int_tmp = G_IM.transition[G_transition_actuelle].etat_suivant;
		gtk_combo_box_set_active(GTK_COMBO_BOX(widgets.liste_etat_suivant), int_tmp);
	}
}

void in_update(GtkWidget *entry, gpointer data)
{
	const gchar* char_tmp;
	
	//Remplissage des symboles à lire dans le tableau de transition. On les sauvegarde dans IM
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.lu1));
	G_IM.transition[G_transition_actuelle].symbole_actuel[0] = char_tmp[0];
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.lu2));
	G_IM.transition[G_transition_actuelle].symbole_actuel[1] = char_tmp[0];
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.lu3));
	G_IM.transition[G_transition_actuelle].symbole_actuel[2] = char_tmp[0];
	
	//Remplissage des symboles à écrire dans le tableau de transition. On les sauvegarde dans IM
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.ecrit1));
	G_IM.transition[G_transition_actuelle].symbole_suivant[0] = char_tmp[0];
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.ecrit2));
	G_IM.transition[G_transition_actuelle].symbole_suivant[1] = char_tmp[0];
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.ecrit3));
	G_IM.transition[G_transition_actuelle].symbole_suivant[2] = char_tmp[0];
	
	//Remplissage des directions de tête de curseur à effectuer. On les sauvegarde dans IM
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.direction1));
	G_IM.transition[G_transition_actuelle].direction[0] = char_tmp[0];
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.direction2));
	G_IM.transition[G_transition_actuelle].direction[1] = char_tmp[0];
	char_tmp = gtk_entry_get_text(GTK_ENTRY(widgets.direction3));
	G_IM.transition[G_transition_actuelle].direction[2] = char_tmp[0];
	
	//Remplissage des états indiqués par l'utilisateur. On sauvegarde dans IM.
	G_IM.transition[G_transition_actuelle].etat_actuel = atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgets.liste_etat_actuel)));
	G_IM.transition[G_transition_actuelle].etat_suivant = atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgets.liste_etat_suivant)));
}

Info_machine in_init_info_machine_vide()
{
	Info_machine IM;
	int i = 1024;
	int j = 0;
	
	IM.alphabet = malloc(sizeof(char) * 128);								//Alphabet possède 128 caractères
	IM.alphabet[0] = '0';													//Caractère 0 est de base dans l'alphabet
	IM.alphabet[1] = '1';													//Caractère 1 est de base dans l'alphabet
	for(j = 2;j<127;j++)
	{
		IM.alphabet[j] = '\0';
	}
	IM.alphabet[127] = '\0';												//Le dernier caractère de l'alphabet est le "caractère blanc", obligatoire dans une machine de Turing
	IM.nb_etats = 128;														//Deux états obligatoires : initial et final. On sait que l'état 0 est le premier, et que l'état "nb_etats" est l'unique accepteur.
	IM.transition = malloc(sizeof(Transition) * NBR_TRANSITION);			//Max 1024 transition pour le moment
	while(i > 0)
	{
		IM.transition[i-1].symbole_actuel = calloc(3, sizeof(char));		//1 symbole par ruban. symbole_actuel[0] = premier ruban... etc
		//IM.transition[0].symbole_actuel = 0;
		IM.transition[i-1].symbole_suivant = calloc(3, sizeof(char));		//1 symbole à remplacer par ruban
		IM.transition[i-1].direction = calloc(3, sizeof(char));			//une direction par ruban
		IM.transition[i-1].etat_actuel = 0;
		IM.transition[i-1].etat_suivant = 0;
		i--;
	}
	return IM;
}

void in_ecran_nouvelle_machine()
{
	int once = 1;
	char str_tmp[12];
	int i = 0;
	G_transition_actuelle = 0;
	
	//On initialise une seule fois la machine
	if(once)
	{
		G_IM = in_init_info_machine_vide();		
		once = 0;
	}
	
	//Widgets globaux
	GtkWidget* space = gtk_label_new("\n"); //ajoute un espace entre deux widgets
	GtkWidget* shift = gtk_label_new(" "); //Ajoute un espace vide pour aligner

	//déclaration des widget et indication de leur hiérarchie
	GtkWidget* mainbox = gtk_vbox_new(TRUE, 0);
		GtkWidget* sauvegarder_executer = gtk_hbox_new(TRUE, 0);
			GtkWidget* bouton_sauvegarde = gtk_button_new_with_label(g_locale_to_utf8("Sauvegarder", -1, NULL, NULL, NULL));	
			GtkWidget* bouton_executer = gtk_button_new_with_label(g_locale_to_utf8("Exécuter", -1, NULL, NULL, NULL));	
		GtkWidget* liste_et_transition = gtk_hbox_new(TRUE, 0);
			GtkWidget* listes_et_labels = gtk_hbox_new(TRUE,0);
				GtkWidget* listes_label = gtk_vbox_new(TRUE, 0);	
					GtkWidget* ecrit_transition = gtk_label_new("Transition actuelle");
					GtkWidget* label_entree1 = gtk_label_new("Entrée ruban 1");
					GtkWidget* label_entree2 = gtk_label_new("Entrée ruban 2");
					GtkWidget* label_entree3 = gtk_label_new("Entrée ruban 3");
				GtkWidget* listes = gtk_vbox_new(TRUE, 0);	
					GtkWidget* liste_transition = gtk_combo_box_text_new_with_entry();			
					GtkWidget* bouton_alphabet = gtk_button_new_with_label(g_locale_to_utf8("Modifier l'alphabet", -1, NULL, NULL, NULL));
					GtkWidget* entree1 = gtk_entry_new();
					GtkWidget* entree2 = gtk_entry_new();
					GtkWidget* entree3 = gtk_entry_new();
			GtkWidget* transition = gtk_vbox_new(FALSE, 0);
				GtkWidget* label_ruban = gtk_hbox_new(TRUE, 0);
					GtkWidget* label_ruban1 = gtk_label_new("Ruban 1");
					GtkWidget* label_ruban2 = gtk_label_new("Ruban 2");
					GtkWidget* label_ruban3 = gtk_label_new("Ruban 3");
				GtkWidget* caractere_lu = gtk_hbox_new(TRUE, 0);
					GtkWidget* lu_label = gtk_label_new("Caractère lu :");
					GtkWidget* lu1 = gtk_entry_new_with_max_length(1);
					GtkWidget* lu2 = gtk_entry_new_with_max_length(1);
					GtkWidget* lu3 = gtk_entry_new_with_max_length(1);
				GtkWidget* caractere_ecrit = gtk_hbox_new(TRUE, 0);
					GtkWidget* ecrit_label = gtk_label_new("Caractère à écrire :");
					GtkWidget* ecrit1 = gtk_entry_new_with_max_length(1);
					GtkWidget* ecrit2 = gtk_entry_new_with_max_length(1);
					GtkWidget* ecrit3 = gtk_entry_new_with_max_length(1);
				GtkWidget* direction = gtk_hbox_new(TRUE, 0);
					GtkWidget* direction_label = gtk_label_new("Déplacement :");
					GtkWidget* direction1 = gtk_entry_new_with_max_length(1);
					GtkWidget* direction2 = gtk_entry_new_with_max_length(1);
					GtkWidget* direction3 = gtk_entry_new_with_max_length(1);
				GtkWidget* etat_actuel = gtk_hbox_new(TRUE, 0);
					GtkWidget* etat_actuel_label = gtk_label_new("Etat actuel");
					GtkWidget* liste_etat_actuel = gtk_combo_box_text_new_with_entry();
				GtkWidget* etat_suivant = gtk_hbox_new(TRUE, 0);
					GtkWidget* etat_suivant_label = gtk_label_new("Etat suivant");
					GtkWidget* liste_etat_suivant = gtk_combo_box_text_new_with_entry();
				GtkWidget* valider = gtk_hbox_new(TRUE, 0);
					GtkWidget* bouton_valider = gtk_button_new_with_label(g_locale_to_utf8("Valider la transition", -1, NULL, NULL, NULL));
	//Remplissage de la structure permettant d'actualiser le tableau de transition
	widgets.lu1 = lu1;
	widgets.lu2 = lu2;
	widgets.lu3 = lu3;
	widgets.ecrit1 = ecrit1;
	widgets.ecrit2 = ecrit2;
	widgets.ecrit3 = ecrit3;
	widgets.direction1 = direction1;
	widgets.direction2 = direction2;
	widgets.direction3 = direction3;
	widgets.liste_etat_actuel = liste_etat_actuel;
	widgets.liste_etat_suivant = liste_etat_suivant;
	
	//Remplissage des listes d'états et de la liste des transitions
	while(i < G_IM.nb_etats)
	{
		sprintf(str_tmp, "%d", i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (liste_etat_suivant), str_tmp);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (liste_etat_actuel), str_tmp);
		i++;
	}
	for(i=0; i < NBR_TRANSITION; i++)
	{
		sprintf(str_tmp, "%d", i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (liste_transition), str_tmp);
	}
	
	//Initialisation de la fenêtre
	GtkWidget* mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(mainwindow), 800,600);
	gtk_signal_connect (GTK_OBJECT(mainwindow), "delete_event", GTK_SIGNAL_FUNC(gtk_exit), NULL);
	gtk_window_set_title(GTK_WINDOW(mainwindow), "Ecriture de la machine de Turing");
	
	//Ajout de la ligne ruban 1, ruban 2 ... 
	gtk_box_pack_start(GTK_BOX(label_ruban), shift, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(label_ruban), label_ruban1, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(label_ruban), label_ruban2, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(label_ruban), label_ruban3, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(transition), label_ruban, TRUE, FALSE, 0);
	
	//Ajout de la ligne "caractere lu" dans le tableau de transition
	gtk_box_pack_start(GTK_BOX(caractere_lu), lu_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(caractere_lu), lu1, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(caractere_lu), lu2, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(caractere_lu), lu3, TRUE, FALSE, 0);
	
	//Ajout de la ligne "caractere à écrire" dans le tableau de transition
	gtk_box_pack_start(GTK_BOX(caractere_ecrit), ecrit_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(caractere_ecrit), ecrit1, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(caractere_ecrit), ecrit2, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(caractere_ecrit), ecrit3, TRUE, FALSE, 0);
	
	//Ajout de la ligne "direction" dans le tableau de transition
	gtk_box_pack_start(GTK_BOX(direction), direction_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(direction), direction1, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(direction), direction2, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(direction), direction3, TRUE, FALSE, 0);
	
	//ajout de la ligne "etat actuel" dans le tableau de transition
	gtk_box_pack_start(GTK_BOX(etat_actuel), etat_actuel_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(etat_actuel), liste_etat_actuel, TRUE, FALSE, 0);
	
	//ajout de la ligne "etat suivant" dans le tableau de transition
	gtk_box_pack_start(GTK_BOX(etat_suivant), etat_suivant_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(etat_suivant), liste_etat_suivant, TRUE, FALSE, 0);
	
	//Ajout du bouton "valider" dans la boite
	gtk_box_pack_start(GTK_BOX(valider), bouton_valider, TRUE, FALSE, 0);
	
	//ajout des 5 boites remplies ci dessus dans une "boite" verticale afin de les ordonner de haut en bas
	gtk_box_pack_start(GTK_BOX(transition), caractere_lu, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(transition), caractere_ecrit, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(transition), direction, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(transition), etat_actuel, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(transition), etat_suivant, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(transition), valider, TRUE, FALSE, 0);
	
	//Ajout des labels dans une boite verticale afin de les ordonner de haut en bas
	gtk_box_pack_start(GTK_BOX(listes_label), ecrit_transition, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes_label), space, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes_label), label_entree1, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes_label), label_entree2, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes_label), label_entree3, TRUE, FALSE, 0);
	
	//Ajout des deux listes de choix dans une boite verticale afin de les ordonner de haut en bas
	gtk_box_pack_start(GTK_BOX(listes), liste_transition, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes), bouton_alphabet, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes), entree1, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes), entree2, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes), entree3, TRUE, FALSE, 0);
	
	//Ajout des listes et de leurs labels dans une boite horizontale
	gtk_box_pack_start(GTK_BOX(listes_et_labels), listes_label, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(listes_et_labels), listes, TRUE, FALSE, 0);
	
	//Ajout de transition et listes dans une boite horizontale afin de les ordonner
	gtk_box_pack_start(GTK_BOX(liste_et_transition), listes_et_labels, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(liste_et_transition), transition, TRUE, FALSE, 0);
	
	//Ajout des boutons sauvegarder et executer dans une boite horizontale pour les ordonner
	gtk_box_pack_start(GTK_BOX(sauvegarder_executer), bouton_sauvegarde, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(sauvegarder_executer), bouton_executer, TRUE, FALSE, 0);
	
	//Ajout de la boite sauvegarder/execution et de la boite gérant les transitions, dans la boite globale
	gtk_box_pack_start(GTK_BOX(mainbox), liste_et_transition, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainbox), sauvegarder_executer, TRUE, FALSE, 0);
	
	//Ajout de la boite globale dans la fenêtre principale
	gtk_container_add(GTK_CONTAINER(mainwindow), mainbox);
	
	//Actualise le tableau de transition lors d'un changement de transition
	gtk_signal_connect(GTK_OBJECT(liste_transition), "changed", G_CALLBACK(in_change_transition), NULL);
	
	//Enregistre toute modification d'un champ du tableau de transition ou de l'état, dans info machine
	gtk_signal_connect(GTK_OBJECT(bouton_valider), "clicked", G_CALLBACK(in_update), NULL);
	
	//Lance l'exécution de la machine
	gtk_signal_connect(GTK_OBJECT(bouton_executer), "clicked", G_CALLBACK(in_executer), NULL);
	
	//Envoi la machine au gestionnaire entrées/sorties lors d'un clic sur le bouton sauvegarder
	gtk_signal_connect(GTK_OBJECT(bouton_sauvegarde), "clicked", G_CALLBACK(in_save), NULL);
	
	//Ouvre une boite de dialogue permettant de changer l'alphabet
	gtk_signal_connect(GTK_OBJECT(bouton_alphabet), "clicked", G_CALLBACK(in_changer_alphabet), NULL);
	
	//Affiche tout
	gtk_widget_show_all(mainwindow);
	//gtk_exit(0);
	
}
