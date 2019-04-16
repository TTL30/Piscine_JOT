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
int Sommet::getX() const
{
    return m_x;
}
int Sommet::getY() const
{
    return m_y;
}
void Sommet::dessinerSommet(Svgfile& svgout, int posinitx,int posinity)const
{
    svgout.addDisk(m_x+posinitx,m_y+posinity,20,"blue");
    svgout.addText(m_x-5+posinitx,m_y+5+posinity,m_id,"white");
}
void Sommet::afficherVoisins() const
{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}

std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const
{
    std::unordered_map<std::string,std::string> l_pred;//map que l'on retourne avec le parcours
    std::unordered_set<std::string> mon_set;//set de stockage des sommets deja visistés
    std::stack<const Sommet*>parc_ours;//pile
    const Sommet* act;//Sommet qui nous sert de maillon
    parc_ours.push(this);//on push dans notre pile l'element que l'utilisateur vient de taper
    for(auto v:m_voisins)
    {
        printf("oui");
        v->afficherData();
    }
    while(!parc_ours.empty())//parcours de la pile
    {
        act= parc_ours.top();//on se place sur le premier element de la pile et on le sauvegarde avec noytre maillon
        parc_ours.pop();//on retire le premier element
        for (const auto &it:act->m_voisins)//parcours des voisins
        {
            if((mon_set.find(it->m_id)==mon_set.end())&& (it!=this))//condition si je n'ai pas encore visite ce voisin
            {
                parc_ours.push(it);//on push le voisin dans notre pile
                mon_set.insert({it->m_id});//et on insert dans notre set de sommet deja visités
                l_pred.insert({it->m_id,act->m_id});//on insert dans la map mon maillon et son predecesseur
            }
        }
    }
    return l_pred;
}

Sommet::~Sommet()
{
    //dtor
}
