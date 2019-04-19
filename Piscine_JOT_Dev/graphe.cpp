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
    int id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    int id_voisin;
    int id_arete;
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
    nbaret=taille;
    m_nbsom=ordre;
    m_nbpoid=taille_poid;
    int k=taille;
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extr�mit�s
        ifs>>id_arete;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture nom arete");
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extr�mit� � la liste des voisins de l'autre (graphe non orient�)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orient�

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

        std::vector<bool> bolAr = {nbaret -1,false};
        bolAr[k]=true;
        m_aretes.push_back({new Aretes{id_arete,poid, m_sommets.find(id)->second, m_sommets.find(id_voisin)->second, taille_poid, bolAr}});
        bolAr.clear();
        --k;
        poid.clear();

    }
}

bool compaPoid(const Aretes* m1,const Aretes* m2)
{
    return m1->getpoidnb(m1->getnbpoid())<m2->getpoidnb(m2->getnbpoid());
}


bool compaPoidGraph(const graphe m1,const graphe m2)
{
    return m1.getpoid(0)<m2.getpoid(0);
}
void affpareto(std::vector<graphe> dom, std::vector<graphe> nodom, Svgfile& svgout)
{
    svgout.addLine(10,10,10,170, "black");
    svgout.addLine(7,50,50,50,"black");
    int scale=(dom.size()+nodom.size())/2;
    svgout.addGrid();
    int d=10.5, nd=10.5, y1=100.5, y2=100.5;

    for(graphe mg:dom)
    {
        svgout.addDisk((mg.getpoid(0)+1)*5,(-mg.getpoid(1)+50)*5,1,"green");
        //d=d+20;
        //y1=y1+10;
    }
    for(graphe mf:nodom)
    {
        svgout.addDisk((mf.getpoid(0)+1)*5,(-mf.getpoid(1)+500)*5,1,"red");
        //y2=y2+10;
        //nd=nd+20;
    }
}
void FrontPareto(std::vector<graphe> possi, Svgfile& svgout)
{
    std::vector<graphe> domine;
    std::vector<graphe> nndomine;
    std::sort(possi.begin(),possi.end(),compaPoidGraph);
    float yref=4000;
      for(graphe mesGr:possi)
        {
            if(mesGr.getpoid(1)<yref)
            {
                domine.push_back(mesGr);
                yref=mesGr.getpoid(1);
            }
            else
            {
                nndomine.push_back(mesGr);
            }
    }
    for(graphe d:domine)
    {
        d.getcoul()={0,255,0};
    }
    for(graphe nd:nndomine)
    {
        nd.getcoul()={255,0,0};
    }
    affpareto(domine,nndomine,svgout);

}
float graphe::mon_poidtot(std::vector<Aretes*> Krusk,int poid)
{
    float mon_poidtot=0.0;
    for(Aretes* j:Krusk)
    {
        mon_poidtot+=j->getpoidnb(poid);
    }
    return mon_poidtot;
}

std::vector<Aretes*> graphe::kruskal (Svgfile& svgout,int p)
{
    std::vector<Aretes*> Arbre;
    int *connexe;
    int poidarbre;
    int indiceA=0,indiceG=0;
    int x,s1,s2;
    int nbsommet= m_sommets.size();
    int n= m_aretes.size();
    Aretes* u ;
    connexe= ( int*)malloc(nbsommet* sizeof( int));
    for(x=0; x<nbsommet; x++)
    {
        connexe[x]=x;
    }

    std::sort(m_aretes.begin(),m_aretes.end(),compaPoid);
    for(auto &j: m_aretes)
    {
        j->setnbpoid(j->add());
    }
    while(indiceA<nbsommet-1 || indiceG<n)
    {
        u=m_aretes[indiceG];
        int idso1 =u->getsommet1()->getid();
        int idso2 = u->getsommet2()->getid();

        s1= connexe[idso1];
        s2= connexe[idso2];
        if(s1==s2)
        {
            indiceG++;
        }
        else
        {
            Arbre.push_back(u);
            indiceA++;
            indiceG++;
            for (x=0 ; x<nbsommet ; x++)
            {

                if (connexe[x]==s1)
                {
                    connexe[x]=s2;
                }
            }
        }
    }
    int posx;
    if(p==0)
    {
        posx=500;
    }
    else
        posx=500+p*500;
    for(auto itr=Arbre.begin(); itr!=Arbre.end(); itr++)
    {
        (*itr)->dessinerArete(svgout,"red",posx,0);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,posx,0);
    }
    auto poidstring=std::to_string(p);
    poidarbre=mon_poidtot(Arbre,p);
    auto poidtotstring=std::to_string(poidarbre);
    svgout.addText(posx+100,450,"Kruskal pour le poids ("+poidstring+"), le poids total : ("+poidtotstring+")","black");
    return Arbre;
}

