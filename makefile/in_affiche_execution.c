#include "definition.h"

void in_afficher_execution(/*T_machine T*/)
{
	char* etat_status = "État n°999";
	char* ruban_haut_1 = "a";
	char* ruban_haut_2 = "b";
	char* ruban_haut_3 = "c";
	char* ruban_milieu_1 = "d";
	char* ruban_milieu_2 = "e";
	char* ruban_milieu_3 = "f";
	char* ruban_bas_1 = "g";
	char* ruban_bas_2 = "h";
	char* ruban_bas_3 = "i";

	//déclaration des widget et indication de leur hiérarchie
	GtkWidget* mainbox = gtk_hbox_new(TRUE, 0);
		GtkWidget* box_shift = gtk_vbox_new(TRUE, 0);
			GtkWidget* box_alignement = gtk_hbox_new(TRUE, 0);
				GtkWidget* label_alignement = gtk_label_new(" ");
		GtkWidget* box_rubans = gtk_vbox_new(TRUE, 0);
			GtkWidget* box_etat_label = gtk_hbox_new(TRUE, 0);
				GtkWidget* label_transition = gtk_label_new(etat_status);
				GtkWidget* box_ruban1 = gtk_hbox_new(TRUE, 0);
					GtkWidget* label_ruban_haut = gtk_label_new("Ruban 1 :");
					GtkWidget* bouton_ruban_1 = gtk_button_new_with_label(g_locale_to_utf8(ruban_haut_1, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_1, 50, 50);
					GtkWidget* bouton_ruban_2 = gtk_button_new_with_label(g_locale_to_utf8(ruban_haut_2, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_2, 50, 50);
					GtkWidget* bouton_ruban_3 = gtk_button_new_with_label(g_locale_to_utf8(ruban_haut_3, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_3, 50, 50);
				//space
				GtkWidget* box_ruban2 = gtk_hbox_new(TRUE, 0);
					GtkWidget* label_ruban_milieu = gtk_label_new("Ruban 2 :");
					GtkWidget* bouton_ruban_4 = gtk_button_new_with_label(g_locale_to_utf8(ruban_milieu_1, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_4, 50, 50);
					GtkWidget* bouton_ruban_5 = gtk_button_new_with_label(g_locale_to_utf8(ruban_milieu_2, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_5, 50, 50);
					GtkWidget* bouton_ruban_6 = gtk_button_new_with_label(g_locale_to_utf8(ruban_milieu_3, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_6, 50, 50);
				//space
				GtkWidget* box_ruban3 = gtk_hbox_new(TRUE, 0);
					GtkWidget* label_ruban_bas = gtk_label_new("Ruban 3 :");
					GtkWidget* bouton_ruban_7 = gtk_button_new_with_label(g_locale_to_utf8(ruban_bas_1, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_7, 50, 50);
					GtkWidget* bouton_ruban_8 = gtk_button_new_with_label(g_locale_to_utf8(ruban_bas_2, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_8, 50, 50);
					GtkWidget* bouton_ruban_9 = gtk_button_new_with_label(g_locale_to_utf8(ruban_bas_3, -1, NULL, NULL, NULL));
					gtk_widget_set_size_request (bouton_ruban_9, 50, 50);
				//space
				GtkWidget* bouton_interrompre = gtk_button_new_with_label(g_locale_to_utf8("interrompre", -1, NULL, NULL, NULL));
		GtkWidget* box_commandes = gtk_vbox_new(TRUE, 0);
			GtkWidget* box_combo_et_commandes = gtk_vbox_new(TRUE, 0);
				GtkWidget* combo_cadencement = gtk_combo_box_text_new();
				GtkWidget* commandes = gtk_hbox_new(TRUE, 0);
					GtkWidget* bouton_pause = gtk_button_new_with_label(g_locale_to_utf8("pause", -1, NULL, NULL, NULL));
					GtkWidget* bouton_start = gtk_button_new_with_label(g_locale_to_utf8("start", -1, NULL, NULL, NULL));

	
	//Initialisation de la fenêtre
	GtkWidget* mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(mainwindow), 800,600);
	gtk_signal_connect (GTK_OBJECT(mainwindow), "delete_event", GTK_SIGNAL_FUNC(gtk_exit), NULL);
	gtk_window_set_title(GTK_WINDOW(mainwindow), "Simulation en cours");
	
	//Ajout du label indiquant les états dans une boite horizontale
	gtk_box_pack_start(GTK_BOX(box_alignement), label_alignement, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_shift), box_alignement, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainbox), box_shift, TRUE, FALSE, 0);
	
	//Ajout du label indiquant l'état de la machine
	gtk_box_pack_start(GTK_BOX(box_etat_label), label_transition, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_rubans), box_etat_label, TRUE, FALSE, 0);
	
	//Ajout cases de ruban 1-9 en box horizontale
	gtk_box_pack_start(GTK_BOX(box_ruban1), label_ruban_haut, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(box_ruban1), bouton_ruban_1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban1), bouton_ruban_2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban1), bouton_ruban_3, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban2), label_ruban_milieu, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban2), bouton_ruban_4, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban2), bouton_ruban_5, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban2), bouton_ruban_6, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban3), label_ruban_bas, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban3), bouton_ruban_7, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban3), bouton_ruban_8, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_ruban3), bouton_ruban_9, TRUE, TRUE, 0);

	//Ajout des trois rubans dans une box verticale
	gtk_box_pack_start(GTK_BOX(box_rubans), box_ruban1, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_rubans), box_ruban2, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_rubans), box_ruban3, TRUE, FALSE, 0);
	
	//Ajout de l'ensemble des rubans dans la box principale
	gtk_box_pack_start(GTK_BOX(mainbox), box_rubans, TRUE, FALSE, 0);
	
	//Ajout des boutons de contrôles dans une boite horizontale
	gtk_box_pack_start(GTK_BOX(commandes), bouton_start, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(commandes), bouton_pause, TRUE, FALSE, 0);
	
	//Ajout de la boite si dessus et de la liste de cadencement dans une boite verticale
	gtk_box_pack_start(GTK_BOX(box_combo_et_commandes), combo_cadencement, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_combo_et_commandes), commandes, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box_commandes), box_combo_et_commandes, TRUE, FALSE, 0);
	
	//Ajout de l'ensemble des rubans dans la box principale
	gtk_box_pack_start(GTK_BOX(mainbox), box_commandes, TRUE, FALSE, 0);
	
	//Ajout de la boite globale dans la fenêtre
	gtk_container_add(GTK_CONTAINER(mainwindow), mainbox);
	
	//Affiche tout
	gtk_widget_show_all(mainwindow);
	//gtk_exit(0);
	
}

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	in_afficher_execution();
	gtk_main();
}
