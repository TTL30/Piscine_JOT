#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include "sommet.h"


int main()
{
    // debut
    Svgfile svgout;
    graphe g{"files/manhattan.txt","files/cubetown_weights_0.txt"};
    g.afficher(svgout);
    return 0;
}
