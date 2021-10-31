#include "Aetoile.h"

int distance_euclidienne(int a, int b, int colonnes)
{
    int ia;
    int ja;
    int ib;
    int jb;
    int res;
    conversion_graphe_coordonneees_tab(a, colonnes, &ia, &ja);
    conversion_graphe_coordonneees_tab(b, colonnes, &ib, &jb);
    double vectx = (double) (ja-jb);
    double vecty = (double) (ia-ib);
    res = (int) (sqrt((vectx*vectx)+(vecty*vecty))*1000.0);
    return res;
}

int * Aetoile(int depart, int arrivee,  graphe_t graphe, int colonnes)
{
    int * tabRes;
    int numero_noeud;
    int voisin;
    int distance;
    int poids_traitement;
    noeud_t noeud_en_traitement;
    int nbTraites = 0;
    int k = 0;
    int fin =0;
    int nb_noeuds = graphe.nb_noeuds;
    tas_t * tas = createtas(graphe.nb_noeuds);
    tabRes = malloc(sizeof(int)*nb_noeuds);
    graphe_djikstra_t gd = converti_graphe(graphe);
    noeud_t noeud_a_traiter = {depart, 0};
    insertNode(tas, noeud_a_traiter, gd.indexes_tas);
    
    while ((nbTraites<nb_noeuds) && (!fin))
    {
        //printf("oui\n");
        noeud_en_traitement = popTas(tas, gd.indexes_tas);
        numero_noeud = noeud_en_traitement.noeud;
        poids_traitement = (*tas).tab[gd.indexes_tas[numero_noeud]].poids;
        gd.indexes_tas[numero_noeud] = -2;
        ++nbTraites;
        //printf("oui3 %d\n", gd.liste_voisins[0][0].noeud);
        if (numero_noeud == arrivee)
        {
            fin = 1;
        }
        while ((k<4) && (((gd.liste_voisins)[numero_noeud][k]).noeud != -1) )
        {
            //printf("oui3 %d\n", numero_noeud);
            voisin = gd.liste_voisins[numero_noeud][k].noeud;
            distance = distance_euclidienne(voisin, arrivee, colonnes);
            if (gd.indexes_tas[voisin] != -2 )
            {
                if (gd.indexes_tas[voisin] == -1)
                {
                    
                    noeud_a_traiter.noeud = voisin;
                    noeud_a_traiter.poids = poids_traitement + distance;
                    insertNode(tas, noeud_a_traiter, gd.indexes_tas);
                    tabRes[voisin] = numero_noeud;
                }
                else
                {
                    if ((*tas).tab[gd.indexes_tas[voisin]].poids > poids_traitement + gd.liste_voisins[numero_noeud][k].poids)
                    {
                        (*tas).tab[gd.indexes_tas[voisin]].poids = poids_traitement + distance;
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

cellule_t * plus_court_chemin_aetoile(int depart, int arrivee, graphe_t graphe, int colonnes)
{
    cellule_t * res = NULL;
    cellule_t * cel;
    int * tabRes = Aetoile(depart,arrivee, graphe, colonnes);
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