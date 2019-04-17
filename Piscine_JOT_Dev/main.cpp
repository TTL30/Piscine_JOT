#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    Svgfile svgout;
    graphe g{"files/triville.txt","files/triville_weights_0.txt"};
    //g.trier();
    //g.afficher(svgout);
    g.Pareto();
    return 0;
}
