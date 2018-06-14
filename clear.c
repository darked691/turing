
void clear(GtkWidget * pWidjet)
{// clear de tout les decendants du widjet 

	GList *pList;
	GList *pList2;
    /* Recuperation de la liste des elements que contient la GtkVBox */
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)pWidjet));
	
	GList *l;// pour eviter que le for fasse 2 lignes
	for (l = pList; l != NULL; l = l->next)
		{
			if(GTK_IS_CONTAINER( l->data)){
				pList2 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)l->data));
				clear(l->data);
			}
		gtk_widget_destroy( l->data);
	
	}
	g_list_free(pList);
	g_list_free(l);
}
