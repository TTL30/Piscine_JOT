#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"
#include "svgfile.h"

Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
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
double Sommet::getX() const
{
    return m_x;
}
double Sommet::getY() const
{
    return m_y;
}
void Sommet::dessinerSommet(Svgfile& svgout)const
{
    svgout.addDisk(m_x,m_y,20,"blue");
    svgout.addText(m_x-5,m_y+5,m_id,"white");
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
