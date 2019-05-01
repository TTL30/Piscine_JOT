#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "aretes.h"
#include "algorithm"
#include <string>

/**
 * \file      aretes.cpp
 * \author    Jade/Oscar/Tiago
 * \version   1.0
 * \brief     fonctions classe arete.
 * \details   initialisation du constructeur, affichage, dessin.
 */


/**
* \brief    Constructeur d'arete
* \param    id        id de l'arete.
* \param    p         vecteur de de poids reels.
* \param    S1         S1 sommet de depart.
* \param    S2         S2 sommet d'arrivé.
* \param    taille     nombre de poid.
* \param    bolAr      vecteur booleen de nbaret-1.
* \param    tp         inutile.
*/
Aretes::Aretes(int id, std::vector<float> p,Sommet* s1, Sommet* s2, int taille, std::vector<bool> bolAr,int tp):m_id{id},m_poid{p},m_s1{s1}, m_s2{s2}, m_taille{taille},m_bolAr{bolAr},m_nbpoid{tp}
{
}
/**
* \brief    affichage donnée d'arete en console
*/
void Aretes::afficher()const
{
    std::cout<<" id de l'arete : "<<m_id<<std::endl;
    m_s1->afficherData();

    m_s2->afficherData();
    for(auto &itr:m_poid)
    {
        std::cout<<" poid " <<itr<<std::endl;
    }
    std::cout<<" "<<std::endl;
}

/**
* \brief    Dessin arete sur le svg
* \param    svgout         feuille svg de dessin.
* \param    m_couleur      inutile.
* \param    posxinit      position en x en fonction du graphe que l'on affiche.
* \param    posyinit      position en y en fonction du graphe que l'on affiche.
*/
void Aretes::dessinerArete(Svgfile& svgout,std::string m_couleur,int posxinit,int posyinit)const
{

    std::string textpoid;
    for(int i=0; i<gettaille(); i++)
    {
        int  poid1 = static_cast<int>(getpoidnb(i));
        auto lepoid1=std::to_string(poid1);
        textpoid.append(lepoid1);
        if((i-gettaille())!=-1)
        {
            textpoid.append(";");
        }
    }
    svgout.addRoute(m_s1->getX()+posxinit,m_s1->getY()+posyinit,m_s2->getX()+posxinit,m_s2->getY()+posyinit,20,"grey");
    svgout.addRoute(m_s1->getX()+posxinit,m_s1->getY()+posyinit,m_s2->getX()+posxinit,m_s2->getY()+posyinit,1,"white");

}

/**
* \brief    destructeur d'arete
*/
Aretes::~Aretes()
{
    //dtor
}

/**
* \brief    getteur d'id d'arete
 * \return  l'id de l'arete.
*/
int Aretes::getid()
{
    return m_id;
}
