#include <fstream>
#include <iostream>
#include "graphe.h"
#include "aretes.h"
#include "algorithm"


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
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille; if ( ifs.fail() )throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    std::string id_arete;
    int taille_ar;
    int taille_poid;

    float p;

    ifc>> taille_ar; if ( ifs.fail() )throw std::runtime_error("Probleme lecture taille aretes");
    ifc>> taille_poid; if (ifs.fail()) throw std::runtime_error("Probleme lecture taille poid");

    std::vector<float> poid;

    //lecture des aretes
    nbaret=taille;
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extrémités
        ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture nom arete");
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté

        ifc>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture nom arete");
        for(int j=0;j<taille_poid;j++)
        {

            ifc>>p; if(ifs.fail()) throw std::runtime_error("Probleme lecture poid 1");
            poid.push_back(p);
            //std::cout<<poid<<std::endl;
        }

        std::vector<bool> bolAr = {false};
        bolAr[i]=true;
        m_aretes.push_back({new Aretes{id_arete,poid, m_sommets.find(id)->second, m_sommets.find(id_voisin)->second, taille_poid, bolAr}});
        bolAr.clear();
        poid.clear();

    }
}

bool compaPoid(const Aretes* m1,const Aretes* m2)
{
    return m1->getpoid()<m2->getpoid();
}

void graphe::Pareto()
{
    std::vector<graphe> salut;
    std::vector<graphe> paretoo;

    graphe allgraphes={"files/sous_graphe.txt","files/sous_graphe.txt"};
    std::vector<bool> c;

    for(int i=0;i<nbaret;++i)
    {
        c.push_back(false);
    }
    std::vector<bool> allaretes=c;
    salut.push_back(allgraphes);
    ///int connex=;

    for(int i=0; i<pow(2,nbaret)-1;++i)
    {
        int nombreAr=0;
        allaretes=possibilites(allaretes);

        for(auto k : m_aretes)
        {
            for(int j=0;j<nbaret;++j)
            {
                if(k->getbolAr(j)==allaretes[j])
                {
                    allgraphes.m_aretes.push_back(k);
                    nombreAr++;
                }
            }
        }
        /*if((nombreAr==nbaret-1)&&())
        {
            salut.push_back(allgraphes);
        }*/

    }

}

void graphe::trier()
{
    std::sort(m_aretes.begin(),m_aretes.end(),compaPoid);
}


void graphe::afficher(Svgfile& svgout) const{
    for(auto itr=m_aretes.begin(); itr!=m_aretes.end();itr++)
    {
        (*itr)->afficher();
        (*itr)->dessinerArete(svgout);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end();it++)
    {
        it->second->dessinerSommet(svgout);
    }
}

std::vector<bool> graphe::possibilites(std::vector<bool> allaretes)
{
    //graphe allgraphes={"files/sous_graphe.txt","files/sous_graphe.txt"};
    if(allaretes[nbaret-1]==false)
    {
        allaretes[nbaret-1] = true;
    }
    else
    {       allaretes[nbaret-1] = false;
            int k=nbaret-1;
            do{
                if( allaretes[k-1]==true)
                {
                    allaretes[k-1]=false;
                    k--;
                }
            }while(allaretes[k-1]==true);
            allaretes[k-1]=true;
    }
    ///---comparaison entre graphe initial et nouv graphe
    for(auto i: allaretes)
    {
        std::cout<<i;
    }
std::cout<<std::endl;

    return allaretes;
}

graphe::~graphe()
{
    //dtor
}
