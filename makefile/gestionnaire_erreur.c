#include <stdlib.h>
#include <stdio.h> //pour printf, à retirer
#include <string.h>
#include <gtk/gtk.h>
#include "gestionnaire_erreur.h"
#define COULEUR_ERREUR "#BB3333"
#define LONGUEUR 800
#define LARGEUR 120
int g_choice = -1;


//On cast avec "GTK_WINDOW(nom_du_widget)"
//On utilise des gchar* au lieu de char pour gtk.

void close_error(GtkButton *button, GtkWidget *mainwindow)
{
	gtk_widget_destroy(mainwindow);
}

void equalone(GtkButton *button, gpointer value)
{
	int* result = value;
	g_choice = 1;
}
void equalzero(GtkButton *button, gpointer value)
{
	int* result = value;
	g_choice = 0;
}

void err_affiche_message_ok(char* message)
{
	//Creation du "box" contenant tous nos widgets
	GtkWidget* box = gtk_vbox_new(TRUE, 0);
	
    //Création d'un pointeur pour la fenêtre principale
    GtkWidget* mainWindow = NULL;
    
    //Création du pointeur du bouton OK
    GtkWidget* buttonOk = NULL;
    
    //Création et assignation au pointeur. gtk_window_new est un peu le "new" si on était en C++
    //TOPLEVEL = fenêtre normale, POPUP = fenêtre sans bordure
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    //Choix taille de la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), LONGUEUR, LARGEUR);
    
    //Effaceur de la fenêtre
    gtk_signal_connect (GTK_OBJECT(mainWindow), "delete_event", GTK_SIGNAL_FUNC(gtk_widget_destroy), mainWindow);
    
    //titre de la fenêtre
	gtk_window_set_title(GTK_WINDOW(mainWindow), "Erreur");
	
	//Ajout du box dans la fenêtre
	gtk_container_add(GTK_CONTAINER(mainWindow), box);

	//Création du texte à afficher AVEC sa mise en page
	gchar* texte =  g_locale_to_utf8(message, -1, NULL, NULL, NULL);
	
	//Creation label et assignation du texte
	GtkWidget* label = gtk_label_new(texte);
	
	//On indique qu'il y a des balises dans le texte
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	
	//Assignation du bouton "ok"
	buttonOk = gtk_button_new_with_label(g_locale_to_utf8("ok", -1, NULL, NULL, NULL));
	
	//Ajout d'une connexion au bouton "ok"
	gtk_signal_connect(GTK_OBJECT(buttonOk), "released", G_CALLBACK(close_error), mainWindow);
	
	//Ajout du label dans le "box"
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 1);
	
	//Ajout du bouton dans le "box"
	gtk_box_pack_start(GTK_BOX(box), buttonOk, FALSE, FALSE, 8);
	
	//Actualisation affichage
	gtk_widget_show_all(mainWindow);
	
	//Boucle évènementielle
	gtk_main();
}

