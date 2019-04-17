#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    Svgfile svgout;
    graphe g{"files/broadway.txt","files/broadway_weights_0.txt"};
    //g.trier();
    //g.afficher(svgout);
    g.Pareto();
    return 0;
}
