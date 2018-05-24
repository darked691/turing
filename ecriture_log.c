#include "definition.h"
//creation des fichiers log et écritures des elements initiales dans le fichier 
void creation_log_latex()
{

	G_fichier=malloc(sizeof(FILE)*3);
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
void ecrire_log(T_machine T)
{
//fichier 1
fputc(10,G_fichier[0]);
fputs("Etat actuel: ",G_fichier[0]);
fprintf(G_fichier[0],"%d ",T.table_transition[T.derniere_transition].etat_actuel);

fputs("Etat suivant: ",G_fichier[0]);
fprintf(G_fichier[0],"%d ",T.table_transition[T.derniere_transition].etat_suivant);

fputs("symbole actuel: ",G_fichier[0]);
fprintf(G_fichier[0],"%s ",T.table_transition[T.derniere_transition].symbole_actuel);

fputs("symbole suivant: ",G_fichier[0]);
fprintf(G_fichier[0],"%s ",T.table_transition[T.derniere_transition].symbole_suivant);

fputs("direction: ",G_fichier[0]);
fputs(T.table_transition[T.derniere_transition].direction,G_fichier[0]);
//fprintf(fichier1,"%s ",T.table_transition[2].direction);
fputc(10,G_fichier[0]);
//fichier 2
fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 1000",G_fichier[1]);
position_texte[0]=position_texte[0]+290;
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("Etat actuel ",G_fichier[1]);
fprintf(G_fichier[1],"%d",T.table_transition[T.derniere_transition].etat_actuel);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 2300",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("Etat suivant: ",G_fichier[1]);
fprintf(G_fichier[1],"%d ",T.table_transition[T.derniere_transition].etat_suivant);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 3800",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("symbole actuel: ",G_fichier[1]);
fprintf(G_fichier[1],"%s ",T.table_transition[T.derniere_transition].symbole_actuel);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 5900",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("symbole suivant: ",G_fichier[1]);
fprintf(G_fichier[1],"%s ",T.table_transition[T.derniere_transition].symbole_suivant);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 8080",G_fichier[1]);
fprintf(G_fichier[1]," %d ",position_texte[0]);
fputs("direction: ",G_fichier[1]);
fprintf(G_fichier[1],"%s ",T.table_transition[T.derniere_transition].direction);
fputc(92,G_fichier[1]);
fputs("001\n",G_fichier[1]);

//fichier 3
fputs("100 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
//fputs("(Etat 2) show\n",fichier3);
fputs("(Etat actuel:",G_fichier[2]);
fprintf(G_fichier[2],"%d",T.table_transition[2].etat_actuel);
fputs(")show\n",G_fichier[2]);

fputs("150 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(Etat suivant:",G_fichier[2]);
fprintf(G_fichier[2],"%d",T.table_transition[2].etat_suivant);
fputs(")show\n",G_fichier[2]);

fputs("210 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(symbole actuel:",G_fichier[2]);
fprintf(G_fichier[2],"%s",T.table_transition[2].symbole_actuel);
fputs(")show\n",G_fichier[2]);

fputs("290 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(Symbole suivant:",G_fichier[2]);
fprintf(G_fichier[2],"%s",T.table_transition[2].symbole_suivant);
fputs(")show\n",G_fichier[2]);

fputs("370 ",G_fichier[2]);
fprintf(G_fichier[2],"%d",position_texte[1]);
fputs(" 16 sub moveto\n",G_fichier[2]);
fputs("(direction:",G_fichier[2]);
fprintf(G_fichier[2],"%s",T.table_transition[2].direction);
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
//écriture des éléments finaux pour chacun de ses 3 fichier et fermeture de ces fichiers
//~ void fermeture_log(FILE* fichier1,FILE* fichier2,FILE* fichier3)
//~ {
//~ fputs("showpage\n",fichier3);
//~ fputc(92,fichier1);
//~ fputs("end{verbatim}",fichier1);
//~ fputc(10,fichier1);
//~ fputc(92,fichier1);
//~ fputs("end{document}",fichier1);
//~ fclose(fichier1);
//~ fclose(fichier2);
//~ fclose(fichier3);
//~ }
