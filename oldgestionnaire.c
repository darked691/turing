#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int NC;
int NT;
int NR;

typedef struct 
{
  char *alphabet;
} T_machine;

T_machine init_NC_alphabet(T_machine T)
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

        fclose(fichier);
	}
	T.alphabet=malloc(sizeof(char)*NC);	
	return T;
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
	//printf("%d\n",nb_ligne);
	//~ while(c!='|')
	//~ {
		
		//~ symbole_actuel[k]=c;
		//~ c=fgetc(fichier);
		//~ k++;
	//~ }	
	//printf("%c\n",c);
	//~ printf("%d\n",k);
	//~ printf("%s\n",symbole_actuel);
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
	c= fgetc(fic);printf("%c tt\n",c);

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
            printf("%d\n",c);
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
			printf("%c\n",c);
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
         close(fichier);
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
		 while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);printf("%c t\n",c);
		 while(c!='\n' ){ c= fgetc(fichier);}c= fgetc(fichier);printf("%c t\n",c);
		 while(c!='\n' ){ c= fgetc(fichier);}
		//~ while(c!='/' ){ c= fgetc(fichier); printf("%c  jj\n",c); if(c=='|')return 0;
			//~ if(c==EOF)return 0; if(c=='\n')parenthese++; if(parenthese >3) break;}
		printf("%c 1\n",c);
		 c= fgetc(fichier); 
		 printf("%c 2\n",c);
		 if(c!='/'){ printf("erreur format /");return  0;}
		if(c=='/'){ nombre_bars_vertical++;}
		c= fgetc(fichier);
        while(c!=EOF && NR==1)
          { 
			 //~ //if(c=='|') printf("ok");
			 //~ if(j==0){if(c!='|'){ printf("erreur format j");return 0;}}
			 //~ if(j==0 && c=='|'){nombre_bars++;}
			//~ c= fgetc(fichier);
             //~ // On lit le caractère
            

            //~ j++;
           //~ j=j%2;

			 //~ printf("%c\n",c);
			
			//~ if(c=='/' ) {j=2; nombre_bars_vertical++;}
		//~ else if(c==' ' || c=='\n'){ j=0; while(c==' ') c= fgetc(fichier);
				//~ c= fgetc(fichier); c= fgetc(fichier);}
			//~ else	if(j==2){if(c!='/') return 0;}
					//~ else if((nombre_bars!=NT*6 || nombre_bars_vertical!=NT*2) && c==EOF)
					 //~ printf("erreur format bars ");
					 c= fgetc(fichier);
					 	 if(c!=' ' || c!='\n')
					 {count++; printf("%c ----->",c); printf("%d \n",count);}
					   if((count%14==2 || count%14==4 || count%14==6 || count%14 == 8 || count%14==10 || count%14==12) && c!='|')
					   { printf("erreur format |"); }
					  if((count%14==1 || count%14==13) && c=='/') nombre_bars_vertical++;
					  //printf("%d nombre_bars_vertical\n",nombre_bars_vertical);
					  if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
         }
	 
         int j2=0;
         j=0;
         
          // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
                 while(c!=EOF && NR==2)
          { 
			  //~ if(j==0 && (nombre_bars==2 || nombre_bars==3) ){
				  //~ if(c!='|'){ printf("erreur format j");return 0;}}
			 //~ if(j==0 && c=='|' && (nombre_bars==2 || nombre_bars==3))
			 //~ {nombre_bars++; j++;j=j%2;}
			 //~ if(j2==0 && c=='|' && (nombre_bars==0 || nombre_bars==1 || nombre_bars==3 || nombre_bars==4 || nombre_bars==5))
			 //~ {nombre_bars++; j2++; j2=j2%3;}
			 //~ if(j2==0 && (nombre_bars==0 || nombre_bars==1 || nombre_bars==3 || nombre_bars==4 || nombre_bars==5) ){
				  //~ if(c!='|'){ printf("erreur format j2");return 0;}}
			//~ c= fgetc(fichier);
             //~ // On lit le caractère
            
			
    

			 //~ printf("%c\n",c);
			
			//~ if(c=='/') {j=2; nombre_bars_vertical++;}	
			//~ if((nombre_bars!=NT*6 || nombre_bars_vertical!=NT*2) && c==EOF)
					 //~ printf("erreur format bars");
					 					 c= fgetc(fichier);
					 	 if(c!=' ' || c!='\n')
					 {count++; printf("%c ----->",c); printf("%d \n",count);}
					  if((count%17==2 || count%17==5 || count%17==7 || count%17 == 9 || count%17==12 || count%17==15) && c!='|')
					  { printf("erreur format"); }
					   if((count%17==1 || count%17==16) && c=='/') nombre_bars_vertical++;
					  //printf("%d nombre_bars_vertical\n",nombre_bars_vertical);
					  if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
				
				
					
         }
         int j3=0;
         nombre_bars=0;
         int check=0;
          while(c!=EOF && NR==3)
          { 
			  printf("---------");
			  //~ if(j==0 && (nombre_bars==1 || nombre_bars==3) ){
				  //~ if(c!='|'){ printf("erreur format j");return 0;}}
			//~ if(j==0 && c=='|' && (nombre_bars==1 || nombre_bars==2))
			 //~ {nombre_bars++; check=1;}	  
			 //~ if(  (nombre_bars==2 || nombre_bars==3))
			 //~ { j++;j=j%2; }

			 //~ if(j3==0 && c=='|' && (nombre_bars==0  || nombre_bars==3 || nombre_bars==4 || nombre_bars==5))
			 //~ {nombre_bars++;  }
			 //~ if(nombre_bars==1 || nombre_bars==4 || nombre_bars==5 )
			 //~ {j3++; j3=j3%4;}
			 //~ if(j3==0 && (nombre_bars==1 && c=='|') || (nombre_bars==2 && c=='|') ){
				  //~ if(c!='|'){ printf("erreur format j2");return 0;}}
				  //~ printf("%c\n",c);
			
             //~ // On lit le caractère
            

    

			 
			
			//~ if(c=='/') {j=0; nombre_bars_vertical++;}	
			//~ if((nombre_bars!=NT*6 || nombre_bars_vertical!=NT*2) && c==EOF)
					 //~ printf("erreur format bars \n");
					 //printf("%d\n",nombre_bars_vertical);
					 //~ printf("%d bars \n ",nombre_bars);
					 //~ printf("%d j \n ",j);
					 //~ printf("%d j3 \n ",j3);

					 //~ if(c!='|')
					 //~ printf("%d\n" ,count);
					 //~ if(count%20==2 || count%20==6 || count%20==8 || count%20 == 10 || count%20==14 || count%20==18 && c!='|')
					 //~ { printf("erreur format"); }
				
					 c= fgetc(fichier);
					 	 if(c!=' ' || c!='\n')
					 {count++;}
					 if((count%20==2 || count%20==6 || count%20==8 || count%20 == 10 || count%20==14 || count%20==18) && c!='|')
					 { printf("erreur format"); }
					 if((count%20==1 || count%20==19) && c=='/') nombre_bars_vertical++;
					  //printf("%d nombre_bars_vertical\n",nombre_bars_vertical);
					  if(c==EOF && nombre_bars_vertical!=2*NT) printf("erreur format bars /");
				
					printf("%c\n",c);
         }
}	 
fclose(fichier);

return 1;
}  
int main(){
int check_etat_alphabet=0;
int check_format=0;

T_machine T;
//T=init_NC_alphabet(T);
 init_NT(T);
init_NR(T);
printf("%dNT \n",NT);
check_etat_alphabet=verifier_format_etat_alphabet();
check_format=verifier_format_transition_ruban_1();
//printf("%d\n",check_etat_alphabet);
   //~ char c;  
	//~ FILE* fichier = NULL;
    //~ fichier = fopen("fichier", "r");
//~ while(c!=EOF){c=fgetc(fichier); printf("%c \n", c);}
//~ fclose(fichier);
return 0;
}
