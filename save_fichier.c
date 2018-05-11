#include "definition.h"
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
Info_machine conversion_donne_fichier(Info_machine I,T_machine T)	
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
	 //remplir le tableau etat d'état le trier et l'écrire dans le fichier
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
		//for(i=0;i<NT+1;i++)  printf(" etat %d\n",etat[i]);
	tri_a_bulle_c(etat,NT+1);
	//for(i=0;i<NT+1;i++)  printf(" etat apres le tri %d\n",etat[i]);
	
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