int err_affiche_message_YN(char* message)
{
	int choice = -1;
	//Creation du "box" contenant tous nos widgets
	GtkWidget* box = gtk_vbox_new(TRUE, 0);
	GtkWidget* boxbutton = gtk_hbox_new(TRUE, 0);
	
    //Création d'un pointeur pour la fenêtre principale
    GtkWidget* mainWindow = NULL;
    
    //Création du pointeur des boutons yes/no
    GtkWidget* buttonYes = NULL;
    GtkWidget* buttonNo = NULL;
    
    //Création et assignation au pointeur. gtk_window_new est un peu le "new" si on était en C++
    //TOPLEVEL = fenêtre normale, POPUP = fenêtre sans bordure
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    //Choix taille de la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), LONGUEUR, LARGEUR);
    
    //Effaceur de la fenêtre
    gtk_signal_connect (GTK_OBJECT(mainWindow), "delete_event", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
    
    //titre de la fenêtre
	gtk_window_set_title(GTK_WINDOW(mainWindow), "Erreur");
	
	//Ajout du box dans la fenêtre
	gtk_container_add(GTK_CONTAINER(mainWindow), box);

	//Création du texte à afficher AVEC sa mise en page
	gchar* texte =  g_locale_to_utf8(message, -1, NULL, NULL, NULL);
	
	//Creation label et assignation du texte
	GtkWidget* label = gtk_label_new(texte);
	
	//On indique qu'il y a des balises dans le texte
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	
	//Assignation du bouton "ok"
	buttonYes = gtk_button_new_with_label(g_locale_to_utf8("Remplacer", -1, NULL, NULL, NULL));
	buttonNo = gtk_button_new_with_label(g_locale_to_utf8("Annuler", -1, NULL, NULL, NULL));
	
	//Ajout d'une connexion au bouton "ok"
	gtk_signal_connect(GTK_OBJECT(buttonYes), "released", G_CALLBACK(equalone), &choice);
	gtk_signal_connect(GTK_OBJECT(buttonYes), "released", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	
	//Ajout d'une connexion au bouton annuler
	gtk_signal_connect(GTK_OBJECT(buttonNo), "released", G_CALLBACK(equalzero), &choice);
	gtk_signal_connect(GTK_OBJECT(buttonNo), "released", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	
	//Ajout du label dans le "box"
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
	
	//Ajout du box des boutons dans le box de la fenêtre
	gtk_container_add(GTK_CONTAINER(box), boxbutton);
	
	//Ajout du bouton dans le "box"
	gtk_box_pack_start(GTK_BOX(boxbutton), buttonYes, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(boxbutton), buttonNo, FALSE, FALSE, 0);
	
	//Actualisation affichage
	gtk_widget_show_all(mainWindow);
	
	//Boucle évènementielle
	gtk_main();
	
	//g_free(label);
    return g_choice;
}

void err_format(char* code)
{
	char* message = malloc(sizeof(char) * (strlen(code) + strlen("<span foreground=\""COULEUR_ERREUR"\"><b>Erreur</b></span> : format du fichier .mdt incorrect. Erreur détéctée à la ligne ")));

	strcpy(message, "<span foreground=\""COULEUR_ERREUR"\"><b>Erreur</b></span> : format du fichier .mdt incorrect. Erreur détéctée à la ligne ");
	strcat(message, code); 
	err_affiche_message_ok(message);
	free(message);
}

void err_introuvable(char* code)
{
	char* message = malloc(sizeof(char) * (strlen(code) + strlen(" est accessible et existe bien.") + strlen("<span foreground=\""COULEUR_ERREUR"\"><b>Erreur</b></span> : fichier spécifié introuvable ou protégé en lecture.\n Veuillez vérifier que le fichier ")));

	strcpy(message, "<span foreground=\""COULEUR_ERREUR"\"><b>Erreur</b></span> : fichier spécifié introuvable ou protégé en lecture.\nVeuillez vérifier que le fichier ");
	strcat(message, code);
	strcat(message, " est accessible et existe bien.");
	err_affiche_message_ok(message);
	free(message);
}

int err_existant(char* code)
{
	char* message = malloc(sizeof(char) * (strlen(code) + strlen(" existe déjà.\n               Voulez vous le remplacer ?") + strlen("<span><b>Attention</b></span> : Le fichier ")));
	
	strcpy(message, "<span><b>Attention</b></span> : Le fichier ");
	strcat(message, code);
	strcat(message, " existe déjà.\n               Voulez vous le remplacer ?");
	err_affiche_message_YN(message);
	
	free(message);
	return 0;
}

void err_caractere_indefini(char* code)
{
	char* etat = malloc(sizeof(char) * 4);
	char* caractere = malloc(sizeof(char)*1);
	char* message = malloc(sizeof(char) * (strlen("<span foreground=\""COULEUR_ERREUR"\"><b>Erreur</b></span> : le caractère \"") + 1 + strlen("\" existe dans une transition à l'état ") + 4 + strlen(" mais est introuvable dans l'alphabet")));
	
	etat[0] = code[1];
	if(code[2] != ']')
	{
		etat[1] = code[2];
	}
	if(code[2] != ']' && code[3] != ']')
	{
		etat[2] = code[3];
	}
	caractere[0] = code[strlen(code)-2];
	
	strcpy(message, "<span foreground=\""COULEUR_ERREUR"\"><b>Erreur</b></span> : le caractère \"");
	strcat(message, caractere);
	strcat(message, "\" existe dans une transition à l'état ");
	strcat(message, etat);
	strcat(message, " mais est introuvable dans l'alphabet.");
	
	err_affiche_message_ok(message);
	
	free(etat);
	free(message);
	free(caractere);
}

//Ce message et ce qui suit sont des tests, ils peuvent être supprimés.
//~ int main(int argc, char **argv)
//~ {
	//~ /* Initialisation de GTK+. Sera fait plus tôt dans le programme final ! */
	//~ gtk_init(&argc, &argv);
	//~ //test de fenêtre classique, le format à respecter pour l'argument d'une des fonctions "err_" est indiqué dans les specs, respectez le à la lettre !
	//~ err_format("3");
	//~ printf("%d\n", g_choice); 
	//~ //err_existant("fichier.mdt");
	//~ err_format("89"); 
	//~ printf("%d\n", g_choice); 
    //~ return EXIT_SUCCESS;
//~ }

