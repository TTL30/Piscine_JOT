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


    std::queue<const Sommet *> file_sommets;
    file_sommets.push(this);
    const Sommet* sommet;

    while(!(file_sommets.empty())) //tant que la file n'est pas vide
    {

        sommet=file_sommets.front(); //On accède au prochain élément et on l'enlève de la file, on nouveau sommet servira de départ
        file_sommets.pop();

        for(const auto &it : sommet->m_voisins)
        {
            if((l_pred.find(it->m_id) == l_pred.end())  &&  (it!=this))  //Si trouve un voisin et différent de lui-même
            {
                file_sommets.push(it);  //Ajout dans la file
                l_pred.insert({it->m_id, sommet->m_id});  //Ajout dans la map du sommet voisin juste après le sommet marqué
            }

        }

    }
    return l_pred;
}

std::unordered_set<std::string> Sommet::rechercherCC() const
{
    std::unordered_set<std::string> cc;
    std::unordered_map<std::string,std::string> l_pred;

    l_pred=parcoursBFS();



    for(const auto s : l_pred)  //Parcours de la map
    {

        cc.insert(s.first);  //On l'insère dans set

    }


    return cc;
}

Sommet::~Sommet()
{
    //dtor
}
