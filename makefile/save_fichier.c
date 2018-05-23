#include "save_fichier.h"
//tri un tableau dans l'ordre croissant
void tri_a_bulle_c(int *t,int n){

    int j =0;int tmp =0;int test =1;

    while(test){

        test = 0;

        for(j =0; j < n-1; j++){

            if(t[j] > t[j+1]){

                    tmp = t[j+1];

                    t[j+1] = t[j];t[j] = tmp;

                    test = 1;

            }

        }

    }

}
//sauvegarde un fichier
void conversion_donne_fichier(char* path, Info_machine I)	
{	int i=0;
	int y=0;
	NC = strlen(I.alphabet);
	//~ int ite=0;
	//~ for(ite=0;I.transition[0].symbole_actuel[ite]!='\0';ite++) {}
	
	//~ printf("ite %d\n",ite);
	//~ I.transition=malloc(sizeof(Transition)*NT+1);
	//~ ce que ta fait I.transition[NT+1]=NULL;
	//~ while(I.transition[y].!=NULL) nombre_transition++;

	int ite;
	 int etat[NT+1];
	 for(i=0;i<NT+1;i++) etat[i]=-1;
	 etat[0]=I.transition[0].etat_actuel;
	 printf("NT %d\n",NT);
	 //remplir le tableau etat d'Ã©tat le trier et l'Ã©crire dans le fichier
	 	 for(ite=0;ite<NT;ite++)
	 	 {
			 printf("etat_suivant %d\n",I.transition[ite].etat_suivant);
			  printf("ite %d\n",ite);

			  for(i=0;i<NT+1;i++)
			 {
			 if(I.transition[ite].etat_suivant==etat[i])
			 {
				 //printf("ok");
				 i=NT+1;
			 }
			 if(etat[i]==-1)
			 {
				 etat[i]=I.transition[ite].etat_suivant;
				 printf("i %d",i);
				 				  printf(" etat %d\n",etat[i]);
				  printf("etat_suivant_dans boucle %d\n",I.transition[ite].etat_suivant);
				 i=NT+1;
				 

				   
			 }	  
			 
			 }
			
		}
		//for(i=0;i<NT+1;i++)  printf(" etat %d\n",etat[i]);
	tri_a_bulle_c(etat,NT+1);
	//for(i=0;i<NT+1;i++)  printf(" etat apres le tri %d\n",etat[i]);
	
	FILE* fichier = NULL;
    fichier = fopen(path, "w");
    char c='\0';
    int j=0;
    while(etat[j]==-1) ++j;
    //printf(" j %d",j);
    
    //ecriture de l'ensemble des Ã©tats
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
    
    //ecriture de l'ensemble des caractÃ©res de l'alphabets
    j=0;
    fputs("[",fichier);
    while(j<NC)
    {
	fprintf(fichier,"%c",I.alphabet[j]);
	if(j<NC-1) fputs(",",fichier);
    j++;
	}
	fputs("]",fichier);
    fputs("\n",fichier);
    fputs("\n",fichier);
    j=0;
    
  //ecriture des transitions    
    while(j<NT)
    {
	fputs("/",fichier);	
	fputs("|",fichier);	
	fputs(I.transition[j].symbole_actuel,fichier);
	fputs("|",fichier);	
	fprintf(fichier,"%d",I.transition[j].etat_actuel);
	fputs("|",fichier);	
	fprintf(fichier,"%d",I.transition[j].etat_suivant);
	fputs("|",fichier);	
	fputs(I.transition[j].symbole_suivant,fichier);
	fputs("|",fichier);	
	fputs(I.transition[j].direction,fichier);
	fputs("|",fichier);	
	fputs("/",fichier);	
	fputs("\n",fichier);
    j++;
	}
	 	fclose(fichier);
	 	for(i=0;i<NT+1;i++) 
	 	printf(" %d etat a la fin de la boucle \n", etat[i]);

}

