#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    Svgfile svgout;
    graphe g{"files/manhattan.txt","files/cubetown_weights_0.txt"};
    g.trier();
    g.afficher(svgout);
    return 0;
}
