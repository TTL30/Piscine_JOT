#include <iostream>
#include "graphe.h"

int main()
{
    // debut
    int choix=0;
    int lepoid=0;
    graphe g{"files/broadway.txt","files/broadway_weights_0.txt"};
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
            g.afficher(svgout,50);
            for(int i=0; i< g.get_aret()->gettaille(); ++i)
            {
                g.kruskal(svgout,i);
            }
            break;
        }
        case 2:
        {
            Svgfile svgout;
            g.Pareto(svgout,0,1);
            break;
        }
        case 3:
        {
            do
            {
                std::cout<<"Veuillez entrer l'objectif sur lequel vous voulez realise votre algorithme de dijkstra :"<<std::endl;
                std::cin>>lepoid;
            }
            while((lepoid!=1)&&(lepoid!=2));
            Svgfile svgout;
            g.Pareto(svgout,1,lepoid);
            break;
        }
        }
    }
    while(choix!=0);
    return 0;
}
