#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "aretes.h"
#include "algorithm"


Aretes::Aretes(std::string id, std::vector<float> p ,Sommet* s1, Sommet* s2, int taille):m_id{id},m_poid{p},m_s1{s1}, m_s2{s2}, m_taille{taille}
{
}
/*bool Aretes::compaPoid(const float m1,const float m2)
{
    return m1<m2;
}*/

void Aretes::afficher()const
{
//    std::sort(m_poid.begin(),m_poid.cend(),compaPoid);
    std::cout<<" id de l'arete : "<<m_id<<std::endl;
    m_s1->afficherData();

    m_s2->afficherData();
    for(auto &itr:m_poid)
    {
        std::cout<<" poid " <<itr<<std::endl;
    }
    std::cout<<" "<<std::endl;
}

Aretes::~Aretes()
{
    //dtor
}
