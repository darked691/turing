#include <stdio.h>
#include <stdlib.h>
#include "definition.h"
#include "charger_fichier.h"
#include "verifier_format.h"
#include "ecriture_log.h"
#include "save_fichier.h"
#include "gestionnaire_erreur.h"
#include "simulateur.h"
#include "interface.h"
#include "accueil.c"

int main(int argc, char **argv)
{
	creation_log_latex();
	/* Initialisation de GTK+. Sera fait plus tôt dans le programme final ! */
	gtk_init(&argc, &argv);

	afficher_accueil();
	
	gtk_main();
	fermeture_log();
	return 0;

}
