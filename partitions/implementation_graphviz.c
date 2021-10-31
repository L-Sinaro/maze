//gcc implementation_graphviz.c -o implementation_graphviz -Wall -Wextra `pkg-config libgvc --cflags` -g -lcgraph -lgvc
#include "implementation_graphviz.h"

static void affiche_arbre_graphe(cellule_t ** table, int x, Agnode_t * pere, Agraph_t * graphe)
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
        if (pere)
        {
            agedge(graphe, fils, pere, NULL, 1);
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

//pour avoir les classes sur des fichiers séparés

/*

void lister_graph(partition_arborescence_t * pa)
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
    graphe = agopen(nomgraphe, Agdirected, 0);

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

*/

void lister_graph(partition_arborescence_t * pa)
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
    fichier = fopen("demo.dot", "w");
    graph_context = gvContext();
    graphe = agopen("mon graphe", Agdirected, 0);
    
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
            affiche_arbre_graphe(table, i, racine, graphe);
        }
    }

    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    system("dot -Tpng demo.dot -o graph.png");
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);

    free(table);
}
/*
void lister_graph(partition_arborescence_t * pa)
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
    fichier = fopen("demo.dot", "w");
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
            affiche_arbre_graphe(table, i, racine, graphe);
        }
    }

    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    system("dot -Tpng demo.dot -o graph.png");
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);

    free(table);
}
*/


/*
int main()
{
    Agraph_t * graphe;
    Agnode_t * n1, * n2;
    Agedge_t *ar1;
    GVC_t *graph_context;

    FILE * fichier;
    
    fichier = fopen("demo.dot", "w");
    graph_context = gvContext();
    graphe = agopen("mon graphe", Agdirected, 0);

    n1 = agnode(graphe, "1", 1);
    n2 = agnode(graphe, "2", 1);
    ar1 = agedge(graphe, n1, n2, NULL, 1);
    //agwrite(graphe, stdout);
    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    system("dot -Tpng demo.dot -o graph.png");
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);
    return 0;
} 
*/