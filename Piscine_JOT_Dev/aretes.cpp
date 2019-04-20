#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "aretes.h"
#include "algorithm"
#include <string>


Aretes::Aretes(int id, std::vector<float> p ,Sommet* s1, Sommet* s2, int taille, std::vector<bool> bolAr,int tp):m_id{id},m_poid{p},m_s1{s1}, m_s2{s2}, m_taille{taille},m_bolAr{bolAr},m_nbpoid{tp}
{
}

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

    /*std::string textpoid;
    for(int i=0;i<gettaille();i++)
    {
        int  poid1 = static_cast<int>(getpoidnb(i));
        auto lepoid1=std::to_string(poid1);
        textpoid.append(lepoid1);
        if((i-gettaille())!=-1)
        {
            textpoid.append(";");
        }
    }
    if(m_s1->getX()==m_s2->getX())
    {
    svgout.addText(m_s1->getX()+posxinit,posyinit+(m_s1->getY()+m_s2->getY())/2,textpoid,m_couleur);
    }
    if(m_s1->getY()==m_s2->getY())
    {
    svgout.addText(-20+posxinit+(m_s1->getX()+m_s2->getX())/2,-5+m_s1->getY()+posyinit,textpoid,m_couleur);
    }*/
    svgout.addRoute(m_s1->getX()+posxinit,m_s1->getY()+posyinit,m_s2->getX()+posxinit,m_s2->getY()+posyinit,20,"grey");
    svgout.addRoute(m_s1->getX()+posxinit,m_s1->getY()+posyinit,m_s2->getX()+posxinit,m_s2->getY()+posyinit,1,"yellow");

    }

Aretes::~Aretes()
{
    //dtor
}

int Aretes::getid()
{
    return m_id;
}
