#include "definition.h"
#include "gestionnaire_erreur.h"
//verifie si le format pour le tableau état et alphabet dans le fichier est respécté
int verifier_format_etat_alphabet()
{
	FILE* fichier=NULL;
    fichier = fopen("fichier", "r");
	int i=0;
	char c = '\0'; 
	int parenthese=0;
	int nombre=0;

        do
         { 
			 
            c= fgetc(fichier); 
            
            if(c=='[') {parenthese++; c= fgetc(fichier); }
            
            //si on arrive à la fin du tableau on sort de la boucle 
            if(c==']') {parenthese++; break;}
            
            nombre++;
            
            nombre=nombre%2;
            
            //si l'état n'est pas un nombre on retourne 0
            if(nombre==1 ){if(c<47 || c>57) {return 0; }}
            if(nombre==0 ) {if(c!=','){return 0;}}
				
         }while (c != ']'); 
			
			if(parenthese!=2) {return 0; }
			
			while( c!='\n'){c= fgetc(fichier);}
			
			c=fgetc(fichier);
			
			parenthese=0;
			
			nombre=0;
			
		 do
         { 
			 
			
            c= fgetc(fichier); 
           
            if(c=='[') {parenthese++; c= fgetc(fichier); }
            
            if(c==']') {parenthese++; break;}
            
            nombre++;
            
           nombre=nombre%2;

            if(nombre==0 ) {if(c!=','){ return 0;}}
				
         }while (c != ']');
         
         fclose(fichier);
         return 1;
	
}	
//verifie sir le format transition est respécté
 int verifier_format_transition_ruban(){
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
	int i=0;
	char c = '\0'; 
	int parenthese=0;
	int j=0;
	int nombre_bars=0;
	int nombre_bars_vertical=0;
	int position_caractere=2;
	if(NR>3)
	{
	 printf("erreur format Nombre de Ruban elevée\n");
	 exit(0);
	} 
    if (fichier != NULL)
    {
		//on saute des lignes pour accéder au transition
		while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);
		while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);
		while(c!='\n' ){ c= fgetc(fichier);}

		c= fgetc(fichier); 

		
		if(c!='/'){  printf("erreur format /"); 	
	//err_existant("fichier.mdt");
	err_format("89"); 
	 }

		 
		if(c=='/'){ nombre_bars_vertical++;}
		
		c= fgetc(fichier);
		if(c!='|'){ printf("erreur format |");exit(0);}
		
        while(c!=EOF && NR==1)
          { 

			c= fgetc(fichier);
			
			if(c!=' ' || c!='\n'){position_caractere++; }
			
			//%14 car une ligne comporte 14 caractere
			if((position_caractere%14==2 || position_caractere%14==4 || position_caractere%14==6 || position_caractere%14 == 8 || position_caractere%14==10 || position_caractere%14==12) && c!='|')
			{ printf("erreur format le  caractere '|' n'est pas à la bonne place"); }
			
			if((position_caractere%14==1 || position_caractere%14==13) && c=='/') nombre_bars_vertical++;
					  
			if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format le caractere '/' n'est pas à la bonne place");
			
			if(c==' ') printf("erreur format espace");
			
         }
	 
         
          // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
         while(c!=EOF && NR==2)
          { 

			c= fgetc(fichier);
			
			if(c!=' ' || c!='\n'){position_caractere++; printf("%c ----->",c); printf("%d \n",position_caractere);}
			
			if((position_caractere%17==2 || position_caractere%17==5 || position_caractere%17==7 || position_caractere%17 == 9 || position_caractere%17==12 || position_caractere%17==15) && c!='|'){ printf("erreur format le caractere '|' n'est pas à la bonne place "); }
			
			if((position_caractere%17==1 || position_caractere%17==16) && c=='/') nombre_bars_vertical++;
					  
			if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format le nombre de '|' et/ou '/' n est pas correcte");
			
			if(c==' ') printf("erreur format espace");
					
         }
         int nombre_ligne=0;
         
         nombre_bars=0;
         
         int check=0;
         
          while(c!=EOF && NR==3)
          { 
			
			c= fgetc(fichier);
			
			printf("nombre_ligne %d \n",nombre_ligne);
	
			
			 if (c=='\n')nombre_ligne++;
			
			if(c!=' ' || c!='\n'){position_caractere++; printf("%c ----->",c); printf("%d \n",position_caractere);}
			
			//%20 car une ligne comporte 20 caractere
			 if((position_caractere%20==2 || position_caractere%20==6 || position_caractere%20==8 || position_caractere%20 == 10 || position_caractere%20==14 || position_caractere%20==18) && c!='|'){ printf("erreur format"); exit(0);}
			
			 if((position_caractere%20==1 || position_caractere%20==19) && c=='/') nombre_bars_vertical++;
			
			//car une transition comporte 2 '/'
			 if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
			
			
			
					if(c==' ')
					{
						 printf("erreur format espace\n");
						 exit(0);
				    }	
         }
         
}

	 
fclose(fichier);

return 1;
}  
//verifie si les transitions n'ont pas été effacés
int verifier_transition_non_vide()
{
		
	FILE* fic = NULL;
	
    fic = fopen("fichier", "r");
    
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
	
	if(c!='/' ) {printf("erreur format symbole vide il manque '\'");return 0;}
	
	c= fgetc(fic);
	
	if(c!='|' ) {printf("erreur format symbole vide il manque '|'");return 0;}
	
	c= fgetc(fic);
	
	if(c=='\n' || c==' '){printf("erreur format symbole vide");return 0;}
	
	 return 1;
}
}
