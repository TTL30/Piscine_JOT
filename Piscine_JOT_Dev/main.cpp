#include <iostream>
#include "graphe.h"
/**
 * \file      main.c
 * \author    Jade/Oscar/Tiago
 * \version   1.0
 * \brief     Menu du projet.
 * \details   initialisation des fichiers que l'on etudie, menu avec choix du fichier puis choix de l'action que l'on veut realiser.
 */
int main()
{
    int choix=0;
    int lepoid=0;
    int chx=0;
    graphe g1{"files/broadway.txt","files/broadway_weights_3.txt"};
    graphe g2{"files/cubetown.txt","files/cubetown_weights_1.txt"};
    graphe g3{"files/triville.txt","files/triville_weights_0.txt"};
    graphe g4{"files/manhattan.txt","files/manhattan_weights_1.txt"};
    graphe g{"files/sous_graphe.txt","files/sous_graphe.txt"};
    do
    {
        std::cout<<"------Bienvenue dans votre generateur------"<<std::endl;
        std::cout<<"--------------Faites un choix--------------"<<std::endl<<std::endl;
        std::cout<<" Sur quel fichier voulez vous travailler? "<<std::endl;
        std::cout<<"1. Broadway   2. Cubetown   3. Triville   4.Manhattan"<<std::endl;
        do
        {
            std::cin>>chx;
        }while((chx<=0)||(chx>4));
        std::cout<<std::endl;

        switch(chx)
        {
        case 1:
            {
                g=g1;
            break;
            }

        case 2:
            {
                 g=g2;
            break;
            }

        case 3:
            {
                 g=g3;
            break;
            }

        case 4:
            {
                g=g4;
            break;
            }

        }
        std::cout<<"0.Quitter"<<std::endl;
        std::cout<<"1.Generer des arbre de poids couvrants minimun"<<std::endl;
        std::cout<<"2.Generer une frontiere de pareto"<<std::endl;
        std::cout<<"3.Generer une frontiere de pareto avec dijkstra"<<std::endl;
        std::cout<<"Votre choix:"<<std::endl;
        do
        {
            std::cin>>choix;
        }while((choix<0)||(choix>3));

        std::cout<<std::endl;
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
            g.Pareto(svgout,0,1, chx);
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
            g.Pareto(svgout,1,lepoid, chx);
            break;
        }
        }
    }
    while(choix!=0);
    return 0;
}
