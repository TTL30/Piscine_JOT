#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"
#include "svgfile.h"

Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
Sommet::Sommet()
{
}
void Sommet::ajouterVoisin(const Sommet* voisin)
{
    m_voisins.push_back(voisin);
}
void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}
int Sommet::getX() const
{
    return m_x;
}

void Sommet::dessinerSommet(Svgfile& svgout, int posinitx,int posinity)const
{
    svgout.addRectangle(m_x+posinitx-20,m_y+posinity-20,40,40,"#D37460");
    svgout.addText(m_x-5+posinitx,m_y+5+posinity,m_id,"white");
}
std::vector<const Sommet*> Sommet::getvoisin() const
{
    return m_voisins;
}
int Sommet::getY() const
{
    return m_y;
}
int Sommet::getid() const
{
    return m_id;
}


void Sommet::afficherVoisins() const
{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}



Sommet::~Sommet()
{
    //dtor
}
