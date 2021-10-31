#include "implementation_graphviz.h"


void matrice_graph(int ** tab, int size)
{
    int i;
    int j;
    Agraph_t * graphe;
    GVC_t *graph_context;
    FILE * fichier;
    char noeud[5];
    Agnode_t ** noeuds;

    noeuds = malloc(sizeof(Agnode_t *) *size);
    fichier = fopen("graphe.dot", "w");
    graph_context = gvContext();
    graphe = agopen("mon graphe", Agundirected, 0);

    for (i=0; i<size;i++)
    {
        snprintf(noeud, 5, "%d", i);
        noeuds[i] = agnode(graphe, noeud, 1);
    }

    for (j=0; j<size;j++)
    {
        for (i=j+1; i<size; ++i)
        {
            if (tab[i][j])
            {
                agedge(graphe, noeuds[i], noeuds[j], NULL, 1);
            }
        }
    }

    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    system("dot -Tpng graphe.dot -o graph.png");
    free(noeuds);
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);

}

void graphe_graph(graphe_t * graphe)
{
    int i;
    int nb_noeuds = (*graphe).nb_noeuds;
    Agraph_t * Aggraphe;
    GVC_t *graph_context;
    FILE * fichier;
    char noeud[5];
    Agnode_t ** tab_noeuds;
    aretes_t * liste = (*graphe).liste_aretes;

    tab_noeuds = malloc(sizeof(Agnode_t *)*nb_noeuds);
    fichier = fopen("graphe.dot", "w");
    graph_context = gvContext();
    Aggraphe = agopen("mon graphe", Agundirected, 0);

    for (i=0; i<nb_noeuds;i++)
    {
        snprintf(noeud, 5, "%d", i);
        tab_noeuds[i] = agnode(Aggraphe, noeud, 1);
    }

    for (i=0; i<(*graphe).nb_aretes;i++)
    {
        agedge(Aggraphe, tab_noeuds[(liste[i].i)], tab_noeuds[(liste[i].j)], NULL, 1);
    }

    gvLayout(graph_context, Aggraphe, "dot");
    gvRender(graph_context, Aggraphe, "dot", fichier);
    system("dot -Tpng graphe.dot -o graph.png");

    free(tab_noeuds);
    gvFreeLayout(graph_context, Aggraphe);
    agclose(Aggraphe);
    fclose(fichier);

}

void graphe_arbre(graphe_t * graphe)
{
    int i;
    int nb_noeuds = (*graphe).nb_noeuds;
    Agraph_t * Aggraphe;
    GVC_t *graph_context;
    FILE * fichier;
    char noeud[5];
    Agnode_t ** tab_noeuds;
    aretes_t * liste = (*graphe).liste_aretes;

    tab_noeuds = malloc(sizeof(Agnode_t *)*nb_noeuds);
    fichier = fopen("kruskal.dot", "w");
    graph_context = gvContext();
    Aggraphe = agopen("mon graphe", Agundirected, 0);

    for (i=0; i<nb_noeuds;i++)
    {
        snprintf(noeud, 5, "%d", i);
        tab_noeuds[i] = agnode(Aggraphe, noeud, 1);
    }

    for (i=0; i<(*graphe).nb_aretes;i++)
    {
        agedge(Aggraphe, tab_noeuds[(liste[i].i)], tab_noeuds[(liste[i].j)], NULL, 1);
    }

    gvLayout(graph_context, Aggraphe, "dot");
    gvRender(graph_context, Aggraphe, "dot", fichier);
    system("dot -Tpng kruskal.dot -o kruskal.png");

    free(tab_noeuds);
    gvFreeLayout(graph_context, Aggraphe);
    agclose(Aggraphe);
    fclose(fichier);

}

static void affiche_arbre_graphe(cellule_t ** table, int x, Agnode_t * pere, Agraph_t * graphe, int racine)
{   
    cellule_t * cour = table[x];
    cellule_t * temp;
    int val;
    char noeud[5];
    Agnode_t * fils;

    while (cour)
    {   
        val = (*cour).valeur;
        snprintf(noeud, 5, "%d", val);
        fils = agnode(graphe, noeud, 1);
        if (pere && (val != racine))
        {
            agedge(graphe, fils, pere, NULL, 1);
        }
        temp = cour;
        cour = (*cour).suiv;
        free(temp);
        if ((cour) && (((*cour).valeur) != x))
        {
            affiche_arbre_graphe(table, (*cour).valeur, fils, graphe, racine);
        }
    }
}

