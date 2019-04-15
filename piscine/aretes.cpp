#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "aretes.h"

Aretes::Aretes(std::string id, float* p ,Sommet* s1, Sommet* s2, int taille):m_id{id},m_poid{p},m_s1{s1}, m_s2{s2}, m_taille{taille}
{
}

void Aretes::afficher()const
{
    std::cout<<" id de l'arete : "<<m_id<<std::endl;
    m_s1->afficherData();

    m_s2->afficherData();
    std::cout<<" poid : "<< m_poid[0]<<std::endl;
    for(int i=0;i<m_taille; ++i)
    {
        std::cout<<" poid " <<i <<" : "<< *m_poid[i]<<std::endl;
    }
    std::cout<<" "<<std::endl;
}

Aretes::~Aretes()
{
    //dtor
}
