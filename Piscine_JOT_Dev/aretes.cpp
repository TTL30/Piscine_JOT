#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "aretes.h"
#include "algorithm"


Aretes::Aretes(int id, std::vector<float> p ,Sommet* s1, Sommet* s2, int taille, std::vector<bool> bolAr):m_id{id},m_poid{p},m_s1{s1}, m_s2{s2}, m_taille{taille},m_bolAr{bolAr}
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

void Aretes::dessinerArete(Svgfile& svgout,int x)const
{
    svgout.addLine(m_s1->getX()+500*x,m_s1->getY(),m_s2->getX()+500*x,m_s2->getY(),"black");
}

Aretes::~Aretes()
{
    //dtor
}

int Aretes::getid()
{
    return m_id;
}
