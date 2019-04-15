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

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::queue<const Sommet*> file ;//FILE
    std::unordered_set<const Sommet*> marque;
    const  Sommet * maill;

    file.push(this);
    marque.insert(this);
    int cpt=0;

    while (!file.empty())
    {
        maill = file.front();
        file.pop();
        for (unsigned int i=0; i<maill->m_voisins.size(); i++)
        {
            for (const auto &elem:marque)
            {
                if (maill->m_voisins[i]==elem)
                {
                    cpt=1;
                }
            }
            if (cpt==0)
            {
                file.push(maill->m_voisins[i]);
                marque.insert(maill->m_voisins[i]);
                l_pred.insert({maill->m_voisins[i]->m_id,maill->m_id});

            }

            if(cpt==1)
            {
                cpt=0;
            }
        }
    }
    return l_pred;
}
std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::stack<const Sommet*> pile ; //PILE
    const  Sommet * maill;

    pile.push(this);

    while (!pile.empty())
    {
        maill = pile.top();
        pile.pop();
        for (const auto &i: maill->m_voisins)
        {
            if((l_pred.find(i->m_id)==l_pred.end())&& (i!=this))
            {
                pile.push(i);
                //marque.insert(i);
                l_pred.insert({i->m_id,maill->m_id});

            }

        }
    }

    return l_pred;
}
std::unordered_set<std::string> Sommet::rechercherCC()
{
    std::unordered_set<std::string> cc;
    // std::unordered_map<std::string,std::string> BFS;

    auto BFS=parcoursBFS();
    cc.insert(m_id);

    for (const auto &i:BFS)
    {
        cc.insert(i.first);
    }

    return cc;
}
Sommet::~Sommet()
{
    //dtor
}
