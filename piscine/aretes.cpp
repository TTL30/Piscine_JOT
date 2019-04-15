#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "aretes.h"

Aretes::Aretes(std::string id, float* p ,Sommet* s1, Sommet* s2):m_id{id},m_poid{p},m_s1{s1}, m_s2{s2}
{
}

/*void Aretes::afficher()const
{
    std::cout<<" "<<m_id<<" , ";
    m_s1->afficherData();
    std::cout<<" ";
    m_s2->afficherData();
    for(int i;i<m_taille; ++i)
    {
        std::cout<<" , " <<m_poid[i]<<std::endl;
    }
}*/

Aretes::~Aretes()
{
    //dtor
}
