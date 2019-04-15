#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include "sommet.h"


int main()
{
    Svgfile svgout;
    graphe g{"files/broadway.txt"};
    g.afficher(svgout);
    return 0;
}
