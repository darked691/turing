#include "definition.h"
//creation des fichiers log et écritures des elements initiales dans le fichier 
FILE** creation_log_latex()
{
	FILE** fichier;
	fichier=malloc(sizeof(FILE)*3);
	//creation du premier fichier log en latex 
	fichier[0]=fopen("log.tex","w");
	fputc(92,fichier[0]);
	//écriture des éléments initiales dans le fichier latex
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
//creation du deuxième fichier log en xfig
fichier[1]=fopen("log.fig","w");
//écriture des éléments initiales dans le fichier xfig
fputs("#FIG 3.2  Produced by xfig version 3.2.7\n",fichier[1]);
fputs("Landscape\n",fichier[1]);
fputs("Center\n",fichier[1]);
fputs("Metric\n",fichier[1]);
fputs("A4\n",fichier[1]);
fputs("100.00\n",fichier[1]);
fputs("Single\n",fichier[1]);
fputs("-2\n",fichier[1]);
fputs("1200 2\n",fichier[1]);
fputs("4 0 0 50 -1 0 12 0.0000 4 135 420 1400 0 ",fichier[1]);
fputs("Transition effectue",fichier[1]);
fputc(92,fichier[1]);
fputs("001\n",fichier[1]);
//fichier3
//creation du troisième fichier log en Postscript
fichier[2]=fopen("log.ps","w");
//écriture des éléments initiales dans le fichier ps
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
//écriture de la dernière transition effectué  contenue dans la variable "int derniere_transition"	pour chaque fichier
void ecrire_log(T_machine T,FILE* fichier1,FILE* fichier2,FILE* fichier3,int *position_texte,int derniere_transition)
{
//fichier 1
fputc(10,fichier1);
fputs("Etat actuel: ",fichier1);
fprintf(fichier1,"%d ",T.table_transition[derniere_transition].etat_actuel);

fputs("Etat suivant: ",fichier1);
fprintf(fichier1,"%d ",T.table_transition[derniere_transition].etat_suivant);

fputs("symbole actuel: ",fichier1);
fprintf(fichier1,"%s ",T.table_transition[derniere_transition].symbole_actuel);

fputs("symbole suivant: ",fichier1);
fprintf(fichier1,"%s ",T.table_transition[derniere_transition].symbole_suivant);

fputs("direction: ",fichier1);
fputs(T.table_transition[derniere_transition].direction,fichier1);
//fprintf(fichier1,"%s ",T.table_transition[2].direction);
fputc(10,fichier1);
//fichier 2
fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 1000",fichier2);
position_texte[0]=position_texte[0]+290;
fprintf(fichier2," %d ",position_texte[0]);
fputs("Etat actuel ",fichier2);
fprintf(fichier2,"%d",T.table_transition[derniere_transition].etat_actuel);
fputc(92,fichier2);
fputs("001\n",fichier2);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 2300",fichier2);
fprintf(fichier2," %d ",position_texte[0]);
fputs("Etat suivant: ",fichier2);
fprintf(fichier2,"%d ",T.table_transition[derniere_transition].etat_suivant);
fputc(92,fichier2);
fputs("001\n",fichier2);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 3800",fichier2);
fprintf(fichier2," %d ",position_texte[0]);
fputs("symbole actuel: ",fichier2);
fprintf(fichier2,"%s ",T.table_transition[derniere_transition].symbole_actuel);
fputc(92,fichier2);
fputs("001\n",fichier2);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 5900",fichier2);
fprintf(fichier2," %d ",position_texte[0]);
fputs("symbole suivant: ",fichier2);
fprintf(fichier2,"%s ",T.table_transition[derniere_transition].symbole_suivant);
fputc(92,fichier2);
fputs("001\n",fichier2);

fputs("4 0 0 50 -1 0 14 0.0000 4 135 1400 8080",fichier2);
fprintf(fichier2," %d ",position_texte[0]);
fputs("direction: ",fichier2);
fprintf(fichier2,"%s ",T.table_transition[derniere_transition].direction);
fputc(92,fichier2);
fputs("001\n",fichier2);

//fichier 3
fputs("100 ",fichier3);
fprintf(fichier3,"%d",position_texte[1]);
fputs(" 16 sub moveto\n",fichier3);
//fputs("(Etat 2) show\n",fichier3);
fputs("(Etat actuel:",fichier3);
fprintf(fichier3,"%d",T.table_transition[derniere_transition].etat_actuel);
fputs(")show\n",fichier3);

fputs("150 ",fichier3);
fprintf(fichier3,"%d",position_texte[1]);
fputs(" 16 sub moveto\n",fichier3);
fputs("(Etat suivant:",fichier3);
fprintf(fichier3,"%d",T.table_transition[derniere_transition].etat_suivant);
fputs(")show\n",fichier3);

fputs("210 ",fichier3);
fprintf(fichier3,"%d",position_texte[1]);
fputs(" 16 sub moveto\n",fichier3);
fputs("(symbole actuel:",fichier3);
fprintf(fichier3,"%s",T.table_transition[derniere_transition].symbole_actuel);
fputs(")show\n",fichier3);

fputs("290 ",fichier3);
fprintf(fichier3,"%d",position_texte[1]);
fputs(" 16 sub moveto\n",fichier3);
fputs("(Symbole suivant:",fichier3);
fprintf(fichier3,"%s",T.table_transition[derniere_transition].symbole_suivant);
fputs(")show\n",fichier3);

fputs("370 ",fichier3);
fprintf(fichier3,"%d",position_texte[1]);
fputs(" 16 sub moveto\n",fichier3);
fputs("(direction:",fichier3);
fprintf(fichier3,"%s",T.table_transition[derniere_transition].direction);
fputs(")show\n",fichier3);

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
//écriture des éléments finaux pour chacun de ses 3 fichier et fermeture de ces fichiers
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
