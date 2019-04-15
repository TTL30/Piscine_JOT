#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include "sommet.h"


int main()
{
    Svgfile svgout;
    graphe g{"files/cubetown.txt","files/cubetown_weights_0.txt"};
    g.afficher(svgout);
    return 0;
}
