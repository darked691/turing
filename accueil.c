#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "clear.c"
/*
in_accueil:
	gcc `pkg-config --libs --cflags gtk+-2.0` in_accueil.c -o nom_de_lexecutable
	./nom_de_lexecutable
*/

void pri(GtkWidget *pEntry, gpointer data){
	char* st = data;						// On cast le void*
}
char *concat_string(char *s1,char *s2)
{
     char *s3=NULL;
     s3=(char *)malloc((strlen(s1)+strlen(s2))*sizeof(char));
     strcpy(s3,s1);
     strcat(s3,s2);
     return s3;
     }
char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    
    return b;
}



void in_nouvelle_machine_call(GtkWidget *pButon, gpointer data){
	clear(data);
	in_ecran_nouvelle_machine(data);

}


void in_charger_machine_call(GtkWidget *pButon, gpointer data){
	GtkWidget* explorateur;
	int action;
	explorateur = gtk_file_chooser_dialog_new (	"charger fichier .mdt",
												NULL,
												GTK_FILE_CHOOSER_ACTION_OPEN,
												GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
												GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
												NULL);
												
	action = gtk_dialog_run(GTK_DIALOG (explorateur));
	if(action == GTK_RESPONSE_ACCEPT)
	{
		char* chemin = "tmp";
		chemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (explorateur));
		gtk_widget_destroy(explorateur);
		clear(data);
		in_ecran_charger_machine(chemin, data);
	}
	else if (action == GTK_RESPONSE_CANCEL)
	{
		gtk_widget_destroy(explorateur);
	}
}


void afficher_accueil(){
GtkWidget *pWindow;
		GtkWidget *pVBox;
			GtkWidget *pHBox1;
			    GtkWidget *pButton1;
			GtkWidget *pHBox2;
				GtkWidget *pButton4;
			GtkWidget *pHBox3;
				GtkWidget *pButton7;


    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Accueil");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 800, 600);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
	pVBox = gtk_vbox_new(TRUE, 10);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    
    pHBox2 = gtk_hbox_new(TRUE, 0);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pVBox), pHBox2);
    pHBox1 = gtk_hbox_new(TRUE, 0);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pVBox), pHBox1);
	pHBox3 = gtk_hbox_new(TRUE, 0);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pVBox), pHBox3);
	
    ///
    ///
   
    pButton1 = gtk_button_new_with_label(g_locale_to_utf8("Charger", -1, NULL, NULL, NULL));
    	gtk_widget_set_size_request(pButton1, 150, 10);
		gtk_box_pack_start(GTK_BOX(pHBox1), pButton1, TRUE, FALSE, 0);
		g_signal_connect(G_OBJECT(pButton1), "clicked", G_CALLBACK(in_charger_machine_call),pWindow );
		

    ///
	///
	
    pButton4 = gtk_button_new_with_label(g_locale_to_utf8("Nouvelle machine", -1, NULL, NULL, NULL));
    	gtk_widget_set_size_request(pButton4, 150, 10);
		gtk_box_pack_start(GTK_BOX(pHBox2), pButton4, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(pButton4), "clicked", G_CALLBACK(in_nouvelle_machine_call), pWindow);
		
    ///
	///
	
	
    pButton7 = gtk_button_new_with_label(g_locale_to_utf8("Quitter", -1, NULL, NULL, NULL));
    	gtk_widget_set_size_request(pButton7, 150, 10);
		gtk_box_pack_start(GTK_BOX(pHBox3), pButton7, TRUE, FALSE, 0);
	    g_signal_connect(G_OBJECT(pButton7), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	
    gtk_widget_show_all(pWindow);
}



void re_afficher_accueil(GtkWidget *pButon, gpointer data){
GtkWidget *pWindow=data;
clear(pWindow);
		GtkWidget *pVBox;
			GtkWidget *pHBox1;
			    GtkWidget *pButton1;
			GtkWidget *pHBox2;
				GtkWidget *pButton4;
			GtkWidget *pHBox3;
				GtkWidget *pButton7;

   // pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Accueil");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 800, 600);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
	pVBox = gtk_vbox_new(TRUE, 10);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    pHBox2 = gtk_hbox_new(TRUE, 0);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pVBox), pHBox2);
    pHBox1 = gtk_hbox_new(TRUE, 0);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pVBox), pHBox1);
	pHBox3 = gtk_hbox_new(TRUE, 0);// 0 = l'espace entre
    gtk_container_add(GTK_CONTAINER(pVBox), pHBox3);
	
	
    pButton1 = gtk_button_new_with_label(g_locale_to_utf8("Charger", -1, NULL, NULL, NULL));
    gtk_widget_set_size_request(pButton1, 150, 10);
	gtk_box_pack_start(GTK_BOX(pHBox1), pButton1, TRUE, FALSE, 0);
	g_signal_connect(G_OBJECT(pButton1), "clicked", G_CALLBACK(in_charger_machine_call),pWindow );
		 
    ///
    ///

    pButton4 = gtk_button_new_with_label(g_locale_to_utf8("Nouvelle machine", -1, NULL, NULL, NULL));
    gtk_widget_set_size_request(pButton4, 150, 10);
	gtk_box_pack_start(GTK_BOX(pHBox2), pButton4, TRUE, FALSE, 0);
	g_signal_connect(G_OBJECT(pButton4), "clicked", G_CALLBACK(in_nouvelle_machine_call), pWindow);

    ///
	///
	
    pButton7 = gtk_button_new_with_label(g_locale_to_utf8("Quitter", -1, NULL, NULL, NULL));
    gtk_widget_set_size_request(pButton7, 150, 10);
	gtk_box_pack_start(GTK_BOX(pHBox3), pButton7, TRUE, FALSE, 0);
	g_signal_connect(G_OBJECT(pButton7), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	
    gtk_widget_show_all(pWindow);
    
}

