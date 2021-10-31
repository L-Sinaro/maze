#include "kruskal.h"

void affiche_aretes(aretes_t * listeAretes, int len)
{
    int i;
    for (i=0;i<len;++i)
    {
        printf("(%d ,%d) ",  (listeAretes[i]).i , (listeAretes[i]).j);
    }
    printf("\n");
}


partition_arborescence_t * kruskalPartition(graphe_t * graphe)
{
    partition_arborescence_t * pa;
    pa = creer_pa((*graphe).nb_noeuds);
    aretes_t * liste = (*graphe).liste_aretes; 
    aretes_t * listeAretes;
    int noeud_i;
    int noeud_j;
    listeAretes = malloc(sizeof(aretes_t)*(*graphe).nb_aretes);
    int i; //qui va parcourir la liste d'aretes du graphe
    int index = 0; //qui va tenir la position du dernier element pour listeAretes

    for (i=0;i<(*graphe).nb_aretes;++i)
    {
        noeud_i = (liste[i]).i;
        noeud_j = (liste[i]).j;
        //fusion_pa(pa, noeud_i, noeud_j);
        if ( (recherche_classe(pa, ((liste[i]).i))) != (recherche_classe(pa, ((liste[i]).j) )) ) 
        {
            //printf("oui\n");
            listeAretes[index].i =  (liste[i]).i;
            listeAretes[index].j =  (liste[i]).j;
            ++index;
        }
        fusion_pa(pa, noeud_i, noeud_j);
    }

    //printf("resultat Kruska : \n");
    //affiche_aretes(listeAretes, index);
    free(listeAretes);

    return pa;
}


graphe_t * kruskalGraphe(graphe_t * graphe, float p)
{
    graphe_t * res;
    partition_arborescence_t * pa;
    pa = creer_pa((*graphe).nb_noeuds);
    aretes_t * liste = (*graphe).liste_aretes; 
    aretes_t * listeAretes;
    int noeud_i;
    int noeud_j;
    listeAretes = malloc(sizeof(aretes_t)*(*graphe).nb_aretes);
    res = malloc(sizeof(graphe_t));
    int i; //qui va parcourir la liste d'aretes du graphe
    int index = 0; //qui va tenir la position du dernier element pour listeAretes

    for (i=0;i<(*graphe).nb_aretes;++i)
    {
        noeud_i = (liste[i]).i;
        noeud_j = (liste[i]).j;
        //fusion_pa(pa, noeud_i, noeud_j);
        if ( (recherche_classe(pa, ((liste[i]).i))) != (recherche_classe(pa, ((liste[i]).j) )) || ((((float) rand())/ ((float) RAND_MAX)) > p)) 
        {
            //printf("oui\n");
            fusion_pa(pa, noeud_i, noeud_j);
            listeAretes[index].i =  (liste[i]).i;
            listeAretes[index].j =  (liste[i]).j;
            ++index;
        }
    }
    (*res).capacite = (*graphe).nb_aretes;
    (*res).nb_aretes = index;
    (*res).nb_noeuds = (*graphe).nb_noeuds;
    (*res).liste_aretes = listeAretes;
    //printf("resultat Kruskal : \n");
    //affiche_aretes(listeAretes, index);
    //lister_foret(pa); //pour avoir la foret
    libere_pa(pa);

    return res;
}