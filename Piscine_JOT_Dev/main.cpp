#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    int choix=0;
    graphe g{"files/manhattan.txt","files/manhattan_weights_0.txt"};


    do
    {
        std::cout<<"------Bienvenue dans votre generateur------"<<std::endl;
        std::cout<<"--------------Faites un choix--------------"<<std::endl<<std::endl;
        std::cout<<"0.Quitter"<<std::endl;
        std::cout<<"1.Generer des arbre de poids couvrants minimun"<<std::endl;
        std::cout<<"2.Generer une frontiere de pareto"<<std::endl;
        std::cout<<"3.Generer une frontiere de pareto avec dijkstra"<<std::endl;
        std::cout<<"Votre choix:"<<std::endl;
        std::cin>>choix;
        switch(choix)
        {
        case 0:
        {
            return 0;
            break;
        }

        case 1:
        {
            Svgfile svgout;
            for(int i=0; i< g.get_aret()->gettaille(); ++i)
            {
                std::cout<< "AUTRE KRUSTAL AVEC POID  :  " << i << std::endl;
                g.kruskal(svgout,i);
                g.afficher(svgout,i);
            }
            break;
        }
        case 2:
        {
            Svgfile svgout;
            g.Pareto(svgout,0);
            break;
        }
        case 3:
        {
            Svgfile svgout;
            g.Pareto(svgout,1);
            break;
        }
        }
    }
    while(choix!=0);
    return 0;
}
