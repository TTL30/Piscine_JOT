#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "aretes.h"
#include "algorithm"


Aretes::Aretes(std::string id, std::vector<float> p ,Sommet* s1, Sommet* s2, int taille, int tp):m_id{id},m_poid{p},m_s1{s1}, m_s2{s2}, m_taille{taille}, m_nbpoid{tp}
{
}
/*bool Aretes::compaPoid(const float m1,const float m2)
{
    return m1<m2;
}*/


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

void Aretes::dessinerArete(Svgfile& svgout,std::string m_couleur,int posxinit,int posyinit)const
{
    int  poid1 = static_cast<int>(getpoid(0));
    int  poid2 = static_cast<int>(getpoid(1));
    auto lepoid1=std::to_string(poid1);
    auto lepoid2=std::to_string(poid2);
    if(m_s1->getX()==m_s2->getX())
    {
    svgout.addText(m_s1->getX()+posxinit,posyinit+(m_s1->getY()+m_s2->getY())/2,"("+lepoid1+");("+lepoid2+")",m_couleur);
    }
    if(m_s1->getY()==m_s2->getY())
    {
    svgout.addText(-20+posxinit+(m_s1->getX()+m_s2->getX())/2,-5+m_s1->getY()+posyinit,"("+lepoid1+");("+lepoid2+")",m_couleur);
    }
    svgout.addLine(m_s1->getX()+posxinit,m_s1->getY()+posyinit,m_s2->getX()+posxinit,m_s2->getY()+posyinit,m_couleur);

}

Aretes::~Aretes()
{
    //dtor
}
