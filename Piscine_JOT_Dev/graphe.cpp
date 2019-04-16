#include <fstream>
#include <iostream>
#include "graphe.h"
#include "aretes.h"
#include "algorithm"
#include <sstream>
#include <string>


graphe::graphe(std::string nomFichier, std::string nomFichier2)
{
    std::ifstream ifs{nomFichier};
    std::ifstream ifc{nomFichier2};
    ///-----OUVERTURE DES FICHIERS
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier ); // du graphe
    if (!ifc)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier ); // des poids
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    std::string id_arete;
    int taille_ar;
    int taille_poid;

    float p;

    ifc>> taille_ar;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille aretes");
    ifc>> taille_poid;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille poid");

    std::vector<float> poid;

    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
        ifs>>id_arete;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture nom arete");
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté

        ifc>>id_arete;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture nom arete");
        for(int j=0; j<taille_poid; j++)
        {

            ifc>>p;
            if(ifs.fail())
                throw std::runtime_error("Probleme lecture poid 1");
            poid.push_back(p);
            //std::cout<<poid<<std::endl;
        }
        // Aretes* ess ={id_arete,poid, m_sommets.find(id)->second, m_sommets.find(id_voisin)->second};
        m_aretes.push_back({new Aretes{id_arete,poid, m_sommets.find(id)->second, m_sommets.find(id_voisin)->second, taille_poid, 0}});
        poid.clear();
    }
}

bool compaPoid(const Aretes* m1,const Aretes* m2)
{
    return m1->getpoid(m1->getnbpoid())<m2->getpoid(m2->getnbpoid());
}



void graphe::afficherDFS(std::string id) const
{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
struct Sous_sommet
{
    int parent_sommet;
    int rang_sommet;
};
int recherche_connexe(Sous_sommet mes_SousSommet[], int i)
{
  if (mes_SousSommet[i].parent_sommet != i)
        mes_SousSommet[i].parent_sommet = recherche_connexe(mes_SousSommet, mes_SousSommet[i].parent_sommet);

    return mes_SousSommet[i].parent_sommet;
}
void Connexite(Sous_sommet mesSousSommet[], int x, int y)
{
    int xroot = recherche_connexe(mesSousSommet, x);
    int yroot = recherche_connexe(mesSousSommet, y);


    if (mesSousSommet[xroot].rang_sommet < mesSousSommet[yroot].rang_sommet)
        mesSousSommet[xroot].parent_sommet = yroot;
    else if (mesSousSommet[xroot].rang_sommet > mesSousSommet[yroot].rang_sommet)
        mesSousSommet[yroot].parent_sommet = xroot;

    else
    {
        mesSousSommet[yroot].parent_sommet = xroot;
        mesSousSommet[xroot].rang_sommet++;
    }
}
void graphe::Krusk(Svgfile& svgout,int p)
{
    std::vector<Aretes*> mesAretesKrusk;
    int nbsommet= m_sommets.size();
    int nbKruskal=0;
    int i=0;
    ///trie
    std::sort(m_aretes.begin(),m_aretes.end(),compaPoid);
    for(auto &j: m_aretes)
    {
        j->setnbpoid(j->add());

    }
    ///allocation dynamique
    Sous_sommet * mes_Soussomm= (struct Sous_sommet*)malloc(nbsommet* sizeof(struct Sous_sommet));

    for(int it=0;it<nbsommet;it++)
    {
        mes_Soussomm[it].parent_sommet=it;
        mes_Soussomm[it].rang_sommet=0;
    }
    while(nbKruskal < nbsommet-1)
    {
        Aretes* maillon_Arete = m_aretes[i++] ;
        int idso1 = std::stoi(maillon_Arete->getSommet1()->getid());
        int idso2 = std::stoi(maillon_Arete->getSommet2()->getid());

        int check_x =recherche_connexe(mes_Soussomm,idso1);
        int check_y =recherche_connexe(mes_Soussomm,idso2);
        if(check_x!=check_y)
        {
            printf("test");
            nbKruskal++;
            mesAretesKrusk.push_back(maillon_Arete);
            Connexite(mes_Soussomm, check_x,check_y);
        }
    }
    int posx=p*500;
    for(auto itr=mesAretesKrusk.begin(); itr!=mesAretesKrusk.end(); itr++)
    {
        (*itr)->dessinerArete(svgout,"red",posx,0);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,posx,0);
    }
    auto poidstring=std::to_string(p);
    svgout.addText(posx+100,450,"Kruskal pour le poids ("+poidstring+")","black");
}



void graphe::afficher(Svgfile& svgout) const
{
    for(auto itr=m_aretes.begin(); itr!=m_aretes.end(); itr++)
    {
        (*itr)->afficher();
        (*itr)->dessinerArete(svgout,"black",0,0);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,0,0);
    }

}



graphe::~graphe()
{
    //dtor
}
