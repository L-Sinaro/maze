#include "graphviz-partitions.h"


static void parcourirFilsGraphviz(Maillon_t ** tableauFils, Maillon_t * cour, Agnode_t * pere, Partition_t partition, Agraph_t * graphe)
{
    char string[5];
    Agnode_t * fils;
    
    if (cour != NULL)
    {
        snprintf(string, 5, "%d", cour->v);
        fils = agnode(graphe, string, 1);
        
        if (!pere)
        {
            snprintf(string, 5, "%d", recupererClasse(partition,cour->v));
            pere = agnode(graphe, string, 1);
        }
        agedge(graphe, fils, pere, NULL, 1);

        parcourirFilsGraphviz(tableauFils, cour->suivant, pere, partition, graphe);
        
        if (!estUneRacine(partition,cour->v))
        {
            parcourirFilsGraphviz(tableauFils, tableauFils[cour->v], fils, partition, graphe);
        }

        cour = cour->suivant;
    }
}


int listerClasseGraphviz(Partition_t partition, int etiquette)
{
    Maillon_t ** tableauFils = genererListeFils(partition);
    if (!tableauFils)
    {
        fprintf(stderr, "Erreur : alloc tableau fils impossible\n");
        exit(EXIT_FAILURE);
    }

    int classe = recupererClasse(partition, etiquette);

    Agraph_t * graphe;
    GVC_t *graph_context;
    FILE * fichier;

    fichier = fopen("classe.dot", "w");
    if (!fichier)
    {
        fprintf(stderr, "Erreur : ouverture fichier lister classe impossible\n");
        exit(EXIT_FAILURE);
    }

    
    graph_context = gvContext();
    graphe = agopen("mon graphe", Agdirected, 0);

    parcourirFilsGraphviz(tableauFils, tableauFils[classe], NULL, partition, graphe);
    
    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", fichier);
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(fichier);
    libererTableauFils(partition, tableauFils);

    system("dot -Tpng classe.dot -o graph-classe.png");

    return gvFreeContext(graph_context);
}



int listerPartitionsGraphviz(Partition_t partition)
{
    Maillon_t ** tableauFils = genererListeFils(partition);
    if (!tableauFils)
    {
        fprintf(stderr, "Erreur : alloc tableau fils impossible\n");
        exit(EXIT_FAILURE);
    }
    Maillon_t * racines = genererListeRacines(partition);
    if (!racines)
    {
        fprintf(stderr, "Erreur : alloc liste des racines impossible\n");
        exit(EXIT_FAILURE);
    }
    Maillon_t * cour = racines;
    
    Agraph_t * graphe;
    GVC_t *graph_context;
    FILE * dotFile;

    dotFile = fopen("partition.dot", "w");
    if (!dotFile)
    {
        fprintf(stderr, "Erreur : ouverture fichier lister classe impossible\n");
        exit(EXIT_FAILURE);
    }

    graph_context = gvContext();
    graphe = agopen("mon graphe", Agdirected, 0);

    while (cour)
    {
        parcourirFilsGraphviz(tableauFils, tableauFils[cour->v], NULL, partition, graphe);
        cour = cour->suivant;
    }
    
    gvLayout(graph_context, graphe, "dot");
    gvRender(graph_context, graphe, "dot", dotFile);
    gvFreeLayout(graph_context, graphe);
    agclose(graphe);
    fclose(dotFile);
    
    system("dot -Tpng partition.dot -o graph-partition.png");

    return gvFreeContext(graph_context);
}