#include <stdio.h>
#include <stdlib.h>
#include "charger_fichier.h"
#include "verifier_format.h"
#include "ecriture_log.h"
#include "save_fichier.h"
#include "gestionnaire_erreur.h"
#include "simulateur.h"
#include "interface.h"
int main(int argc, char **argv)
{
	/* Initialisation de GTK+. Sera fait plus tôt dans le programme final ! */
	gtk_init(&argc, &argv);
int check_etat_alphabet=0;
int check_format=0;

//scanf("%s",path);
T_machine T;
Info_machine I;



if(verifier_transition_non_vide()==1)
T=charger_fichier(T,"fichier");

//printf("%dNE \n",NE);
//~ check_etat_alphabet=verifier_format_etat_alphabet();
//~ check_format=verifier_format_transition_ruban();
//~ T=fill_alphabet(T);
 //~ T=fill_transition(T);

 //~ I=conversion_donne_fichier(I,T);
 //~ T=fill_matrice_t(T);
 int a=0;
 int position_texte[2];
 position_texte[0]=900;
 position_texte[1]=790;
 position_texte[2]=1;
 printf("%s\n",T.table_transition[2].direction);
 FILE** fichier;
 fichier=creation_log_latex();
while(a!=200) 
{
ecrire_log(T,fichier[0],fichier[1],fichier[2],position_texte,1);
a++;
}

fermeture_log(fichier[0],fichier[1],fichier[2]);

	//~ gtk_init(&argc, &argv);
	
	//~ in_ecran_nouvelle_machine();
	
	//~ gtk_main();
	return 0;

}
