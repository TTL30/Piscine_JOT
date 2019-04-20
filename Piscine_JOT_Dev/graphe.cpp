#include <fstream>
#include <iostream>
#include "graphe.h"
#include "aretes.h"
#include "algorithm"
#include "functional"
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#define Infini 10000


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
bool compaPoid1Graph(const float m1,const float m2)
{
    return m1<m2;
}

bool compaPoid0Graph(const graphe m1,const graphe m2, int i)
{
    return m1.getpoid(i)<m2.getpoid(i);
}
void affpareto(std::vector<graphe> dom, std::vector<graphe> nodom,std::vector<float> mespoids, Svgfile& svgout)
{
    std::sort(mespoids.begin(),mespoids.end(),compaPoid1Graph);
    svgout.addText(10,15, "cout 2", "black");
    svgout.addText(750,790, "cout 1", "black");
    svgout.addLine(0, 5,5,0,"black" );
    svgout.addLine(5,0,10,5,"black");
    svgout.addLine(795, 790,800,795, "black");
    svgout.addLine(800,795,795,800, "black");
    svgout.addLine(5,1,5,800, "black");
    svgout.addLine(1,795,800, 795,"black");
    int d=1, dd=1;
    //svgout.addGrid();


    for(graphe mg:dom)
    {
        svgout.addDisk((mg.getpoid(0)*7),(795-mg.getpoid(1)*(7))+mespoids[mespoids.size()-1],2.5,"green");
    }
    for(graphe mf:nodom)
    {
        svgout.addDisk((mf.getpoid(0)*7),(795-mf.getpoid(1)*(7))+mespoids[mespoids.size()-1],2.5,"red");
    }
}
void affpareto2(std::vector<graphe> dom, std::vector<graphe> nodom,std::vector<float> mespoids, Svgfile& svgout, int x, int y)
{

    if((x==0)&&(y==1))
    {
        svgout.addLine(5,0,5,266, "black");
        svgout.addLine(0, 266, 266,266, "black");
        svgout.addText(10,20, "cout2", "black");
        svgout.addText(216,256, "cout1", "black");
        svgout.addLine(0,5,5,0,"black");
        svgout.addLine(5,0,10,5,"black");
        svgout.addLine(261,261,266,266,"black");
        svgout.addLine(266,266,261,271,"black");
        for(graphe mg:dom)
        {
            svgout.addDisk((mg.getpoid(x)*7),(266-mg.getpoid(y)*(7))+mespoids[mespoids.size()-1],2,"green");
        }
    }
    else if(x==1)
    {
        svgout.addLine(266,266,266,532, "black");
        svgout.addLine(266,532, 532, 532, "black");
        svgout.addText(276,286, "cout3", "black");
        svgout.addText(480,520, "cout2", "black");
        svgout.addLine(266,266,271,271,"black");
        svgout.addLine(527,527,532,532,"black");
        svgout.addLine(532,532,527,537,"black");
        for(graphe mg:dom)
        {
            svgout.addDisk((mg.getpoid(x)*7)+266,(532-mg.getpoid(y)*(7))+mespoids[mespoids.size()-1],2,"green");
        }
    }
    else
    {
         svgout.addLine(532,532,532,795, "black");
         svgout.addLine(532,795,800,795, "black");
         svgout.addText(542,552, "cout3", "black");
         svgout.addText(750,790, "cout1", "black");
         svgout.addLine(532,532,537,537,"black");
         svgout.addLine(795, 790,800,795, "black");
         svgout.addLine(800,795,795,800, "black");
         for(graphe mg:dom)
        {
            svgout.addDisk((mg.getpoid(x)*7)+532,(798-mg.getpoid(y)*(7))+mespoids[mespoids.size()-1],2,"green");
        }
    }

}
std::vector<graphe> FrontPareto(std::vector<graphe> possi, Svgfile& svgout, int x, int y, int nbpoid, float* pmax)
{
    //std::vector<graphe> entredeux;
    std::vector<graphe> domine;
    std::vector<graphe> nndomine;
    std::vector<float> mespoid;
    std::sort(possi.begin(),possi.end(),std::bind(compaPoid0Graph, std::placeholders::_1, std::placeholders::_2, x));
    domine.push_back(possi[0]);
    float yref=domine[0].getpoid(y);
        for(graphe mesGr:possi)
        {
            mespoid.push_back(mesGr.getpoid(y));
            if((mesGr.getpoid(y)<yref)&&(mesGr.getpoid(x)==domine[domine.size()-1].getpoid(x)))
            {
                domine.pop_back();
                nndomine.push_back(domine[domine.size()]);
                domine.push_back(mesGr);
                yref=mesGr.getpoid(y);
                //j++;
            }
            else if(mesGr.getpoid(y)<yref)
            {
                domine.push_back(mesGr);
                yref=mesGr.getpoid(y);
            }
            else
            {
                if(mesGr.getpoid(y)!=yref)
                nndomine.push_back(mesGr);
            }
    }

    std::sort(mespoid.begin(),mespoid.end(),compaPoid1Graph);
    *pmax=mespoid[mespoid.size()-1];
    if(nbpoid==2)
    affpareto(domine,nndomine,mespoid,svgout);
    else if(nbpoid==3)
    {
        affpareto2(domine,nndomine,mespoid,svgout, x, y);
    }
    return domine;

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
    for (int i=0; i<nbaret; ++i)
    {
        if (i<ordre-1)
        {
            allaretes.push_back(true);
        }
        else
            allaretes.push_back(false);
    }
    std::cout<<std::endl;
    std::sort(allaretes.begin(),allaretes.end());
    do
    {
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



            con=allgraphes.Connexite();

            if(con==0)
            {
                if(cas==m_nbsom-1)
                {
                for(int i=0;i<m_nbpoid;i++)
                {
                    allgraphes.setvectpoid(mon_poidtot(allgraphes.m_aretes, i));

                }
                toutesPossi.push_back(allgraphes);
            }
            ///if(cas>=m_nbsom-1)----TIAGO


        }
        allgraphes.m_aretes.clear();
        allgraphes.m_sommets.clear();
        allgraphes.m_poid.clear();

    }
    while(std::next_permutation(allaretes.begin(),allaretes.end()));
    std::cout<<std::endl;
    std::cout<<"size:"<<toutesPossi.size()<<std::endl;
    std::vector<graphe> domine;
    std::vector<graphe> domine1;
    std::vector<graphe> domine2;
    std::vector<graphe> domine3;
    float p1max=0.0;
    float p2max=0.0;

    if(m_nbpoid==2)
        domine=FrontPareto(toutesPossi, svgout, 0, 1, m_nbpoid, &p1max);
    else if(m_nbpoid==3)
    {
        domine1=FrontPareto(toutesPossi, svgout, 0, 1, m_nbpoid, &p1max);
        domine2=FrontPareto(toutesPossi, svgout, 1, 2, m_nbpoid, &p2max);
        domine3=FrontPareto(toutesPossi, svgout, 0, 2, m_nbpoid, &p2max);
        std::cout<<"p1 : "<<p1max <<" p2 "<<p2max<<std::endl;
        for(graphe dom:domine1)
        {
            for(graphe dim:domine2)
            {
                for(graphe dam :domine3)
                {
                    if((dom.getpoid(0)==dim.getpoid(0))&&(dom.getpoid(0)==dam.getpoid(0))&&
                       (dom.getpoid(1)==dim.getpoid(1))&&(dom.getpoid(1)==dam.getpoid(1)))
                    {
                        svgout.addCircle((dom.getpoid(0)*7),(266-dom.getpoid(1)*(7))+p1max,4,1,"blue");
                        svgout.addCircle((dim.getpoid(1)*7)+266,(532-dom.getpoid(2)*(7))+p2max,4,1,"blue");
                        svgout.addCircle((dam.getpoid(0)*7)+532,(798-dom.getpoid(2)*(7))+p2max,4,1,"blue");
                    }
                }

            }


        }
    }

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
