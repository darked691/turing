#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -Wextra -W -pedantic
 
 
#
# Flags pour le compilateur:
#
GLIB_CFLAGS = $$(pkg-config --cflags glib-2.0)
PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_CFLAGS = $$(pkg-config --cflags gtk+-2.0)
 
CFLAGS = $(ERROR_FLAGS) $(GLIB_CFLAGS) $(PANGO_CFLAGS) $(GTK_CFLAGS)
 
 
#
# Flags pour l'editeur de liens:
#
GLIB_LDFLAGS = $$(pkg-config --libs glib-2.0)
PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-2.0)
TFLAGS=$$( pkg-config --libs --cflags gtk+-2.0 ) 
 
LDFLAGS = $(ERROR_FLAGS) $(TFLAGS) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS) $(CFLAGS)


all: gestionnaire

gestionnaire: charger_fichier.o verifier_format.o ecriture_log.o save_fichier.o gestionnaire_erreur.o simulateur.o interface.o main.o 
	gcc $(LDFLAGS) -o  simulateur_exe  charger_fichier.o verifier_format.o ecriture_log.o save_fichier.o  gestionnaire_erreur.o simulateur.o interface.o main.o 


main.o: main.c charger_fichier.h verifier_format.h ecriture_log.h save_fichier.h gestionnaire_erreur.h simulateur.h interface.h
	gcc $(LDFLAGS) -o main.o -c main.c -lm -g

charger_fichier.o: charger_fichier.c
	gcc -o charger_fichier.o -c charger_fichier.c -lm  -g

verifier_format.o: verifier_format.c
	gcc $(LDFLAGS)  -o verifier_format.o -c verifier_format.c -lm  -g

ecriture_log.o: ecriture_log.c
	gcc -o ecriture_log.o -c ecriture_log.c -lm -g

save_fichier.o: save_fichier.c
	gcc -o save_fichier.o -c save_fichier.c -lm  -g
	
gestionnaire_erreur.o: gestionnaire_erreur.c
		gcc $(LDFLAGS)   -o gestionnaire_erreur.o -c gestionnaire_erreur.c -g

simulateur.o: simulateur.c
		gcc $(LDFLAGS)   -o simulateur.o -c simulateur.c -g
		
interface.o:interface.c		
		gcc $(LDFLAGS)   -o interface.o -c interface.c -g
			
clean:
	rm -rf *.o

mrproper: clean
	rm -rf simulateur_exe
				