int graphe::Connexite()
{
    int ordre=m_sommets.size();
    int* tab_connexe;
    tab_connexe=(int*) malloc(ordre*sizeof(int));
    int val_prede,val_s1,val_s2,k,connexe=0;
    for(int i=0;i<ordre;i++)
    {
        tab_connexe[i]=i;
    }
   for(auto &mon_arete:m_aretes)
    {
        val_s1=mon_arete->getsommet1()->getid();
        val_s2=mon_arete->getsommet2()->getid();
        val_prede=tab_connexe[val_s2];
        tab_connexe[val_s2]=tab_connexe[val_s1];
        for(int j=0;j<ordre;j++)
        {
            if(tab_connexe[j]==val_prede)
            {
                tab_connexe[j]=tab_connexe[val_s1];
            }
        }
    }
    for(int i=0;i<ordre-1;i++)
    {
        if(tab_connexe[i]!=tab_connexe[i+1])
        {
            connexe=1;
        }
    }
    return connexe;
}


void graphe::Pareto(Svgfile &svgout)
{
    std::vector<std::vector<bool>> graphepossibles;
    int nombreAr=0;
    int ordre=m_sommets.size();
    std::vector<graphe> toutesPossi;
    std::vector<graphe> toutesPossiconnexe;
    graphe allgraphes= {"files/sous_graphe.txt","files/sous_graphe.txt"};
    ///std::vector<bool> c;
    std::vector<bool> allaretes;
    for(int i=0;i<nbaret;i++)
    {
        allaretes.push_back(false);
    }
        /*for (int i=0; i<nbaret; ++i)
        {
            if (i<ordre-1)
            {
                allaretes.push_back(true);
            }
            else
                allaretes.push_back(false);
        }*/
        for(int h=nbaret;h>-1;h--)
        {
            allaretes[h]=1;

        std::sort(allaretes.begin(),allaretes.end());
        do
        {
            for(int i=0;i<nbaret;++i)
            {
                std::cout<<allaretes[i];
            }
            std::cout<<std::endl;
            std::vector<graphe> paretoo;
            std::vector<Sommet*> allsom;
            int con;
            int cas=0;
            int j= nbaret-1;
            for(Aretes* k : m_aretes)
            {
                if(allaretes[j]==1)
                {
                    cas++;
                    allgraphes.setar(k);
                }
                if(j!=0)
                {
                    j--;
                }
            }

            allgraphes.m_sommets=m_sommets;
            allgraphes.m_nbsom=m_nbsom;
            allgraphes.nbaret=cas;
            allgraphes.m_nbpoid=m_nbpoid;


            if(cas>=m_nbsom-1)
            {
                //printf("test\n");
                con=allgraphes.Connexite();

                if(con==0)
                {
                    for(int i=0;i<m_nbpoid;i++)
                    {
                        allgraphes.setvectpoid(mon_poidtot(allgraphes.m_aretes, i));
                    }

                    toutesPossi.push_back(allgraphes);
                }

            }
            //toutesPossi.push_back(allgraphes);
            allgraphes.m_aretes.clear();
            allgraphes.m_sommets.clear();
            allgraphes.m_poid.clear();
        }
        while(std::next_permutation(allaretes.begin(),allaretes.end()));
        }
    std::cout<<std::endl;
    std::cout<<"size:"<<toutesPossi.size()<<std::endl;
    FrontPareto(toutesPossi, svgout);
    //toutesPossi[1].afficher(svgout);

}


void graphe::trier()
{
    std::sort(m_aretes.begin(),m_aretes.end(),compaPoid);
}


void graphe::afficher(Svgfile& svgout) const
{
    for(auto itr=m_aretes.begin(); itr!=m_aretes.end(); itr++)
    {
        //(*itr)->afficher();
        (*itr)->dessinerArete(svgout,"black",0,0);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,0,0);
    }
}

void graphe::setar(Aretes* unearete)
{
    m_aretes.push_back(unearete);
}
int graphe::getnbpoid()const
{
    return m_nbpoid;
}
float graphe::getpoid(int i) const
{
    return m_poid[i];
}

void graphe::setvectpoid(float poid)
{
    m_poid.push_back(poid);
}

std::vector<float> graphe::getvectpoid()const
{
    return m_poid;
}

Couleur graphe::getcoul()const
{
    return m_couleur;
}
