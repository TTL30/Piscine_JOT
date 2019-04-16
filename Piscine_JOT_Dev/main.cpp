#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    Svgfile svgout;
    graphe g{"files/manhattan.txt","files/manhattan_weights_0.txt"};
    for(int i=0;i< g.get_aret()->get_taillep();++i)
    {
        std::cout<< "AUTRE KRUSTAL AVEC POID  :  " << i << std::endl;
        g.Krusk();
        g.afficher(svgout);


    }

    return 0;
}
