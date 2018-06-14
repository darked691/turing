#include "definition.h"
//creation des fichiers log et écritures des elements initiales dans le fichier 
void creation_log_latex()
{

	G_fichier=calloc(3, sizeof(FILE));
	//creation du premier fichier log en latex 
	G_fichier[0]=fopen("log.tex","w");
	fputc(92,G_fichier[0]);
	//écriture des éléments initiales dans le fichier latex
fputs("documentclass{article}",G_fichier[0]);
fputc(10,G_fichier[0]);
fputc(92,G_fichier[0]);
fputs("begin{document}",G_fichier[0]);
fputc(10,G_fichier[0]);
fputc(92,G_fichier[0]);
fputs("subsection{Log}",G_fichier[0]);
fputc(10,G_fichier[0]);
fputc(92,G_fichier[0]);
fputs("begin{verbatim}",G_fichier[0]);
fputc(10,G_fichier[0]);
fputs("Transition effectue:",G_fichier[0]);
//fichier2
//creation du deuxième fichier log en xfig
G_fichier[1]=fopen("log.fig","w");
//écriture des éléments initiales dans le fichier xfig
fputs("#FIG 3.2  Produced by xfig version 3.2.7\n",G_fichier[1]);
fputs("Landscape\n",G_fichier[1]);
fputs("Center\n",G_fichier[1]);
fputs("Metric\n",G_fichier[1]);
fputs("A4\n",G_fichier[1]);
fputs("100.00\n",G_fichier[1]);
fputs("Single\n",G_fichier[1]);
fputs("-2\n",G_fichier[1]);
fputs("1200 2\n",G_fichier[1]);
fputs("4 0 0 50 -1 0 12 0.0000 4 135 420 1400 0 ",G_fichier[1]);
fputs("Transition effectue",G_fichier[1]);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);
//fichier3
position_texte[1]=790;
//creation du troisième fichier log en Postscript
G_fichier[2]=fopen("log.ps","w");
//écriture des éléments initiales dans le fichier ps
fputs("%!PS-Adobe-3.0\n\n",G_fichier[2]);
fputs("%%Page: 1 1\n",G_fichier[2]);
fputs("%%BeginPageSetup\n",G_fichier[2]);
fputs(" /pgsave save def\n",G_fichier[2]);
fputs("%%IncludeResource: font TimesRoman\n",G_fichier[2]);
fputs("%%EndPageSetup\n",G_fichier[2]);
fputs(" /Helvetica findfont 8 scalefont setfont\n",G_fichier[2]);
fputs("100 800 16 sub moveto\n",G_fichier[2]);
fputs("(Transition effectue:) show\n",G_fichier[2]);

}	
//écriture de la dernière transition effectué  contenue dans la variable "int derniere_transition"	pour chaque fichier
void ecrire_log(T_machine *T)
{
//fichier 1
fputc(10,G_fichier[0]); 

fputs("Etat actuel: ",G_fichier[0]);
fprintf(G_fichier[0],"%d, ",T->table_transition[T->derniere_transition].etat_actuel);

fputs("Etat suivant: ",G_fichier[0]);
fprintf(G_fichier[0],"%d, ",T->table_transition[T->derniere_transition].etat_suivant);

fputs("symbole actuel: ",G_fichier[0]);
fprintf(G_fichier[0],"%s,",T->table_transition[T->derniere_transition].symbole_actuel);

fputs("symbole suivant: ",G_fichier[0]);
fprintf(G_fichier[0],"%s, ",T->table_transition[T->derniere_transition].symbole_suivant);

fputs("direction: ",G_fichier[0]);
fprintf(G_fichier[0],"%s ",T->table_transition[T->derniere_transition].direction);
//fputc(10,G_fichier[0]);


//fichier 2
fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 1000",G_fichier[1]);
position_texte[0]=position_texte[0]+290;
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("Etat actuel ",G_fichier[1]);
fprintf(G_fichier[1],"%d",T->table_transition[T->derniere_transition].etat_actuel);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 2300",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("Etat suivant: ",G_fichier[1]);
fprintf(G_fichier[1],"%d ",T->table_transition[T->derniere_transition].etat_suivant);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 3800",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("symbole actuel: ",G_fichier[1]);
fprintf(G_fichier[1],"%s ",T->table_transition[T->derniere_transition].symbole_actuel);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 5900",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("symbole suivant: ",G_fichier[1]);
fprintf(G_fichier[1],"%s ",T->table_transition[T->derniere_transition].symbole_suivant);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 8080",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("direction: ",G_fichier[1]);
fprintf(G_fichier[1],"%s ",T->table_transition[T->derniere_transition].direction);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

//fichier 3
fputs("100 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);

fputs("(Etat actuel:",G_fichier[2]);
fprintf(G_fichier[2],"%d",T->table_transition[T->derniere_transition].etat_actuel);
fputs(")show\n",G_fichier[2]);

fputs("150 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(Etat suivant:",G_fichier[2]);
fprintf(G_fichier[2],"%d",T->table_transition[T->derniere_transition].etat_suivant);
fputs(")show\n",G_fichier[2]);

fputs("210 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(symbole actuel:",G_fichier[2]);
fprintf(G_fichier[2],"%s",T->table_transition[T->derniere_transition].symbole_actuel);
fputs(")show\n",G_fichier[2]);

fputs("290 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(Symbole suivant:",G_fichier[2]);
fprintf(G_fichier[2],"%s",T->table_transition[T->derniere_transition].symbole_suivant);
fputs(")show\n",G_fichier[2]);

fputs("370 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(direction:",G_fichier[2]);
fprintf(G_fichier[2],"%s",T->table_transition[T->derniere_transition].direction);
fputs(")show\n",G_fichier[2]);

position_texte[1]=position_texte[1]-10;
if(position_texte[1]==30)
{
fputs("showpage\n",G_fichier[2]);	
position_texte[2]=position_texte[2]+1;
fputs("%%Page: ",G_fichier[2]);
fprintf(G_fichier[2],"%d ",position_texte[2]);
fprintf(G_fichier[2],"%d\n",position_texte[2]);
fputs("%%BeginPageSetup\n",G_fichier[2]);
fputs(" /pgsave save def\n",G_fichier[2]);
fputs("%%IncludeResource: font TimesRoman\n",G_fichier[2]);
fputs("%%EndPageSetup\n",G_fichier[2]);
fputs(" /Helvetica findfont 8 scalefont setfont\n",G_fichier[2]);
fputs("100 800 16 sub moveto\n",G_fichier[2]);
fputs("(Transition effectue:) show\n",G_fichier[2]);
position_texte[1]=790;
}
}

void ecrire_ruban(Ruban **r,int entier)
{
	position_texte[0]=position_texte[0]+300;
	position_texte[1]=position_texte[1]-20;
    int i=0;
    int y=0;
		fputs("\n",G_fichier[0]);
		fputs(" Mots d'entre ",G_fichier[0]);
        fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 2300",G_fichier[1]);
		fprintf(G_fichier[1]," %d ",position_texte[0]);

		fputs(" Mots d'entre ",G_fichier[1]);
		fputc(92,G_fichier[1]);
		fputs("001\n",G_fichier[1]);
		
		
	        fputs("100 ",G_fichier[2]);
		fprintf(G_fichier[2],"%d",position_texte[1]);
		fputs(" 16 sub moveto\n",G_fichier[2]);
		fputs("\n (Mots d'entre) \n",G_fichier[2]);
		fputs("show\n",G_fichier[2]);
		fputs("\n",G_fichier[0]);
		int k=0;
		int x;
		int j=0;
		for(i=0;i<NR;i++)
		{

			k++;
        fputs(mot_a_lire[i],G_fichier[0]);
        fputs("\n",G_fichier[0]);
        //fputc(r[i]->valeur,G_fichier[1]);
        fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 ",G_fichier[1]);
        x=3700+130*k;
        fprintf(G_fichier[1]," %d",x);
		fprintf(G_fichier[1]," %d ",position_texte[0]);
		fprintf(G_fichier[1],"%s ",mot_a_lire[i]);
		fputc(92,G_fichier[1]);
		fputs("001\n",G_fichier[1]);
		        x=200+5*k;
        fprintf(G_fichier[2]," %d ",x);
		fprintf(G_fichier[2],"%d",position_texte[1]);
		fputs(" 16 sub moveto\n",G_fichier[2]);
		 fputs("(",G_fichier[2]);
		fprintf(G_fichier[2],"%s",mot_a_lire[i]);
		fputs(")show\n",G_fichier[2]);
		x=0;
		k=0;
		position_texte[0]=position_texte[0]+300;
		position_texte[1]=position_texte[1]-20;
		}
				fputs("\n",G_fichier[0]);
		fputs(" Mots de sortie ",G_fichier[0]);
        fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 2300",G_fichier[1]);
		fprintf(G_fichier[1]," %d ",position_texte[0]);

		fputs(" Mots de sortie",G_fichier[1]);
		fputc(92,G_fichier[1]);
		fputs("001\n",G_fichier[1]);
		
			        fputs("100 ",G_fichier[2]);
		fprintf(G_fichier[2],"%d",position_texte[1]);
		fputs(" 16 sub moveto\n",G_fichier[2]);
		fputs("\n (Mots de sortie) \n",G_fichier[2]);
		fputs("show\n",G_fichier[2]);
		fputs("\n",G_fichier[0]);	
				
    for(i=0;i<NR;i++)
    {

        while(r[i]->droite!=NULL)
        {
			k++;
        fputc(r[i]->valeur,G_fichier[0]);
        //fputc(r[i]->valeur,G_fichier[1]);
        fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 ",G_fichier[1]);
        x=3700+130*k;
        fprintf(G_fichier[1]," %d",x);
		fprintf(G_fichier[1]," %d ",position_texte[0]);
		fprintf(G_fichier[1],"%c ",r[i]->valeur);
		fputc(92,G_fichier[1]);
		fputs("001\n",G_fichier[1]);
        //fputc(r[i]->valeur,G_fichier[2]);
        x=200+5*k;
        fprintf(G_fichier[2]," %d ",x);
		fprintf(G_fichier[2],"%d",position_texte[1]);
		fputs(" 16 sub moveto\n",G_fichier[2]);
		 fputs("(",G_fichier[2]);
		fprintf(G_fichier[2],"%c",r[i]->valeur);
		fputs(")show\n",G_fichier[2]);
        r[i] = r[i]->droite;

        }
        fputs("\n",G_fichier[0]);
        k=0;
        x=0;
    position_texte[0]=position_texte[0]+300;
	position_texte[1]=position_texte[1]-20;
    }
    position_texte[0]=position_texte[0]+300;
	position_texte[1]=position_texte[1]-20;
    if(entier == 1)
    {
         fputs("\n Mot accepte \n",G_fichier[0]);
         fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 2300",G_fichier[1]);
		fprintf(G_fichier[1]," %d ",position_texte[0]);
		fputs("\n Mot accepte \n",G_fichier[1]);
		fputc(92,G_fichier[1]);
		fputs("001\n",G_fichier[1]);
		
         //fputs("\n Mot accepté \n",G_fichier[1]);
        fputs("100 ",G_fichier[2]);
		fprintf(G_fichier[2],"%d",position_texte[1]);
		fputs(" 16 sub moveto\n",G_fichier[2]);
		fputs(" (Mot accepte)",G_fichier[2]);
		fputs("show\n",G_fichier[2]);
         //fputs("\n Mot accepté \n",G_fichier[2]);
    }
    else if(entier == 0)
    {
        fputs("\n Mot refuse \n",G_fichier[0]);
        fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 2300",G_fichier[1]);
		fprintf(G_fichier[1]," %d ",position_texte[0]);
		fputs("\n MOt refuse \n",G_fichier[1]);
		fputc(92,G_fichier[1]);
		fputs("001\n",G_fichier[1]);
          //fputs("\n Mot refusé \n",G_fichier[1]);
          
        fputs("100 ",G_fichier[2]);
		fprintf(G_fichier[2],"%d",position_texte[1]);
		fputs(" 16 sub moveto\n",G_fichier[2]);
		fputs("\n (Mot refuse) \n",G_fichier[2]);
		fputs("show\n",G_fichier[2]);
         
	  }
	position_texte[0]=position_texte[0]+300;
	position_texte[1]=position_texte[1]-20;
}

//écriture des éléments finaux pour chacun de ses 3 fichier et fermeture de ces fichiers
void fermeture_log()
{
fputs("showpage\n",G_fichier[2]);
fputc(92,G_fichier[0]);
fputs("end{verbatim}",G_fichier[0]);
fputc(10,G_fichier[0]);
fputc(92,G_fichier[0]);
fputs("end{document}",G_fichier[0]);
fclose(G_fichier[0]);
fclose(G_fichier[1]);
fclose(G_fichier[2]);
}
