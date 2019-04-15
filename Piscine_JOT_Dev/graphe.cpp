#include <fstream>
#include <iostream>
#include "graphe.h"

graphe::graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    ///lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
    }
}

///----AFFICHAGE DU GRAPHE

void graphe::afficher(Svgfile& svgout) const
{

    std::cout<<"graphe : "<<std::endl;
    //std::cout<<"  coder l'affichage ! "<<std::endl;
    std::cout<< "odre :" <<m_sommets.size()<< std::endl;
    for(auto itr=m_sommets.begin(); itr!=m_sommets.end(); itr++)
    {
        //std::cout<<itr->first <<" " <<std::endl;
        std::cout<<"Sommet:"<<std::endl;
        itr->second->afficherData();
        itr->second->afficherVoisins();
        itr->second->dessinerSommet(svgout);

    }

}

void graphe::parcoursBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}

void graphe::afficherBFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
auto print(std::unordered_set<std::string> const &s)
{
    auto it = s.cbegin() ;
    std::cout << *it << ' ';
    return it;

}

int graphe::rechercher_afficherToutesCC() const
{
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set<std::string> cc;
    std::unordered_map<std::string,Sommet*> MesSom;
    std::unordered_set<std::string> Liste;

    MesSom=m_sommets;

    std::string id= MesSom.begin()->first;
    Sommet*s0=(m_sommets.find(id))->second;

    int i=0;
    int vartest=0;
 for(auto j: m_sommets)
    {
        for(const auto &i:cc)
            {
                Liste.insert(i);
            }
        if(Liste.find(j.first)==cc.find(j.first))
            {
                id=j.first;
                s0=(m_sommets.find(id))->second;
                cc=s0->rechercherCC();
                cc.insert(id);
            }
            else{cc.clear();}

        if(!cc.empty())
        {
            i++;
            std::cout<<"cc"<<i<<std::endl;

            for(auto itr=cc.begin(); itr!=cc.end();++itr)
                {
                    std::cout<< *itr << " ";
                }
               std::cout<<""<< std::endl;
        }
    }
    std::cout<<"recherche et affichage de toutes les composantes connexes a coder"<<std::endl;
    return i;
}
graphe::~graphe()
{
    //dtor
}
