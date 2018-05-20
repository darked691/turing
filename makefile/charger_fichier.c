#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include "definition.h"

void init_NC_(char* path)
{
	NC=0;
	FILE* fichier = NULL;
    fichier = fopen(path, "r");
	int i=0;
	char c = '\0'; 
    if (fichier != NULL)
    {
        do
         { 			 			
            c= fgetc(fichier);
            
            if(c==',')
            {
				NC++;		
            }
            // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
        }while (c != ']'); 
			NC++;
        fclose(fichier);
	}		
}

void init_NE(char* path)
{	
	FILE* fichier = NULL;
    fichier = fopen(path, "r");
	int i=0;
	char c = '\0'; 
	NE=0;
    if (fichier != NULL)
    {
		while(c != '[') c=fgetc(fichier);
		
		c=fgetc(fichier);
		
		while(c!=']')
		{
			
			if(i==0) NE++;
			
			c=fgetc(fichier);
		
			i++;
		 
			i=i%2;		
		}
        fclose(fichier);
	}		
}	

void init_NT(char* path)
{

	FILE* fichier = NULL;
    fichier = fopen(path, "r");
	int i=0;
	char c = '\0';
	int nb_ligne=0; 
    if (fichier != NULL)
    {
		
        do
         { 
			 
            c= fgetc(fichier); 

    }while (c != '/'); 
	
	c= fgetc(fichier);
	
	c= fgetc(fichier);

	int verifie_ligne_vide=0;

	while(c!=EOF)
	{
		c=fgetc(fichier);
		if(c=='\n')
		nb_ligne++;
	}
	NT=nb_ligne;
    fclose(fichier);
	}
}

void init_NR(char* path)
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
	

	
	c= fgetc(fic);
	
	
	c= fgetc(fic);


	int k=0;
	
	while(c!='|' || c!=EOF)
	{
		//if(c==' '){printf("erreur format symbole vide ");exit(0);}
		symbole_actuel[k]=c;
		c=fgetc(fic);
		k++;
		if(c=='|' ) break;

			 
	}	
	
	NR=k;

        fclose(fic); 
	}
}

T_machine fill_alphabet(T_machine T,char* path)
{
	FILE* fichier = NULL;
    fichier = fopen(path, "r");
    char c='\0';
    int position_virgule_fichier=0;
    int position_fichier=0;
    int position_tableau_alphabet=0;

    if(fichier!=NULL)
    {
		while(c!='\n') c= fgetc(fichier);
	
		c= fgetc(fichier);
    
		c= fgetc(fichier);

		T.alphabet=malloc(sizeof(char)*NC);
		position_virgule_fichier=0;
         do
         { 
			 
			if(position_virgule_fichier==0)
			{
			
			position_tableau_alphabet=position_fichier/2;
			
			T.alphabet[position_tableau_alphabet]=c;			
       
			}	
			position_virgule_fichier++;
			
			position_virgule_fichier=position_virgule_fichier%2;
			
            position_fichier++;
            
            c= fgetc(fichier);
            
        }while (c != ']');
     }    
  fclose(fichier);

return T;      
}    

