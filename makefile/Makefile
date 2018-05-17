#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic
 
 
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
TEST=$$( pkg-config --libs --cflags gtk+-2.0 ) 
 
LDFLAGS = $(ERROR_FLAGS) $(TEST) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS) $(CFLAGS)


all: gestionnaire

gestionnaire: charger_fichier.o verifier_format.o ecriture_log.o save_fichier.o gestionnaire_erreur.o main.o 
	gcc $(LDFLAGS) $(pkg-config --libs --cflags gtk+-2.0) -o  gestionnaire  charger_fichier.o verifier_format.o ecriture_log.o save_fichier.o  gestionnaire_erreur.o main.o 


main.o: main.c charger_fichier.h verifier_format.h ecriture_log.h save_fichier.h gestionnaire_erreur.h
	gcc $(LDFLAGS) -o main.o -c main.c -lm 

charger_fichier.o: charger_fichier.c
	gcc -o charger_fichier.o -c charger_fichier.c -lm  

verifier_format.o: verifier_format.c
	gcc $(LDFLAGS) $(pkg-config --libs --cflags gtk+-2.0) -o verifier_format.o -c verifier_format.c -lm  

ecriture_log.o: ecriture_log.c
	gcc -o ecriture_log.o -c ecriture_log.c -lm 

save_fichier.o: save_fichier.c
	gcc -o save_fichier.o -c save_fichier.c -lm  
	
gestionnaire_erreur.o: gestionnaire_erreur.c
		gcc $(LDFLAGS)  $(pkg-config --libs --cflags gtk+-2.0)  -o gestionnaire_erreur.o -c gestionnaire_erreur.c



clean:
	rm -rf *.o

mrproper: clean
	rm -rf gestionnaire
				
