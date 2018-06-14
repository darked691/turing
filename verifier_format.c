#include "definition.h"
#include "gestionnaire_erreur.h"

//verifie si le format pour le tableau état et alphabet dans le fichier est respécté
int verifier_format_etat_alphabet(char* path)
{
	FILE* fichier=NULL;
    fichier = fopen(path, "r");
	int i=0;
	char c = '\0'; 
	int parenthese=0;
	int nombre=0;
	c=fgetc(fichier);
	if(c=='[') {parenthese++;}
        do
         { 
			 
            c= fgetc(fichier); 
            
            
            
            //si on arrive à la fin du tableau on sort de la boucle 
            
            
            nombre++;
            
            nombre=nombre%2;

            if(nombre==1 && c==']') {err_format("1 le caractére n'est pas un nombre");  exit(0); }
            
            if(c==']') {parenthese++; break;}
            
            if(c== '\n')break;
            
            if(c=='[') {err_format("1 le nombre de parenthése est incorrecte");  exit(0);  }
            
            //si l'état n'est pas un nombre on retourne 0
            if(nombre==1 ){if(c<47 || c>57) {err_format("1 le caractére n'est pas un nombre");  exit(0); }}
            if(nombre==0 ) {if(c!=','){err_format("1 le caractére n'est pas une virgule");  exit(0);}}
				
         }while (c != ']'); 
         
         
			
			if(parenthese!=2) {err_format("1 le nombre de parenthése est incorrecte");  exit(0);  }
			
			//while( c!='\n'){c= fgetc(fichier);}
			c=fgetc(fichier);
			if(c!='\n'){err_format("1 le caractére hors tableau");  exit(0);}
			c=fgetc(fichier);
			
			
			
			
 
			parenthese=0;
			
			nombre=0;
			
			if(c=='[') {parenthese++;  }
			
		 do
         { 
				
			
		
            c= fgetc(fichier); 

            nombre++;
            
           nombre=nombre%2; 

            if(nombre==1 && c==']') {err_format("1 le caractére n'est pas un symbole de l'alphabet");  exit(0); }
            
            if(c==']'){ parenthese++; break;}
            
            if(c== '\n')break;
            if(c=='[') {err_format("1 le nombre de parenthése est incorrecte");  exit(0);  }
            
 
            
            if(nombre==0 ) {if(c!=','){err_format("1 le caractére n'est pas une virgule");  exit(0);}}

		

				
         }while (c != ']');
         c=fgetc(fichier);
         
         if(c!='\n'){err_format("1 le caractére hors tableau");  exit(0);}
         
         if(parenthese!=2) {err_format("1 le nombre de parenthése est incorrecte");  exit(0);  }
         
         fclose(fichier);
         return 1;
	
}	
//verifie sir le format transition est respécté
 int verifier_format_transition_ruban(char* path){
	FILE* fichier = NULL;
    fichier = fopen(path, "r");
	int i=0;
	char c = '\0'; 
	int parenthese=0;
	int j=0;
	int nombre_bars=0;
	int nombre_bars_vertical=0;
	int position_caractere=2;
	char message[8];

	if(NR>3)
	{

	 exit(0);
	} 
    if (fichier != NULL)
    {
		//on saute des lignes pour accéder au transition
		while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);
		while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);
		while(c!='\n' ){ c= fgetc(fichier);}

		c= fgetc(fichier); 

		
		if(c!='/'){ err_format("4 il manque un '/'"); exit(0); }

		 
		if(c=='/'){ nombre_bars_vertical++;}
		
		c= fgetc(fichier);
		if(c!='|'){ err_format("4 il manque un '|'");exit(0);}
		int nombre_ligne=4;
		
        while(c!=EOF && NR==1)
          { 

			c= fgetc(fichier);
			if(c==EOF) break;
			if (c=='\n')nombre_ligne++;

			if(c!=' ' || c!='\n'){position_caractere++; }
			//%14 car une ligne comporte 14 caractere
			
			if((position_caractere%14==2 || position_caractere%14==4 || position_caractere%14==6 || position_caractere%14 == 8 || position_caractere%14==10 || position_caractere%14==12) && c!='|'){ sprintf(message,"%d",nombre_ligne); err_format(strcat(message,"  le  caractere '|' ou '/' n'est pas défini")); exit(0);}
			
			if(((position_caractere%14>2 && position_caractere%14<4) || (position_caractere%14 > 8 && position_caractere%14<10) || (position_caractere%14>10 && position_caractere%14<12)) &&  (c=='|' || c=='/') ) {sprintf(message,"%d",nombre_ligne); err_format(strcat(message," un symbole de l'alphabet a ete déplacé ou supprimer")); exit(0);}

			if(((position_caractere%14==5) || (position_caractere%14==7)) && (c=='/' || c=='|')) { sprintf(message,"%d",nombre_ligne); err_format(strcat(message," un numero d'état a ete déplacé ou supprimer")); exit(0);}					
							
			
			if((position_caractere%14==1 || position_caractere%14==13) && c=='/') nombre_bars_vertical++;
					  
			if(c==EOF && nombre_bars_vertical!=2*NT) { sprintf(message,"%d",nombre_ligne); err_format(strcat(message," le nombre de  '/' est incorrecte")); exit(0);}
			
			if(c==' ')
			{
						sprintf(message,"%d",nombre_ligne);
						 err_format(strcat(message," il y a un espace"));
						 exit(0);
			}	
         }
	 
         nombre_ligne=4;
          // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
         while(c!=EOF && NR==2)
          { 
			
			c= fgetc(fichier);
			if(c==EOF) break;
			if (c=='\n')nombre_ligne++;
			if(c!=' ' || c!='\n'){position_caractere++;}
			
			
			
			if(((position_caractere%17>2 && position_caractere%17<5) || (position_caractere%17 > 9 && position_caractere%17<12) || (position_caractere%17>12 && position_caractere%17<15)) &&  (c=='|' || c=='/') ) {sprintf(message,"%d",nombre_ligne); err_format(strcat(message," un symbole de l'alphabet a ete déplacé ou supprimer")); exit(0);}
			
			if(((position_caractere%17==6) || (position_caractere%17==8)) && (c=='/' || c=='|')) { sprintf(message,"%d",nombre_ligne); err_format(strcat(message," un numero d'état a ete déplacé ou supprimer")); exit(0);}
			
			if((position_caractere%17==2 || position_caractere%17==5 || position_caractere%17==7 || position_caractere%17 == 9 || position_caractere%17==12 || position_caractere%17==15) && c!='|'){ sprintf(message,"%d",nombre_ligne); err_format(strcat(message,"  le  caractere '|' ou '/' n'est pas défini")); exit(0);}
			
			
			
			if((position_caractere%17==1 || position_caractere%17==16) && c=='/') nombre_bars_vertical++;
					  
			if(c==EOF && nombre_bars_vertical!=2*NT) { sprintf(message,"%d",nombre_ligne); err_format(strcat(message," le nombre de  '/' est incorrecte")); exit(0);}
			
			if(c==' ') 
			{
						sprintf(message,"%d",nombre_ligne);
						 err_format(strcat(message," il y a un espace"));
						 exit(0);
			}		
         }
          nombre_ligne=4;
         
         nombre_bars=0;
         
         int check=0;
         
         
          while(c!=EOF && NR==3)
          { 
			
			c= fgetc(fichier);
			if(c==EOF) break;

	
			
			 if (c=='\n')nombre_ligne++;
			
			if(c!=' ' || c!='\n'){position_caractere++; }
			
			//%20 car une ligne comporte 20 caractere
			
			if(((position_caractere%20>2 && position_caractere%20<6) || (position_caractere%20>10 && position_caractere%20 < 14) || (position_caractere%20>14 && position_caractere%20<18)) && (c=='/' || c=='|')) { sprintf(message,"%d",nombre_ligne); err_format(strcat(message," un symbole de l'alphabet a ete déplacé ou supprimer")); exit(0);}
			
			if(((position_caractere%20==7) || (position_caractere%20==9)) && (c=='/' || c=='|')) { sprintf(message,"%d",nombre_ligne); err_format(strcat(message," un numero d'état a ete déplacé ou supprimer")); exit(0);}
			
			 if((position_caractere%20==2 || position_caractere%20==6 || position_caractere%20==8 || position_caractere%20 == 10 || position_caractere%20==14 || position_caractere%20==18) && c!='|'){ sprintf(message,"%d",nombre_ligne); err_format(strcat(message," le  caractere '|' ou '/' n'est pas défini")); exit(0);}
			
			 
			
			 if((position_caractere%20==1 || position_caractere%20==19) && c=='/') nombre_bars_vertical++;
			
			//car une transition comporte 2 '/'
			 if(c==EOF && nombre_bars_vertical!=2*NT){ sprintf(message,"%d",nombre_ligne); err_format(strcat(message," le nombre de  '/' est incorrecte")); exit(0);}
			
			
			
					if(c==' ')
					{
						sprintf(message,"%d",nombre_ligne);
						 err_format(strcat(message," il y a un espace"));
						 exit(0);
				    }	
         }
         
}

	 
fclose(fichier);

return 1;
}  
//verifie si les transitions n'ont pas été effacés
int verifier_transition_non_vide(char* path)
{
		
	FILE* fic = NULL;
	
    fic = fopen(path, "r");
    
    char symbole_actuel[3];
    
	int i=0;
	
	char c = '\0';

    if (fic != NULL)
    {
		
			do
			{ 			
			 			
            c= fgetc(fic); 

        }while (c != '\n'); 
			do
			{ 
				c= fgetc(fic); 
				
        }while (c != '\n'); 
            do
			{ 
			 
			
            c= fgetc(fic);

        }while (c != '\n'); 
        
	c= fgetc(fic);
	
	if(c!='/' ) {exit(0);}
	
	c= fgetc(fic);
	
	if(c!='|' ) {exit(0);}
	
	c= fgetc(fic);
	
	if(c=='\n' || c==' '){exit(0);}
	

}
}
