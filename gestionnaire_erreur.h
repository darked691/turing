
#include "definition.h"
#ifndef H_GL_ERR
#define H_GL_ERR
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


void equalone(GtkButton *button, gpointer value);
void equalzero(GtkButton *button, gpointer value);
void err_affiche_message_ok(char* message);
int err_affiche_message_YN(char* message);
void err_format(char* code);
void err_introuvable(char* code);
int err_existant(char* code);
void err_caractere_indefini(char* code);
#endif
