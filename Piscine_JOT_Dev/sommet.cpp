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
std::vector<const Sommet*> Sommet::getvoisin() const
{
    return m_voisins;
}
double Sommet::getY() const
{
    return m_y;
}
int Sommet::getid() const
{
    return m_id;
}
void Sommet::dessinerSommet(Svgfile& svgout,int i)const
{
    svgout.addDisk(m_x+i*200,m_y,20,"blue");
    svgout.addText(m_x-5+i*200,m_y+5,m_id,"white");
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
