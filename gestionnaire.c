#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

#define TRUE 1

#define FALSE 0
int NC;
int NT;
int NR;
int NE;

typedef struct
{
	int etat_actuel;
	
	int etat_suivant;
	
	char *symbole_actuel;
	
	char *symbole_suivant;
	
	char *direction;
	
} Transition;

typedef struct 
{
  char *alpabet;
  
  Transition *table_transition;
  
  int **matrice_transition;
  
} T_machine;

typedef struct
{
	char* alphabet;
	
	int nb_etats;
	
	Transition* transition;
	
}Info_machine;	
void init_NC_()
{
	NC=0;
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
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
        }while (c != ']'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
			NC++;
        fclose(fichier);
	}		
}
void init_NE()
{	
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
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
void init_NT(T_machine T){

	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
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
		
		//~ if(verifie_ligne_vide==1 && c!='/')
		//~ {
			 //~ printf("erreur format : symbole_vide\n");
			 //~ nb_ligne--;
			 //~ break;
		//~ }
		//~ if(c=='\n') verifie_ligne_vide++;
		//~ else
		//~ verifie_ligne_vide=0;
	}
	NT=nb_ligne;
    fclose(fichier);
	}
}
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
void init_NR(T_machine T){
	
	
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
		while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);
		while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);
		while(c!='\n' ){ c= fgetc(fichier);}

		c= fgetc(fichier); 

		
		if(c!='/'){ printf("erreur format /");exit(0);}
		//if(c==' '){ printf("erreur format manque /");exit(0);}
		 
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
			//if(c==' ' && count==3 ) {printf("erreur format symbole vide");exit(0);}
			
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
T_machine fill_alphabet(T_machine T)
{
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
    char c='\0';
    int position_virgule_fichier=0;
    int position_fichier=0;
    int position_tableau_alphabet=0;

    if(fichier!=NULL)
    {
		while(c!='\n') c= fgetc(fichier);
	
		c= fgetc(fichier);
    
		c= fgetc(fichier);

		T.alpabet=malloc(sizeof(char)*NC);
		position_virgule_fichier=0;
         do
         { 
			 
			if(position_virgule_fichier==0)
			{
			
			position_tableau_alphabet=position_fichier/2;
			
			T.alpabet[position_tableau_alphabet]=c;			
       
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
T_machine fill_transition(T_machine T)
{
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
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
T_machine fill_matrice_t(T_machine T)
{

	int resultat=1;
	
	int puissance=0;
	int alloc=1;
		while(puissance!=NR) {puissance++; alloc=alloc*NC;}
		printf("alloc early %d \n",alloc);
		if(NR==3)
	alloc=alloc+NC*NC+NC;
	   else if(NR==2)
	   alloc=alloc+NC;
	printf("alloc early 1 %d \n",alloc);
	
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

	
	if(NR==1)
	{
	for(i=0;i<NE;i++){
		
		for(numero_transition=0;numero_transition<NT;numero_transition++){
			if(T.table_transition[numero_transition].etat_actuel==i )
			{
				printf("symbole_actuel %s \n",T.table_transition[numero_transition].symbole_actuel);


					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[numero_transition].symbole_actuel[0] )
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
					
						if(T.alpabet[k]==T.table_transition[numero_transition].symbole_actuel[0])
						{
							
							numero_indice_matrice=k;
							printf("numero 1er boucle %d\n",numero_indice_matrice);
						}
					}
					
					puissance=0;
					
	
					
					resultat=1;
					
					for(k=0;k<NC;k++){
					
						if(T.alpabet[k]==T.table_transition[numero_transition].symbole_actuel[1])
						{

							while(puissance!=NR) {puissance++; resultat=resultat*k;}
							
							numero_indice_matrice=numero_indice_matrice+resultat;
							printf("numero 2er boucle %d\n",numero_indice_matrice);
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
					
						if(T.alpabet[k]==T.table_transition[numero_transition].symbole_actuel[0])
						{
							printf("%c",T.alpabet[k]);
							numero_indice_matrice=k;
							printf("numero 1er boucle %d\n",numero_indice_matrice);
						
						}
					}
						
					puissance=0;
					
					resultat=1;
					
					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[numero_transition].symbole_actuel[1])
						{

							while(puissance!=NR-1) {resultat=resultat*k; puissance++; }
							
							printf("%c",T.alpabet[k]);
							
							
							numero_indice_matrice=numero_indice_matrice+resultat;
							printf("\n nnumero 2er boucle %d\n",numero_indice_matrice);
						}
					}	
					puissance =0;
					resultat=1;
					
					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[numero_transition].symbole_actuel[2])
						{
 
							while(puissance!=NR) {puissance++; resultat=resultat*k;}
							//resultat=resultat*resultat;
							
							printf("%c \n",T.alpabet[k]);
							
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




void tri_a_bulle_c(int *t,int n){

    int j =0;int tmp =0;int test =1;

    while(test){

        test = FALSE;

        for(j =0; j < n-1; j++){

            if(t[j] > t[j+1]){

                    tmp = t[j+1];

                    t[j+1] = t[j];t[j] = tmp;

                    test = TRUE;

            }

        }

    }

}
Info_machine allocation(Info_machine I,T_machine T)	
{	int i=0;
	int y=0;
	//~ int ite=0;
	//~ for(ite=0;T.table_transition[0].symbole_actuel[ite]!='\0';ite++) {}
	
	//~ printf("ite %d\n",ite);
	//~ I.transition=malloc(sizeof(Transition)*NT+1);
	//~ T.table_transition[NT+1].symbole_actuel=NULL;
	//~ while(T.table_transition[y].symbole_actuel!=NULL) y++;

	int ite;
	 int etat[NT+1];
	 for(i=0;i<NT+1;i++) etat[i]=-1;
	 etat[0]=T.table_transition[0].etat_actuel;
	 printf("NT %d\n",NT);
	 	 for(ite=0;ite<NT;ite++)
	 	 {
			 printf("etat_suivant %d\n",T.table_transition[ite].etat_suivant);
			  printf("ite %d\n",ite);

			  for(i=0;i<NT+1;i++)
			 {
			 if(T.table_transition[ite].etat_suivant==etat[i])
			 {
				 //printf("ok");
				 i=NT+1;
			 }
			 if(etat[i]==-1)
			 {
				 etat[i]=T.table_transition[ite].etat_suivant;
				 printf("i %d",i);
				 				  printf(" etat %d\n",etat[i]);
				  printf("etat_suivant_dans boucle %d\n",T.table_transition[ite].etat_suivant);
				 i=NT+1;
				 

				   
			 }	  
			 
			 }
			
		}
		for(i=0;i<NT+1;i++)  printf(" etat %d\n",etat[i]);
	tri_a_bulle_c(etat,NT+1);
	for(i=0;i<NT+1;i++)  printf(" etat apres le tri %d\n",etat[i]);
	FILE* fichier = NULL;
    fichier = fopen("test", "w");
    char c='\0';
    int j=0;
    while(etat[j]==-1) ++j;
    //printf(" j %d",j);
    fputs("[",fichier);
    while(j<NT+1)
    {
	if(etat[j]!=-1)
	{
    fprintf(fichier,"%d",etat[j]);

    if(j<NT) 
    fputs(",",fichier);
    j++;
	}
	}
    fputs("]",fichier);
    fputs("\n",fichier);
    j=0;
    fputs("[",fichier);
    while(j<NC)
    {
	fprintf(fichier,"%c",T.alpabet[j]);
	if(j<NC-1) fputs(",",fichier);
    j++;
	}
	fputs("]",fichier);
    fputs("\n",fichier);
    fputs("\n",fichier);
    j=0;
    
    while(j<NT)
    {
	fputs("/",fichier);	
	fputs("|",fichier);	
	fputs(T.table_transition[j].symbole_actuel,fichier);
	fputs("|",fichier);	
	fprintf(fichier,"%d",T.table_transition[j].etat_actuel);
	fputs("|",fichier);	
	fprintf(fichier,"%d",T.table_transition[j].etat_suivant);
	fputs("|",fichier);	
	fputs(T.table_transition[j].symbole_suivant,fichier);
	fputs("|",fichier);	
	fputs(T.table_transition[j].direction,fichier);
	fputs("|",fichier);	
	fputs("/",fichier);	
	fputs("\n",fichier);
    j++;
	}
	 	fclose(fichier);
	 	for(i=0;i<NT+1;i++) 
	 	printf(" %d etat a la fin de la boucle \n", etat[i]);
	return I;
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
FILE** creation_log_latex()
{
	FILE** fichier;
	fichier=malloc(sizeof(FILE)*3);
	fichier[0]=fopen("log.tex","w");
	fputc(92,fichier[0]);
fputs("documentclass{article}",fichier[0]);
fputc(10,fichier[0]);
fputc(92,fichier[0]);
fputs("begin{document}",fichier[0]);
fputc(10,fichier[0]);
fputc(92,fichier[0]);
fputs("subsection{Log}",fichier[0]);
fputc(10,fichier[0]);
fputc(92,fichier[0]);
fputs("begin{verbatim}",fichier[0]);
fputc(10,fichier[0]);
fputs("Transition effectue:",fichier[0]);
//fichier2
fichier[1]=fopen("log.fig","w");
fputs("#FIG 3.2  Produced by xfig version 3.2.7\n",fichier[1]);
fputs("Landscape\n",fichier[1]);
fputs("Center\n",fichier[1]);
fputs("Metric\n",fichier[1]);
fputs("A4\n",fichier[1]);
fputs("100.00\n",fichier[1]);
fputs("Single\n",fichier[1]);
fputs("-2\n",fichier[1]);
fputs("1200 2\n",fichier[1]);
fputs("4 0 0 50 -1 0 12 0.0000 4 135 420 2475 900 ",fichier[1]);
fputs("Transition effectue",fichier[1]);
fputc(92,fichier[1]);
fputs("001\n",fichier[1]);
//fichier3
fichier[2]=fopen("log.ps","w");
fputs("%!PS-Adobe-3.0\n\n",fichier[2]);
fputs("%%Page: 1 1\n",fichier[2]);
fputs("%%BeginPageSetup\n",fichier[2]);
fputs(" /pgsave save def\n",fichier[2]);
fputs("%%IncludeResource: font TimesRoman\n",fichier[2]);
fputs("%%EndPageSetup\n",fichier[2]);
fputs(" /Helvetica findfont 8 scalefont setfont\n",fichier[2]);
fputs("100 800 16 sub moveto\n",fichier[2]);
fputs("(Transition effectue:) show\n",fichier[2]);
return fichier;
}		
void ecrire_log(T_machine T,FILE* fichier1,FILE* fichier2,FILE* fichier3,int *position_texte)
{
fputc(10,fichier1);
fputs("Etat : ",fichier1);
fprintf(fichier1,"%d",T.table_transition[2].etat_actuel);
fputc(10,fichier1);
fputs("4 0 0 50 -1 0 16 0.0000 4 135 420 2475",fichier2);
position_texte[0]=position_texte[0]+290;
fprintf(fichier2," %d ",position_texte[0]);
fputs("etat ",fichier2);
fprintf(fichier2,"%d",T.table_transition[2].etat_actuel);
fputc(92,fichier2);
fputs("001\n",fichier2);

//fichier 2
fputs("100 ",fichier3);
fprintf(fichier3,"%d",position_texte[1]);
fputs(" 16 sub moveto\n",fichier3);
fputs("(Etat 2) show\n",fichier3);
position_texte[1]=position_texte[1]-10;
if(position_texte[1]==30)
{
fputs("showpage\n",fichier3);	
position_texte[2]=position_texte[2]+1;
fputs("%%Page: ",fichier3);
fprintf(fichier3,"%d ",position_texte[2]);
fprintf(fichier3,"%d\n",position_texte[2]);
fputs("%%BeginPageSetup\n",fichier3);
fputs(" /pgsave save def\n",fichier3);
fputs("%%IncludeResource: font TimesRoman\n",fichier3);
fputs("%%EndPageSetup\n",fichier3);
fputs(" /Helvetica findfont 8 scalefont setfont\n",fichier3);
fputs("100 800 16 sub moveto\n",fichier3);
fputs("(Transition effectue:) show\n",fichier3);
position_texte[1]=790;
}	
}
void fermeture_log(FILE* fichier1,FILE* fichier2,FILE* fichier3)
{
fputs("showpage\n",fichier3);
fputc(92,fichier1);
fputs("end{verbatim}",fichier1);
fputc(10,fichier1);
fputc(92,fichier1);
fputs("end{document}",fichier1);
fclose(fichier1);
fclose(fichier2);
fclose(fichier3);
}
int main(){
int check_etat_alphabet=0;
int check_format=0;

T_machine T;
Info_machine I;

if(verifier_transition_non_vide()==1)
{
init_NR(T);

init_NC_();
 init_NT(T);
init_NE();
}
//printf("%dNE \n",NE);
check_etat_alphabet=verifier_format_etat_alphabet();
check_format=verifier_format_transition_ruban();
T=fill_alphabet(T);
 T=fill_transition(T);
 I=allocation(I,T);
 T=fill_matrice_t(T);
 int a=0;
 int position_texte_et_nombre_page[2];
 position_texte_et_nombre_page[0]=900;
 position_texte_et_nombre_page[1]=790;
 position_texte_et_nombre_page[2]=1;
 FILE** fichier;
 fichier=creation_log_latex();
while(a!=200) 
{
ecrire_log(T,fichier[0],fichier[1],fichier[2],position_texte_et_nombre_page);
a++;
}

fermeture_log(fichier[0],fichier[1],fichier[2]);
 //free(I.transition);
 //free(I.transition->symbole_suivant);				
//~ free(I.transition->symbole_actuel);				
//~ free(I.transition->direction);
//~ free(T.table_transition);
//~ free(T.table_transition->direction);
//~ free(T.table_transition->symbole_actuel);
//~ free(T.table_transition->symbole_suivant);
 //free(T.table_transition);
 //free(T.alpabet);
 //~ printf("check_etat_alphabet %d\n",check_etat_alphabet);
 //~ printf("check_format %d\n",check_format);
//~ T=fill_matrice_t(T);
int i=0;
//~ for(i=0;i<NT;i++)
//~ {
	//~ printf("symb_actuel %s  etat_actuel %d  etat_suivant %d  symb_suivant %s  direction %s \n",T.table_transition[i].symbole_actuel,T.table_transition[i].etat_actuel,T.table_transition[i].etat_suivant,T.table_transition[i].symbole_suivant,T.table_transition[i].direction);
//~ }

//~ printf("sizeof Transistion %d\n",sizeof(T.table_transition[0]));
//~ printf("sizeof Transistion %d\n",sizeof(T.table_transition[1]));
//~ printf("sizeof Transistion %d\n",sizeof(T.table_transition[2]));
//~ printf("sizeof Transistion %d\n",sizeof(T.table_transition[100]));
//~ printf("sizeof tout les  Transistion %d\n",sizeof(T_machine));
//~ printf(" Transistion %d\n",T.table_transition[100].etat_actuel);
//~ for(i=0;T.table_transition[i].etat_actuel!=0;i++){printf(" Transistion %d\n",T.table_transition[i].symbole_actuel);}
//~ printf(" NT %d\n",i);
//~ return 0;
}
