#include "definition.h"
#ifndef H_GL_LOG
#define H_GL_LOG
FILE** creation_log_latex();
void ecrire_log(T_machine T,FILE* fichier1,FILE* fichier2,FILE* fichier3,int *position_texte);
void fermeture_log(FILE* fichier1,FILE* fichier2,FILE* fichier3);
#endif
