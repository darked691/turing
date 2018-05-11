#include "definition.h"
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
