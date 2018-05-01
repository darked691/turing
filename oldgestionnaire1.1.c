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

void init_NC_()
{
	NC=0;
FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
	int i=0;
	char c = '\0'; //log1.1 : char c = "" changé en char c = ' ' car le symbole " est utilisé pour les chaines de caractères.
	char entre[60];
    if (fichier != NULL)
    {
        do
         { 
			 
			
            c= fgetc(fichier); // On lit le caractère
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
	char c = '\0'; //log1.1 : char c = "" changé en char c = ' ' car le symbole " est utilisé pour les chaines de caractères.
	char entre[60];
	NE=0;
    if (fichier != NULL)
    {
		while(c != '[') c=fgetc(fichier);
	// On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
		c=fgetc(fichier);
		while(c!=']') {
			if(i==0) NE++;
		c=fgetc(fichier); i++; i=i%2;
		
		}
        fclose(fichier);
	}
		

}	
void init_NT(T_machine T){
char symbole_actuel[3];
FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
	int i=0;
	char c = '\0'; //log1.1 : char c = "" changé en char c = ' ' car le symbole " est utilisé pour les chaines de caractères.
	char entre[60];
    if (fichier != NULL)
    {
		
        do
         { 
			 
			
            c= fgetc(fichier); // On lit le caractère

        }while (c != '/'); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
	//printf("%c",c);
	c= fgetc(fichier);
	c= fgetc(fichier);
	//printf("%c\n",c);
	int k=0;
	int nb_ligne=0;
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
	c= fgetc(fic);//printf("%c tt\n",c);

	int k=0;

	while(c!='|' || c!=EOF)
	{
		
		symbole_actuel[k]=c;
		c=fgetc(fic);
		k++;
		if(c=='|' || c==EOF || c==' ' ||c== '\n') break;
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
    //~ if (fichier != NULL)
    //~ {
		
        do
         { 
			 
			
            c= fgetc(fichier); // On lit le caractère
            //printf("%d\n",c);
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
			//printf("%c\n",c);
	do
         { 
			 
			
            c= fgetc(fichier); // On lit le caractère
           // printf("%d\n",c);
            if(c=='[') {parenthese++; c= fgetc(fichier); }
            if(c==']') {parenthese++; break;}
            j++;
           j=j%2;
            //if(j==1 ){if(c<47 || c>57) {printf("probléme j"); break;}}
            if(j==0 ) {if(c!=','){ return 0;}}
				
         }while (c != ']');
         fclose(fichier);
         return 1;
	
}	

 int verifier_format_transition_ruban_1(){
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
	int i=0;
	char c = '\0'; //log1.1 : char c = "" changé en char c = ' ' car le symbole " est utilisé pour les chaines de caractères.
	int parenthese=0;
	int j=0;
	int nombre_bars=0;
	int nombre_bars_vertical=0;
	int count=2;
    if (fichier != NULL)
    {
		 while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);//printf("%c t\n",c);
		 while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);//printf("%c t\n",c);
		 while(c!='\n' ){ c= fgetc(fichier);}
		//printf("%c 1\n",c);
		 c= fgetc(fichier); 
		 //printf("%c 2\n",c);
		 if(c!='/'){ printf("erreur format /");return  0;}
		if(c=='/'){ nombre_bars_vertical++;}
		c= fgetc(fichier);
        while(c!=EOF && NR==1)
          { 

					 c= fgetc(fichier);
					 	 if(c!=' ' || c!='\n')
					 {count++; }
					   if((count%14==2 || count%14==4 || count%14==6 || count%14 == 8 || count%14==10 || count%14==12) && c!='|')
					   { printf("erreur format |"); }
					  if((count%14==1 || count%14==13) && c=='/') nombre_bars_vertical++;
					  //printf("%d nombre_bars_vertical\n",nombre_bars_vertical);
					  if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
					  if(c==' ') printf("erreur format espace");
         }
	 
         int j2=0;
         j=0;
         
          // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
                 while(c!=EOF && NR==2)
          { 

					 	 c= fgetc(fichier);
					 	 if(c!=' ' || c!='\n')
					 {count++; printf("%c ----->",c); printf("%d \n",count);}
					  if((count%17==2 || count%17==5 || count%17==7 || count%17 == 9 || count%17==12 || count%17==15) && c!='|')
					  { printf("erreur format"); }
					   if((count%17==1 || count%17==16) && c=='/') nombre_bars_vertical++;
					  //printf("%d nombre_bars_vertical\n",nombre_bars_vertical);
					  if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
					if(c==' ') printf("erreur format espace");
				
					
         }
         int j3=0;
         nombre_bars=0;
         int check=0;
          while(c!=EOF && NR==3)
          { 
			 // printf("---------");				
					 c= fgetc(fichier);
						if(c!=' ' || c!='\n')
					 {count++; printf("%c ----->",c); printf("%d \n",count);}
					 if(c=='|' && count%20==2 )printf("ok \n");
					 else if((count%20==2 || count%20==6 || count%20==8 || count%20 == 10 || count%20==14 || count%20==18) && c!='|')
					 { printf("erreur format"); }
					 else if((count%20==1 || count%20==19) && c=='/') nombre_bars_vertical++;
					  //printf("%d nombre_bars_vertical\n",nombre_bars_vertical);
					 else if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
					if(c==' ')
					{
						 printf("erreur format espace\n");
						 exit(0);
				    }	
					//printf("%c\n",c);
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
    //for(i=0;i<1000;i++) T.alphabet[i]=' ';
    if(fichier!=NULL)
    {
	while(c!='\n') c= fgetc(fichier);
         c= fgetc(fichier);
         c= fgetc(fichier);
         //printf("%c\n",c);
         //while(c!='\n') {c= fgetc(fichier); printf("%c\n",c);}
         T.alpabet=malloc(sizeof(char)*NC);
         int j=0;
                 do
         { 
			 
			
             //~ // On lit le caractère
				if(j==0){
			//printf("%c",c);
			k=i/2;
				T.alpabet[k]=c;
				printf(" alphabet[k] %c i %d NC %d \n",T.alpabet[k],k,NC);
       
			}
			j++;
			j=j%2;
            i++;
            c= fgetc(fichier);
        }while (c != ']');
		 //printf("--> %s \n",T.alpabet);
		 //while(i<10) {printf("%c \n",T.alpabet[i]); i++;}
     }    
  fclose(fichier);
 // free(T.alpabet);
return T;      
}    
T_machine fill_transition(T_machine T)
{
	FILE* fichier = NULL;
    fichier = fopen("fichier", "r");
    char c='\0';
    int j=0;
    int i=0;
    //int nt=NT;
    
    //for(i=0;i<1000;i++) T.alphabet[i]=' ';
    if(fichier!=NULL)
    {
	while(c!='\n') c= fgetc(fichier); c= fgetc(fichier);
	while(c!='\n') c= fgetc(fichier); c= fgetc(fichier);
	while(c!='\n') c= fgetc(fichier); c= fgetc(fichier); c= fgetc(fichier);
	c= fgetc(fichier);
	
	//printf("%c \n",c);
	T.table_transition=malloc(sizeof(Transition)*NT+1);

		//printf("%d \n",j);
	
	

	//~ while(c!='/'){
		//~ if(c=
    //~ }
    while(c!=EOF){
	T.table_transition[j].direction=malloc(sizeof(char)*NR);
	//~ T.table_transition[j].etat_actuel=malloc(sizeof(char*)*NR);
	//~ T.table_transition[j].etat_suivant=malloc(sizeof(char*)*NR);
	T.table_transition[j].symbole_suivant=malloc(sizeof(char)*NR);
	T.table_transition[j].symbole_actuel=malloc(sizeof(char)*NR);
	i=0;
    while(i!=NC-1 && c!='|'){
		
    T.table_transition[j].symbole_actuel[i]=c;
     printf(" tab %c",T.table_transition[j].symbole_actuel[i]);
     printf(" i %d",i);
     printf(" j %d \n",j);
    i++;
     //printf("%c \n",c);
    c=fgetc(fichier);
	}
	 //printf("%c \n",c);
	c=fgetc(fichier);
	i=0;
		
	    while( c!='|'){
		
    T.table_transition[j].etat_actuel= c - '0';
     printf(" tab %d",T.table_transition[j].etat_actuel);
     printf(" i %d",i);
     printf(" j %d \n",j);
    i++;
     //printf("%c \n",c);
    c=fgetc(fichier);
	}
	c=fgetc(fichier);
	i=0;
	
	while( c!='|'){
    T.table_transition[j].etat_suivant= c - '0';
    printf(" tab %d",T.table_transition[j].etat_suivant);
     printf(" i %d",i);
     printf(" j %d \n",j);
    i++;
     //printf("%c \n",c);
    c=fgetc(fichier);
	}
	c=fgetc(fichier);
	i=0;
	    while(i!=NC-1 && c!='|'){
    T.table_transition[j].symbole_suivant[i]=c;
     printf("tab %c ",T.table_transition[j].symbole_suivant[i]);
     printf("%d i ",i);
     printf("%d j \n",j);
    i++;
     //printf("%c \n",c);
    c=fgetc(fichier);
	}
	c=fgetc(fichier);
	i=0;
	while(i!=NC-1 && c!='|'){
    T.table_transition[j].direction[i]=c;
     printf("tab %c",T.table_transition[j].direction[i]);
     printf(" i %d",i);
     printf(" j %d \n",j);
    i++;
     //printf("%c \n",c);
    c=fgetc(fichier);
	}
	c=fgetc(fichier);
	//c=fgetc(fichier);
	while(c!=10) {c=fgetc(fichier); printf("ok");}
	c=fgetc(fichier);
	printf("%d end\n",c);
	 

	 //printf("%d \n",sizeof(Transition));
	if(j==NT-1) break;
	c=fgetc(fichier);
	c=fgetc(fichier); 
	//c=fgetc(fichier); 
	 //c=fgetc(fichier); 
	 	 j++;
}
}

	fclose(fichier);
	return T;
}   
T_machine fill_matrice_t(T_machine T)
{

	//T.matrice_transition=malloc(pow(NC,NR)*sizeof(int));
	
	int t=0;
	int res=1;
	while(t!=3) {t++; res=res*128;}
		printf("res early %d \n",res);
	res=res*res;
	printf("res early 1 %d \n",res);
	T.matrice_transition=malloc(256*sizeof(int));
	
	int i=0;
	for(i=0;i<NE;i++)
	{
		T.matrice_transition[i]=malloc(pow(128,3)*sizeof(int));
		for(t=0;t<res;t++)
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
			if(T.table_transition[j].etat_actuel==i ){
				printf("num %d\n",num);
				printf(" tt%d\n",T.table_transition[j].etat_actuel);
				printf(" tt%d\n",T.table_transition[j].etat_suivant);
				 //num=*((int*)T.table_transition[j].symbole_actuel);
					//num=num%res;
					
					for(k=0;k<NC;k++){
					
					if(T.alpabet[k]==T.table_transition[j].symbole_actuel[0] )
					{
						printf(" alphabet[k] %c \n",T.alpabet[k]);
						num=k;
						T.matrice_transition[i][num]=j;
						printf(" mt_f %d\n",T.matrice_transition[i][num]);
					}
				}
				printf("num %d\n",num);
				printf("i %d\n",i);
				 	 //char c = (char)T.table_transition.etat_suivant;
				 	// printf("c %d\n",c);
			
			//printf(" mt_f %d\n",T.matrice_transition[i][num]);
			printf("---------------------\n");
			
		}
		}
	}
}
	else if(NR==2)
	{
		int r=0;
	for(i=0;i<NE;i++){
		
		for(j=0;j<NT;j++){
			if(T.table_transition[j].etat_actuel==i){
				printf("num %d\n",num);
				printf(" tt%d\n",T.table_transition[j].etat_actuel);
				printf(" tt%d\n",T.table_transition[j].etat_suivant);
				 //num=*((int*)T.table_transition[j].symbole_actuel);
					//num=num%res;
					
					for(k=0;k<NC;k++){
					
					if(T.alpabet[k]==T.table_transition[j].symbole_actuel[0])
					{
						printf(" alphabet[k] %c \n",T.alpabet[k]);
						num=k;
					}
				}
					t=0;
					printf("num aa %d\n",num);
					res=1;
					for(k=0;k<NC;k++){
					
					if(T.alpabet[k]==T.table_transition[j].symbole_actuel[1])
					{
						printf(" k %d \n",k);
						printf("res avant while%d\n",res);
						while(t!=NC) {t++; res=res*k;}
						printf(" alphabet[k] %c \n",T.alpabet[k]);
						printf("res apres while%d\n",res);
						num=num+res;
						T.matrice_transition[i][num]=j;
						printf(" mt_f %d\n",T.matrice_transition[i][num]);
					}
				}
				printf("num a%d\n",num);
				printf("i %d\n",i);
				 	 //char c = (char)T.table_transition.etat_suivant;
				 	// printf("c %d\n",c);
			
			
			printf("---------------------\n");
			
		
		}	
		
	}
}
		
}

	else if(NR==3)
	{
		int r=0;
		
	for(i=0;i<NE;i++){
		
		for(j=0;j<NT;j++){
			if(T.table_transition[j].etat_actuel==i){
				
				printf(" T.table_transition.symbole_actuel %c  \n",T.table_transition[2].symbole_actuel[0]);
				printf("num %d\n",num);
				printf(" tt%d\n",T.table_transition[j].etat_actuel);
				printf(" tt%d\n",T.table_transition[j].etat_suivant);
				 //num=*((int*)T.table_transition[j].symbole_actuel);
					//num=num%res;
					
					for(k=0;k<NC;k++){
					
					if(T.alpabet[k]==T.table_transition[j].symbole_actuel[0])
					{
						printf(" alphabet[k] %c \n",T.alpabet[k]);
						num=k;
						
					}
				}
					t=0;
					printf("num aa %d\n",num);
					res=1;
					for(k=0;k<NC;k++){
					
					if(T.alpabet[k]==T.table_transition[j].symbole_actuel[1])
					{
						printf(" k %d \n",k);
						printf("res avant while%d\n",res);
						while(t!=NC) {t++; res=res*k;}
						printf(" alphabet[k] %c \n",T.alpabet[k]);
						printf("res apres while%d\n",res);
						num=num+res;
					}
				}
					for(k=0;k<NC;k++){
					
					if(T.alpabet[k]==T.table_transition[j].symbole_actuel[2])
					{
						printf(" k %d \n",k);
						printf("res avant while%d\n",res);
						
						res=res*res;
						printf(" alphabet[k] %c \n",T.alpabet[k]);
						printf("res apres while%d\n",res);
						num=num+res;
						printf(" mt_f %d\n",T.matrice_transition[i][num]);
						T.matrice_transition[i][num]=j;
					}
				}
				printf("num a%d\n",num);
				printf("i %d\n",i);
				 	 //char c = (char)T.table_transition.etat_suivant;
				 	// printf("c %d\n",c);
			
			printf(" mt_f %d\n",T.matrice_transition[i][num]);
			printf("---------------------\n");
			
		
		}	
		
	}
}		
}


	return T;
}	
int main(){
int check_etat_alphabet=0;
int check_format=0;

T_machine T;
init_NC_();
 init_NT(T);
init_NR(T);
init_NE();
printf("%dNE \n",NE);
check_etat_alphabet=verifier_format_etat_alphabet();
check_format=verifier_format_transition_ruban_1();
T=fill_alphabet(T);
T=fill_transition(T);
T=fill_matrice_t(T);
int i=0;

//~ printf("%d \n",(int)pow(2,3));
	//~ printf(" mt %d\n",T.matrice_transition[2][3]); 
	//~ int i;
//~ printf(" T.table_transition.symbole_actuel %c \n",T.table_transition[2].symbole_actuel[0]);
					//~ printf(" tt%d\n",T.table_transition[2].etat_actuel);
				//~ printf(" tt%d\n",T.table_transition[2].etat_suivant);


free(T.alpabet);
return 0;
}
