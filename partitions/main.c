#include <stdio.h>
#include "partition_marqueurs.h"
#include "partition_arborescence.h"
#include "liste_chainee.h"
#include "implementation_graphviz.h"


int main()
{
    /*
    partition_marqueurs_t * pm;

    pm = creer_pm(11);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 0,1);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 3,2);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 5, 6);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 6,7);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 6,8);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 3,10);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 5,4);
    printTab((*pm).tab, (*pm).size);
    fusion_pm(pm, 7,9);
    printTab((*pm).tab, (*pm).size);
    lister_classe_pm(pm,3);
    lister_partition(pm);
    libere_pm(pm);
    */
    partition_arborescence_t * pa;

    pa = creer_pa(11);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 0,1);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 2,3);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 10, 3);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 5,9);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 4,6);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 8,7);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 7,9);
    //printTab((*pa).tab, (*pa).size);
    fusion_pa(pa, 6,8);
    //printTab((*pa).tab, (*pa).size);
    //printTab((*pa).hauteur, (*pa).size);
    //lister_classe_pa(pa, 0);
    //lister_classe_pa(pa,3);
    lister_partition_pa(pa);
    lister_graph(pa);
    libere_pa(pa);
}