T_machine fill_transition(T_machine T,char* path)
{
	FILE* fichier = NULL;
    fichier = fopen(path, "r");
    char c='\0';
    int j=0;
    int i=0;

    if(fichier!=NULL)
    {
	while(c!='\n') c= fgetc(fichier); c= fgetc(fichier);
	while(c!='\n') c= fgetc(fichier); c= fgetc(fichier);
	while(c!='\n') c= fgetc(fichier); c= fgetc(fichier); c= fgetc(fichier);
	
	c= fgetc(fichier);
	
	T.table_transition=malloc(sizeof(Transition)*NT+1);

		while(c!=EOF)
		{
			T.table_transition[j].direction=malloc(sizeof(char)*NR);

			T.table_transition[j].symbole_suivant=malloc(sizeof(char)*NR);
		
			T.table_transition[j].symbole_actuel=malloc(sizeof(char)*NR);
		
			i=0;
		
		while(i!=NC-1 && c!='|')
		{
		
			T.table_transition[j].symbole_actuel[i]=c;
		
			printf(" symbole_actuel %c",T.table_transition[j].symbole_actuel[i]);
			printf(" i %d",i);
			printf(" j %d \n",j);
			
			i++;

			c=fgetc(fichier);
			
		}
	 
	c=fgetc(fichier);
		
	i=0;
		
	    while( c!='|')
	    {
		
			T.table_transition[j].etat_actuel= c - '0';
			
			printf(" etat_actuel %d",T.table_transition[j].etat_actuel);
			printf(" i %d",i);
			printf(" j %d \n",j);
			
			i++;
     
			c=fgetc(fichier);
		
		}
		
	c=fgetc(fichier);
		
	i=0;
	
		while( c!='|')
		{
			T.table_transition[j].etat_suivant= c - '0';
		
			printf(" etat_suivant %d",T.table_transition[j].etat_suivant);
			printf(" i %d",i);
			printf(" j %d \n",j);
		
			i++;

			c=fgetc(fichier);	
		}
	
	c=fgetc(fichier);
	
	i=0;
	
	    while(i!=NC-1 && c!='|')
	    {
			T.table_transition[j].symbole_suivant[i]=c;
		
			printf(" symbole_suivant %c ",T.table_transition[j].symbole_suivant[i]);
			printf("%d i ",i);
			printf("%d j \n",j);
		
			i++;

			c=fgetc(fichier);
		
		}
	c=fgetc(fichier);
	i=0;
	
	while(i!=NC-1 && c!='|')
	{
		T.table_transition[j].direction[i]=c;
	
		printf(" direction %c",T.table_transition[j].direction[i]);
		printf(" i %d",i);
		printf(" j %d \n",j);
    
		i++;

		c=fgetc(fichier);
	}
	c=fgetc(fichier);

	while(c!=10) {c=fgetc(fichier); }
	
	c=fgetc(fichier);
	
	printf("%c end\n",c);

	if(j==NT-1) break;
	c=fgetc(fichier);
	c=fgetc(fichier); 

	 	 j++;
}
}

	fclose(fichier);
	return T;
} 
//fonction qui rempli la matrice de transition
T_machine fill_matrice_t(T_machine T)
{

	int resultat=1;
	
	int puissance=0;
	int alloc=1;
	//calcule de la taille maximal du pointeur matrice de transition
		while(puissance!=NR) {puissance++; alloc=alloc*NC;}

		//~ if(NR==3)
		//~ alloc=alloc+NC*NC+NC;
	   //~ else if(NR==2)
	   //~ alloc=alloc+NC;
		printf("alloca %d\n",alloc);
	
	T.matrice_transition=malloc(NE+2*sizeof(Transition));
	
	int i=0;
	int j=0;
	 for(i=0;i<NE;i++)
	 {
		T.matrice_transition[i]=malloc(alloc*sizeof(Transition));
		
		for(j=0;j<alloc;j++)
		T.matrice_transition[i][j]=-1;
	 }	
	
	int numero_transition=0;
	int numero_indice_matrice=0;
	i=0;
	int k=0;

	//on dissocie les cas ou le nombre de ruban est égale à 1,2,3
	//selon les cas on remplie la matrice de transition différement 
	//pour le cas 1, on cherche pour chaque transition dans la table de transition la place du caractere "symbole actuel[0]" dans le tableau alphabet
	// qui contient tout les symboles de l'alphabet
	if(NR==1)
	{
	for(i=0;i<NE;i++){
		
		for(numero_transition=0;numero_transition<NT;numero_transition++){
			if(T.table_transition[numero_transition].etat_actuel==i )
			{
				printf("symbole_actuel %s \n",T.table_transition[numero_transition].symbole_actuel);


					for(k=0;k<NC;k++)
					{
					
						if(T.alphabet[k]==T.table_transition[numero_transition].symbole_actuel[0] )
						{

							numero_indice_matrice=k;
							T.matrice_transition[i][numero_indice_matrice]=numero_transition;
							printf("numero 1er boucle %d\n",numero_indice_matrice);
							printf("mt_f %d\n",T.matrice_transition[i][numero_indice_matrice]);
						}
					}

				printf("i %d\n",i);

				printf("---------------------\n");
			
		}
		}
	}
}
    //pour le cas 2, on cherche pour chaque transition dans la table de transition la place du caractere(=nombre 1) "symbole actuel[0]" dans le tableau alphabet
	// qui contient tout les symboles de l'alphabet
	// on cherche pour chaque transition dans la table de transition la place du caractere(=nombre 2) "symbole actuel[1]" dans le tableau alphabet
	// qui contient tout les symboles de l'alphabet
	// on calcule nombre1+(nombre2 puissance nombre de ruban) pour obtenir indice de la matrice 
	else if(NR==2)
	{
	int r=0;
	for(i=0;i<NE;i++)
	{
		for(numero_transition=0;numero_transition<NT;numero_transition++)
		{
			if(T.table_transition[numero_transition].etat_actuel==i)
			{
				

				printf("symbole_actuel %s \n",T.table_transition[numero_transition].symbole_actuel);
					for(k=0;k<NC;k++)
					{
					
						if(T.alphabet[k]==T.table_transition[numero_transition].symbole_actuel[0])
						{
							
							numero_indice_matrice=k;
							printf("numero 1er boucle %d\n",numero_indice_matrice);
						}
					}
					
					puissance=0;
					
	
					
					resultat=1;
					
					for(k=0;k<NC;k++){
					
						if(T.alphabet[k]==T.table_transition[numero_transition].symbole_actuel[1])
						{

							resultat=resultat*NC;

							resultat=resultat*k;
							numero_indice_matrice=numero_indice_matrice+resultat;

							T.matrice_transition[i][numero_indice_matrice]=numero_transition;
							printf("mt_f %d\n",T.matrice_transition[i][numero_indice_matrice]);
						}
				}

				printf("i %d\n",i);
				printf("---------------------\n");
		}	
		
	}
}
		
}
    //pour le cas 3, on cherche pour chaque transition dans la table de transition la place du caractere(=nombre 1) "symbole actuel[0]" dans le tableau alphabet
	// qui contient tout les symboles de l'alphabet
	// on cherche pour chaque transition dans la table de transition la place du caractere(=nombre 2) "symbole actuel[1]" dans le tableau alphabet
	// qui contient tout les symboles de l'alphabet
	// on cherche pour chaque transition dans la table de transition la place du caractere(=nombre 3) "symbole actuel[2]" dans le tableau alphabet
	// qui contient tout les symboles de l'alphabet
	// on calcule nombre1+(nombre2 puissance nombre de ruban-1)+(nombre3 puissance nombre de ruban) pour obtenir indice de la matrice 
	else if(NR==3)
	{
		int r=0;
		
	for(i=0;i<NE;i++)
	{
		
		for(numero_transition=0;numero_transition<NT;numero_transition++)
		{
			if(T.table_transition[numero_transition].etat_actuel==i)
			{
				
				printf("T.table_transition.symbole_actuel %c  \n",T.table_transition[2].symbole_actuel[0]);
				
					
					for(k=0;k<NC;k++)
					{
					
						if(T.alphabet[k]==T.table_transition[numero_transition].symbole_actuel[0])
						{
							printf("%c",T.alphabet[k]);
							numero_indice_matrice=k;
							printf("numero 1er boucle %d\n",numero_indice_matrice);
						
						}
					}
						
					puissance=0;
					
					resultat=1;
					
					for(k=0;k<NC;k++)
					{
					
						if(T.alphabet[k]==T.table_transition[numero_transition].symbole_actuel[1])
						{

							resultat=resultat*NC;

							resultat=resultat*k;
							
							printf("%c",T.alphabet[k]);

							numero_indice_matrice=numero_indice_matrice+resultat;
							printf("\n nnumero 2er boucle %d\n",numero_indice_matrice);
						}
					}	
					puissance =0;
					resultat=1;
					
					for(k=0;k<NC;k++)
					{
					
						if(T.alphabet[k]==T.table_transition[numero_transition].symbole_actuel[2])
						{
 
							while(puissance!=NR-1) {puissance++; resultat=resultat*NC;}
							//resultat=resultat*resultat;
							resultat=resultat*k;
							printf("%c \n",T.alphabet[k]);
							
							numero_indice_matrice=numero_indice_matrice+resultat;
							printf("\n numero 3er boucle %d\n",numero_indice_matrice);
							
							printf(" mt_f %d\n",T.matrice_transition[i][numero_indice_matrice]);
							
							T.matrice_transition[i][numero_indice_matrice]=numero_transition;
						}
					}

				printf("i %d\n",i);
				printf(" mt_f %d\n",T.matrice_transition[i][numero_indice_matrice]);
				printf("---------------------\n");
		}	
	}
}		
}
	return T;
}




	
void liberation_de_la_memoire(T_machine T,Info_machine I)
{

//~ free(I.transition);
//~ free(I.transition->symbole_suivant);				
//free(I.transition->symbole_actuel);				
//free(I.transition->direction);
//~ free(T.table_transition);
//~ free(T.table_transition->direction);
//free(T.table_transition->symbole_actuel);
//free(T.table_transition->symbole_suivant);
//free(T.table_transition);
//free(T.alpabet);
}

T_machine charger_fichier(T_machine T,char* path)
{
	init_NC_(path);
	init_NE(path);
	init_NR(path);
	init_NT(path);	
	T=fill_alphabet(T,path);
	T=fill_transition(T,path);
	T=fill_matrice_t(T);
	
return T;	
}
	
