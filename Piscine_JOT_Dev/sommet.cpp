#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"
#include "svgfile.h"
/**
 * \brief    constructeur de sommet
  * \param    id    id du sommet.
  * \param    x    posx du sommet.
  * \param    y    posy du sommet.
 */
Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
/**
 * \brief    constructeur de sommet avide
 */
Sommet::Sommet()
{
}
/**
 * \brief    ajout voisin du sommet
  * \param    voisin    voisin du sommet.
 */
void Sommet::ajouterVoisin(const Sommet* voisin)
{
    m_voisins.push_back(voisin);
}
/**
 * \brief    affichage données du sommet en console
 */
void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}
/**
 * \brief    getteur posx sommet
 * \return    posx du sommet
 */
int Sommet::getX() const
{
    return m_x;
}
/**
 * \brief    dessin du sommet
 * \param    svgout    feuille de dessin.
 * \param    posinitx   posinitiale en x du graphe.
 * \param    posinity   posinitiale en y du graphe.
 */
void Sommet::dessinerSommet(Svgfile& svgout, int posinitx,int posinity)const
{
    svgout.addRectangle(m_x+posinitx-20,m_y+posinity-20,40,40,"#D37460");
    svgout.addText(m_x-5+posinitx,m_y+5+posinity,m_id,"white");
}
/**
 * \brief    getteur des voisins du sommet
 * \return   vecteur de voisin du sommet
 */
std::vector<const Sommet*> Sommet::getvoisin() const
{
    return m_voisins;
}
/**
 * \brief    getteur posy sommet
 * \return    posy du sommet
 */
int Sommet::getY() const
{
    return m_y;
}
/**
 * \brief    getteur id sommet
 * \return    id du sommet
 */
int Sommet::getid() const
{
    return m_id;
}

/**
 * \brief    affichage données voisins du sommet en console
 */
void Sommet::afficherVoisins() const
{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}

/**
 * \brief    destructeur sommet
 */
Sommet::~Sommet()
{
    //dtor
}
