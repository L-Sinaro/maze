#include "djikstra.h"

graphe_djikstra_t converti_graphe(graphe_t graphe)
{
    graphe_djikstra_t res;
    int i;
    int j;
    int k=0;
    aretes_t arete;
    int nb_noeuds = graphe.nb_noeuds;
    aretes_t * liste_aretes = graphe.liste_aretes;
    res.nb_noeuds = nb_noeuds;
    noeud_t ** liste_voisins = malloc(sizeof(noeud_t *)*nb_noeuds);
    res.indexes_tas = malloc(sizeof(int)*nb_noeuds);
    
    for (i=0;i<nb_noeuds;++i)
    {
        liste_voisins[i]=malloc(sizeof(noeud_t)*5);
        for (j=0;j<4;++j)
        {
            liste_voisins[i][j].noeud = -1;
            liste_voisins[i][j].poids = 1;
        }
        res.indexes_tas[i]=-1;
    }

    for (i=0;i<graphe.nb_aretes;++i)
    {
        arete = liste_aretes[i];
        while (liste_voisins[arete.i][k].noeud != -1)
        {
            ++k;
        }
        liste_voisins[arete.i][k].noeud = arete.j;
        k=0;
        while (liste_voisins[arete.j][k].noeud != -1)
        {
            ++k;
        }
        liste_voisins[arete.j][k].noeud = arete.i;
        k=0;
    }
    res.liste_voisins = liste_voisins;
    return res;    
}



int * djikstra(int depart, graphe_t graphe)
{
    int * tabRes;
    int numero_noeud;
    int voisin;
    int poids_traitement;
    noeud_t noeud_en_traitement;
    int nbTraites = 0;
    int k = 0;
    int nb_noeuds = graphe.nb_noeuds;
    tas_t * tas = createtas(graphe.nb_noeuds);
    tabRes = malloc(sizeof(int)*nb_noeuds);
    graphe_djikstra_t gd = converti_graphe(graphe);
    noeud_t noeud_a_traiter = {depart, 0};
    insertNode(tas, noeud_a_traiter, gd.indexes_tas);
    
    while (nbTraites<nb_noeuds)
    {
        //printf("oui\n");
        noeud_en_traitement = popTas(tas, gd.indexes_tas);
        numero_noeud = noeud_en_traitement.noeud;
        poids_traitement = (*tas).tab[gd.indexes_tas[numero_noeud]].poids;
        gd.indexes_tas[numero_noeud] = -2;
        ++nbTraites;
        //printf("oui3 %d\n", gd.liste_voisins[0][0].noeud);
        while ((k<4) && (((gd.liste_voisins)[numero_noeud][k]).noeud != -1) )
        {
            //printf("oui3 %d\n", numero_noeud);
            voisin = gd.liste_voisins[numero_noeud][k].noeud;
            if (gd.indexes_tas[voisin] != -2 )
            {
                if (gd.indexes_tas[voisin] == -1)
                {
                    
                    noeud_a_traiter.noeud = voisin;
                    noeud_a_traiter.poids = poids_traitement + gd.liste_voisins[numero_noeud][k].poids;
                    insertNode(tas, noeud_a_traiter, gd.indexes_tas);
                    tabRes[voisin] = numero_noeud;
                }
                else
                {
                    if ((*tas).tab[gd.indexes_tas[voisin]].poids > poids_traitement + gd.liste_voisins[numero_noeud][k].poids)
                    {
                        (*tas).tab[gd.indexes_tas[voisin]].poids = poids_traitement + gd.liste_voisins[numero_noeud][k].poids;
                        percoleHaut(tas, gd.indexes_tas, gd.indexes_tas[voisin]);
                        tabRes[voisin] = numero_noeud;
                    }
                }
            }
            ++k;
        }
        k = 0;
    }

    freetas(tas);
    return tabRes;
}

cellule_t * plus_court_chemin_djikstra(int depart, int arrivee, graphe_t graphe)
{
    cellule_t * res = NULL;
    cellule_t * cel;
    int * tabRes = djikstra(depart, graphe);
    int i=arrivee;
    int cpt = 0;
    while ((i != depart)  && cpt < graphe.nb_noeuds) //on utilise un compteur pour éviter une boucle infinie
    {
        cel = creation_bloc(i);
        adj_cel(cel, &res);
        i=tabRes[i];
        cpt++;
    }
    cel = creation_bloc(depart);
    adj_cel(cel, &res);
    return res;
}
