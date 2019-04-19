#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    Svgfile svgout;
    graphe g{"files/triville.txt","files/triville_weights_0.txt"};
    g.Pareto(svgout);
    //g.afficher(svgout);
    /*for(int i=0;i< g.get_aret()->gettaille();++i)
    {
        //std::cout<< "AUTRE KRUSTAL AVEC POID  :  " << i << std::endl;
        //g.kruskal(svgout,i);
        //g.afficher(svgout);
    }*/
    return 0;
}
