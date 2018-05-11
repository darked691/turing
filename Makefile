all: gestionnaire

gestionnaire: charger_fichier.o verifier_format.o ecriture_log.o save_fichier.o main.o
	gcc -o gestionnaire charger_fichier.o verifier_format.o ecriture_log.o save_fichier.o main.o

charger_fichier.o: charger_fichier.c
	gcc -o charger_fichier.o -c charger_fichier.c -lm  

main.o: main.c charger_fichier.h verifier_format.h ecriture_log.h save_fichier.h 
	gcc -o main.o -c main.c -lm 

verifier_format.o: verifier_format.c
	gcc -o verifier_format.o -c verifier_format.c -lm  

ecriture_log.o: ecriture_log.c
	gcc -o ecriture_log.o -c ecriture_log.c -lm 

save_fichier.o: save_fichier.c
	gcc -o save_fichier.o -c save_fichier.c -lm  

clean:
	rm -rf *.o

mrproper: clean
	rm -rf gestionnaire
				
