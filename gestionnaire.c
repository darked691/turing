#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

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
	char entre[60];
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
	char entre[60];
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
	char symbole_actuel[3];
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
	int i=0;
	char c = '\0';
	int k=0;
	int nb_ligne=1; 
	char entre[60];
    if (fichier != NULL)
    {
		
        do
         { 
			 
            c= fgetc(fichier); // On lit le caractère

    }while (c != '/'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
	
	c= fgetc(fichier);
	
	c= fgetc(fichier);

	while(c!=EOF)
	{
		c=fgetc(fichier);
		if(c=='/')
		nb_ligne++;
	}
	NT=nb_ligne/2;
    fclose(fichier);
	}
}
void init_NR(T_machine T){
	
	char symbole_actuel[3];
	
	FILE* fic = NULL;
	
    fic = fopen("fichier", "r");
    
	int i=0;
	
	char c = '\0'; //log1.1 : char c = "" changé en char c = ' ' car le symbole " est utilisé pour les chaines de caractères.
	char entre[60];
    if (fic != NULL)
    {
		
			do
			{ 			
			 			
            c= fgetc(fic); // On lit le caractère

        }while (c != '\n'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
			do
			{ 
				c= fgetc(fic); // On lit le caractère
				
        }while (c != '\n'); 
            do
			{ 
			 
			
            c= fgetc(fic); // On lit le caractère

        }while (c != '\n'); 
	c= fgetc(fic);
	c= fgetc(fic);
	c= fgetc(fic);//printf("%c touy\n",c);
	if(c=='\n' || c==' '){printf("erreur format symbole vide");exit(0);}

	int k=0;

	while(c!='|' || c!=EOF)
	{
		if(c==' '){printf("erreur format symbole vide");exit(0);}
		symbole_actuel[k]=c;
		c=fgetc(fic);
		k++;
		if(c=='|' ) break;
		
	}	
	if(k>3) printf("erreur format NR");
	NR=k;

        fclose(fic);
	}
}
int verifier_format_etat_alphabet()
{
	FILE* fichier=NULL;
    fichier = fopen("fichier", "r");
	int i=0;
	char c = '\0'; //log1.1 : char c = "" changé en char c = ' ' car le symbole " est utilisé pour les chaines de caractères.
	int parenthese=0;
	int j=0;

        do
         { 
			 
            c= fgetc(fichier); // On lit le caractère
            
            if(c=='[') {parenthese++; c= fgetc(fichier); }
            if(c==']') {parenthese++; break;}
            
            j++;
            
            j=j%2;
            
            if(j==1 ){if(c<47 || c>57) {return 0; break;}}
            if(j==0 ) {if(c!=','){return 0; break;}}
				
         }while (c != ']'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
			
			if(parenthese!=2) {return 0; }
			
			while( c!='\n'){c= fgetc(fichier);}
			
			c=fgetc(fichier);
			
			parenthese=0;
			
			j=0;
			
		 do
         { 
			 
			
            c= fgetc(fichier); // On lit le caractère
           
            if(c=='[') {parenthese++; c= fgetc(fichier); }
            
            if(c==']') {parenthese++; break;}
            
            j++;
            
           j=j%2;

            if(j==0 ) {if(c!=','){ return 0;}}
				
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
	int count=2;
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
			
			if(c!=' ' || c!='\n'){count++; }
			
			if((count%14==2 || count%14==4 || count%14==6 || count%14 == 8 || count%14==10 || count%14==12) && c!='|')
			{ printf("erreur format |"); }
			
			if((count%14==1 || count%14==13) && c=='/') nombre_bars_vertical++;
					  
			if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
			
			if(c==' ') printf("erreur format espace");
			
			//if( c==EOF || c==' ' ||c== '\n') {printf("erreur format symbole vide");exit(0);}
         }
	 
         int j2=0;
         j=0;
         
          // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
         while(c!=EOF && NR==2)
          { 

			c= fgetc(fichier);
			
			if(c!=' ' || c!='\n'){count++; printf("%c ----->",c); printf("%d \n",count);}
			
			if((count%17==2 || count%17==5 || count%17==7 || count%17 == 9 || count%17==12 || count%17==15) && c!='|'){ printf("erreur format"); }
			
			if((count%17==1 || count%17==16) && c=='/') nombre_bars_vertical++;
					  
			if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
			
			if(c==' ') printf("erreur format espace");
					
         }
         int j3=0;
         
         nombre_bars=0;
         
         int check=0;
         
          while(c!=EOF && NR==3)
          { 
			
			c= fgetc(fichier);
			
			printf("j3 %d \n",j3);
			//if(c==' ' && count==3 ) {printf("erreur format symbole vide");exit(0);}
			
			 if (c=='\n')j3++;
			
			if(c!=' ' || c!='\n'){count++; printf("%c ----->",c); printf("%d \n",count);}
			
			else if((count%20==2 || count%20==6 || count%20==8 || count%20 == 10 || count%20==14 || count%20==18) && c!='|'){ printf("erreur format"); }
			
			else if((count%20==1 || count%20==19) && c=='/') nombre_bars_vertical++;
			
			else if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
			
			
			
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
    int j=0;
    int i=0;
    int k=0;

    if(fichier!=NULL)
    {
		while(c!='\n') c= fgetc(fichier);
	
		c= fgetc(fichier);
    
		c= fgetc(fichier);

		T.alpabet=malloc(sizeof(char)*NC);
		j=0;
         do
         { 
			 
			if(j==0)
			{
			
			k=i/2;
			
			T.alpabet[k]=c;			
       
			}	
			j++;
			
			j=j%2;
			
            i++;
            
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

	int res=1;
	
	int t=0;
	int alloc=1;
		while(t!=3) {t++; alloc=alloc*NC;}
		printf("alloc early %d \n",alloc);
	alloc=alloc*alloc;
	printf("alloc early 1 %d \n",alloc);
	
	T.matrice_transition=malloc(NE+2*sizeof(Transition));
	
	int i=0;
	
	 for(i=0;i<NE;i++)
	 {
		T.matrice_transition[i]=malloc(1000000*sizeof(Transition));
		
		for(t=0;t<alloc;t++)
		T.matrice_transition[i][t]=-1;
	 }	
	
	int j=0;
	int num=0;
	i=0;
	int k=0;
	t=0;
	
	if(NR==1)
	{
	for(i=0;i<NE;i++){
		
		for(j=0;j<NT;j++){
			if(T.table_transition[j].etat_actuel==i )
			{
				printf("num %d\n",num);
				printf("tt%d\n",T.table_transition[j].etat_actuel);
				printf("tt%d\n",T.table_transition[j].etat_suivant);

					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[j].symbole_actuel[0] )
						{
							printf("alphabet[k] %c \n",T.alpabet[k]);
							num=k;
							T.matrice_transition[i][num]=j;
							printf("mt_f %d\n",T.matrice_transition[i][num]);
						}
					}
				printf("num %d\n",num);
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
		for(j=0;j<NT;j++)
		{
			if(T.table_transition[j].etat_actuel==i)
			{
				printf("num %d\n",num);
				printf("tt%d\n",T.table_transition[j].etat_actuel);
				printf("tt%d\n",T.table_transition[j].etat_suivant);
				
					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[j].symbole_actuel[0])
						{

							num=k;
						}
					}
					
					t=0;
					
					printf("num aa %d\n",num);
					
					res=1;
					
					for(k=0;k<NC;k++){
					
						if(T.alpabet[k]==T.table_transition[j].symbole_actuel[1])
						{
							printf("k %d \n",k);
							printf("res avant while%d\n",res);
							while(t!=NC) {t++; res=res*k;}
							printf("alphabet[k] %c \n",T.alpabet[k]);
							printf("res apres while%d\n",res);
							num=num+res;
							T.matrice_transition[i][num]=j;
							printf("mt_f %d\n",T.matrice_transition[i][num]);
						}
				}
				printf("num a%d\n",num);
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
		
		for(j=0;j<NT;j++)
		{
			if(T.table_transition[j].etat_actuel==i)
			{
				
				printf("T.table_transition.symbole_actuel %c  \n",T.table_transition[2].symbole_actuel[0]);
				printf("num %d\n",num);
					
					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[j].symbole_actuel[0])
						{
							printf("%c",T.alpabet[k]);
							num=k;
						
						}
					}
						
					t=0;
					
					res=1;
					
					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[j].symbole_actuel[1])
						{

							while(t!=NC) {t++; res=res*k;}
							
							printf("%c",T.alpabet[k]);
							
							
							num=num+res;
						}
					}	
					for(k=0;k<NC;k++)
					{
					
						if(T.alpabet[k]==T.table_transition[j].symbole_actuel[2])
						{

							
							res=res*res;
							
							printf("%c \n",T.alpabet[k]);
							
							num=num+res;
							
							printf(" mt_f %d\n",T.matrice_transition[i][num]);
							
							T.matrice_transition[i][num]=j;
						}
					}
				printf("num %d\n",num);
				printf("i %d\n",i);
				printf(" mt_f %d\n",T.matrice_transition[i][num]);
				printf("---------------------\n");
		}	
	}
}		
}
	return T;
}
int partitionner(int *tableau, int p, int r) {
    int pivot = tableau[p], i = p-1, j = r+1;
    int temp;
    while (1) {
        do
            j--;
        while (tableau[j] > pivot);
        do
            i++;
        while (tableau[i] < pivot);
        if (i < j) {
            temp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = temp;
        }
        else
            return j;
    }
}
void quickSort(int *tableau, int p, int r) {
    int q;
    if (p < r) {
        q = partitionner(tableau, p, r);
        quickSort(tableau, p, q);
        quickSort(tableau, q+1, r);
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
			 //printf("etat_suivant %d\n",T.table_transition[ite].etat_suivant);
			  printf("ite %d\n",ite);

			  for(i=0;i<NT+1;i++)
			 {
			 if(T.table_transition[ite].etat_suivant==etat[i])
			 {
				 //printf("ok");
				 i=NT+1;
			 }
			 else if(etat[i]==-1)
			 {
				 etat[i]=T.table_transition[ite].etat_suivant;
				 printf("i %d",i);
				 i=NT+1;
				 
				  printf(" etat %d\n",etat[ite]);
				  //printf("etat_suivant %d\n",I.transition[i].etat_suivant);
				   
			 }	  
			 
			 }
			
		}
	quickSort(etat,0,NT+1);
	FILE* fichier = NULL;
    fichier = fopen("test", "w");
    char c='\0';
    int j=0;
    while(etat[j]==-1) ++j;
    //printf(" j %d",j);
    fputs("[",fichier);
    while(j<NT+1)
    {
    fprintf(fichier,"%d",etat[j]);
    if(j<NT) 
    fputs(",",fichier);
    j++;
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


init_NR(T);
init_NC_();
 init_NT(T);
init_NE();
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
//~ while(a!=200) 
//~ {
//~ ecrire_log(T,fichier[0],fichier[1],fichier[2],position_texte_et_nombre_page);
//~ a++;
//~ }
//~ ecrire_log(T,fichier[0],fichier[1],fichier[2],position_texte);
//~ ecrire_log(T,fichier[0],fichier[1],fichier[2],position_texte);
//~ fermeture_log(fichier[0],fichier[1],fichier[2]);
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
