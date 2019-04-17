#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    Svgfile svgout;
    graphe g{"files/cubetown.txt","files/cubetown_weights_0.txt"};
    //g.trier();
    //g.afficher(svgout);
    g.Pareto(svgout);
    return 0;
}