void lister_graph_composantes_connexes(partition_arborescence_t * pa)
{
    cellule_t ** table = NULL;
    int taille = (*pa).size;
    int i;
    cellule_t * cel;
    Agraph_t * graphe;
    GVC_t *graph_context;
    FILE * fichier;
    Agnode_t * racine;
    char noeud[5];

    table = calloc(taille, sizeof(cellule_t *));
    fichier = fopen("cc.dot", "w");
    graph_context = gvContext();
    graphe = agopen("mon graphe", Agundirected, 0);
    
    for (i=0; i<taille;++i)
    {
        cel = creation_bloc(i);
        adj_cel(cel, &(table[((*pa).tab)[i]]));
    }

    for (i=0; i<taille;i++)
    {
        if ((table[i]) && (i == ((*pa).tab)[i]))
        {
            snprintf(noeud, 50, "%d", i);
            racine = agnode(graphe, noeud, 1);
            affiche_arbre_graphe(table, i, racine, graphe, i);
        }
    }

    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    system("dot -Tpng cc.dot -o cc.png");
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);

    free(table);
}

void lister_foret(partition_arborescence_t * pa)
{
    cellule_t ** table = NULL;
    int taille = (*pa).size;
    int i;
    cellule_t * cel;
    Agraph_t * graphe;
    GVC_t *graph_context;
    FILE * fichier;
    Agnode_t * racine;
    char noeud[5];

    table = calloc(taille, sizeof(cellule_t *));
    fichier = fopen("foret.dot", "w");
    graph_context = gvContext();
    graphe = agopen("mon graphe", Agdirected, 0);
    
    for (i=0; i<taille;++i)
    {
        cel = creation_bloc(i);
        adj_cel(cel, &(table[((*pa).tab)[i]]));
    }
    //printf("contenu table :\n");
    //affiche_table(table, taille);
    //printf("------------\n");   //
    for (i=0; i<taille;i++)
    {
        if ((table[i]) && (i == ((*pa).tab)[i]))
        {
            snprintf(noeud, 50, "%d", i);
            racine = agnode(graphe, noeud, 1);
            affiche_arbre_graphe(table, i, racine, graphe, i);
        }
    }

    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    system("dot -Tpng foret.dot -o foret.png");
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);

    free(table);
}

//pour avoir les classes sur des fichiers séparés

/*

static void affiche_arbre_graphe(cellule_t ** table, int x, Agnode_t * pere, Agraph_t * graphe)
{   
    cellule_t * cour = table[x];
    cellule_t * temp;
    int val;
    char noeud[5];
    Agnode_t * fils;
    Agedge_t *ar;

    while (cour)
    {   
        val = (*cour).valeur;
        snprintf(noeud, 5, "%d", val);
        fils = agnode(graphe, noeud, 1);
        if (pere)
        {
            ar = agedge(graphe, fils, pere, NULL, 1);
        }
        temp = cour;
        cour = (*cour).suiv;
        free(temp);
        if ((cour) && (((*cour).valeur) != x))
        {
            affiche_arbre_graphe(table, (*cour).valeur, fils, graphe);
        }
    }
}



void creer_graph(partition_arborescence_t * pa, cellule_t ** table, int i)
{
    Agraph_t * graphe;
    GVC_t *graph_context;
    FILE * fichier;
    Agnode_t * racine;
    char noeud[5];
    char commande[50];
    char nomfichier[30];
    char nomgraphe[30];

    snprintf(nomfichier, 50, "demo%d.dot", i);
    fichier = fopen(nomfichier, "w");
    graph_context = gvContext();
    snprintf(nomgraphe, 50, "mon graphe %d", i);
    graphe = agopen(nomgraphe, Agundirected, 0);

    table = table_classe_pa(pa);
    
    snprintf(noeud, 50, "%d", i);
    racine = agnode(graphe, noeud, 1);
    affiche_arbre_graphe(table, i, racine, graphe);

    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    snprintf(commande, 50, "dot -Tpng demo%d.dot -o graph%d.png", i, i);
    system(commande);
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);

}

void lister_graph_composantes_connexes(partition_arborescence_t * pa)
{
    cellule_t ** table = NULL;
    int taille = (*pa).size;
    int i;
    cellule_t * cel;

    table = calloc(taille, sizeof(cellule_t *));
    
    for (i=0; i<taille;++i)
    {
        cel = creation_bloc(i);
        adj_cel(cel, &(table[((*pa).tab)[i]]));
    }

    for (i=0; i<taille;i++)
    {
        if ((table[i]) && (i == ((*pa).tab)[i]))
        {
            creer_graph(pa, table, i);
        }
    }

    free(table);
}

*/