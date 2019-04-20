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
#define INFINI 1000.0

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
        m_aretes.push_back({new Aretes{id_arete,poid, m_sommets.find(id)->second, m_sommets.find(id_voisin)->second, taille_poid, bolAr,0}});

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

//void affpareto(std::vector<graphe> dom, std::vector<graphe> nodom,std::vector<float> mespoids, Svgfile& svgout)
//{
//    std::sort(mespoids.begin(),mespoids.end(),compaPoid1Graph);
//    svgout.addLine(10,10,10,mespoids[0]*15, "black");
//    svgout.addLine(-dom[0].getpoid(1)+mespoids[mespoids.size()-1],mespoids[0]*15,800,mespoids[0]*15,"black");
//    //svgout.addGrid();
//
//
//    for(graphe mg:dom)
//    {
//        svgout.addDisk((mg.getpoid(0)-dom[0].getpoid(0)+2)*15,(-mg.getpoid(1)+mespoids[mespoids.size()-1]+1)*15,5,"green");
//    }
//    for(graphe mf:nodom)
//    {
//        svgout.addDisk((mf.getpoid(0)-dom[0].getpoid(0)+2)*15,(-mf.getpoid(1)+mespoids[mespoids.size()-1]+1)*15,5,"red");
//    }
//}



void affpareto(std::vector<graphe> dom,std::vector<float> mespoids, Svgfile& svgout)
{
    std::sort(mespoids.begin(),mespoids.end(),compaPoid1Graph);
    svgout.addLine(10,10,10,mespoids[0]*15, "black");
    svgout.addLine(-dom[0].getpoid(1)+mespoids[mespoids.size()-1],mespoids[0]*15,800,mespoids[0]*15,"black");
    //svgout.addGrid();


    for(graphe mg:dom)
    {
        svgout.addDisk((mg.getpoid(0)-dom[0].getpoid(0)+2)*15,(-mg.getpoid(1)+mespoids[mespoids.size()-1]+1)*15,5,"green");
    }
}

//
//std::vector<graphe> FrontPareto(std::vector<graphe> possi, Svgfile& svgout)
//{
//    //std::vector<graphe> entredeux;
//    std::vector<graphe> domine;
//    std::vector<graphe> nndomine;
//    std::vector<float> mespoid;
//    int j=0;
//    float mon_yref=0;
//    std::sort(possi.begin(),possi.end(),std::bind(compaPoid0Graph, std::placeholders::_1, std::placeholders::_2, 0));
//    domine.push_back(possi[0]);
//    float yref=domine[0].getpoid(1);
//    for(graphe mesGr:possi)
//    {
//        mespoid.push_back(mesGr.getpoid(1));
//        if((mesGr.getpoid(1)<yref)&&(mesGr.getpoid(0)==domine[domine.size()-1].getpoid(0)))
//        {
//            domine.pop_back();
//            mesGr.getcoul()= {0,255,0};
//            nndomine.push_back(domine[domine.size()]);
//            domine.push_back(mesGr);
//            yref=mesGr.getpoid(1);
//            //j++;
//        }
//        else if(mesGr.getpoid(1)<yref)
//        {
//            mesGr.getcoul()= {0,255,0};
//            domine.push_back(mesGr);
//            yref=mesGr.getpoid(1);
//            //j++;
//        }
//        else
//        {
//            mesGr.getcoul()= {255,0,0};
//            if(mesGr.getpoid(1)!=yref)
//                nndomine.push_back(mesGr);
//        }
//    }
//    affpareto(domine,nndomine,mespoid,svgout);
//    return domine;
//
//}



float graphe::FrontPareto(std::vector<graphe> possi, Svgfile& svgout)
{
    //std::vector<graphe> entredeux;
    std::vector<graphe> domine;
    std::vector<graphe> nndomine;
    std::vector<float> mespoid;
    int j=0;
    std::sort(possi.begin(),possi.end(),std::bind(compaPoid0Graph, std::placeholders::_1, std::placeholders::_2, 0));
    float** ma_matrice;
    ma_matrice=graphetomatradj(possi[0]);
    possi[0].setpoiddij(djikstra(ma_matrice,INFINI));
    domine.push_back(possi[0]);
    float yref=domine[0].getpoid(1);
    float dij_maillon=0;
   for(graphe mesGr:possi)
    {
        ma_matrice=graphetomatradj(mesGr);
        dij_maillon=djikstra(ma_matrice,yref);
       if(dij_maillon<yref)
        {
            mesGr.setpoiddij(dij_maillon);
            domine.push_back(mesGr);
            yref=dij_maillon;
            mespoid.push_back(mesGr.getpoid(1));
            std::cout<<mesGr.getpoid(1)<<std::endl;


        }
    }
        std::cout<<domine.size()<<std::endl;


    affpareto(domine,mespoid,svgout);
    return yref;
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
    for(int i=0; i<ordre; i++)
    {
        tab_connexe[i]=i;
    }
    for(auto &mon_arete:m_aretes)
    {
        val_s1=mon_arete->getsommet1()->getid();
        val_s2=mon_arete->getsommet2()->getid();
        val_prede=tab_connexe[val_s2];
        tab_connexe[val_s2]=tab_connexe[val_s1];
        for(int j=0; j<ordre; j++)
        {
            if(tab_connexe[j]==val_prede)
            {
                tab_connexe[j]=tab_connexe[val_s1];
            }
        }
    }
    for(int i=0; i<ordre-1; i++)
    {
        if(tab_connexe[i]!=tab_connexe[i+1])
        {
            connexe=1;
        }
    }
    return connexe;
}


void graphe::Pareto(Svgfile &svgout,int dij)
{
    std::vector<std::vector<bool>> graphepossibles;
    std::vector<bool> last;
    int nombreAr=0;
    int ordre=m_sommets.size();
    std::vector<graphe> toutesPossi;
    std::vector<graphe>mes_dijkstra;
    graphe allgraphes= {"files/sous_graphe.txt","files/sous_graphe.txt"};
    std::vector<bool> allaretes;
    float** ma_matrice;
    int resltdij=0;
    for (int i=0; i<nbaret; ++i)
    {
        if (i<ordre-1)
        {
            allaretes.push_back(true);
        }
        else
            allaretes.push_back(false);
    }
    for(int h=ordre-1; h<nbaret; ++h)
    {
        allaretes[0]=1;
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

            if(dij==0)
            {
                if(cas==m_nbsom-1)
                {
                    con=allgraphes.Connexite();

                    if(con==0)
                    {
                        for(int i=0; i<m_nbpoid; i++)
                        {
                            allgraphes.setvectpoid(mon_poidtot(allgraphes.m_aretes, i));
                        }
                        toutesPossi.push_back(allgraphes);
                    }
                }
            }
            if(dij==1)
            {
                if(cas>=m_nbsom-1)
                {
                    con=allgraphes.Connexite();

                    if(con==0)
                    {
                        for(int i=0; i<m_nbpoid; i++)
                        {
                            allgraphes.setvectpoid(mon_poidtot(allgraphes.m_aretes, i));
                        }

                        toutesPossi.push_back(allgraphes);
                    }
                }
            }

            allgraphes.m_aretes.clear();
            allgraphes.m_sommets.clear();
            allgraphes.m_poid.clear();
        }
        while(std::next_permutation(allaretes.begin(),allaretes.end()));
    }
    for (int i=0; i<nbaret; ++i)
    {
        last.push_back(true);
    }
    int j= nbaret;
    int cas=0;
    int con;
    for(Aretes* k : m_aretes)
    {
        allaretes[j]==1;
            cas++;
            allgraphes.setar(k);

    }
    allgraphes.m_sommets=m_sommets;
    allgraphes.m_nbsom=m_nbsom;
    allgraphes.nbaret=cas;
    allgraphes.m_nbpoid=m_nbpoid;
    if(dij==1)
    {
        if(cas>=m_nbsom-1)
        {
            con=allgraphes.Connexite();

            if(con==0)
            {
                for(int i=0; i<m_nbpoid; i++)
                {
                    allgraphes.setvectpoid(mon_poidtot(allgraphes.m_aretes, i));
                }

                toutesPossi.push_back(allgraphes);
            }
        }
    }

    allgraphes.m_aretes.clear();
    allgraphes.m_sommets.clear();
    allgraphes.m_poid.clear();

    std::cout<<std::endl;
    std::cout<<"size:"<<toutesPossi.size()<<std::endl;
    FrontPareto(toutesPossi, svgout);

    /*for(int i=0;i<toutesPossi.size();i++)
    toutesPossi[i].afficher(svgout,180*i);
    std::cout<<"size paje dij:"<<mes_dijkstra.size()<<std::endl;
    for(int i=0; i<mes_dijkstra.size(); i++)
    {
        std::cout<<"p1 et dij "<<i<<" "<<mes_dijkstra[i].getpoid(0)<<"//"<<mes_dijkstra[i].getpoid(1)<<std::endl;
    }*/
}


void graphe::trier()
{
    std::sort(m_aretes.begin(),m_aretes.end(),compaPoid);
}


void graphe::afficher(Svgfile& svgout,int posx) const
{
    for(auto itr=m_aretes.begin(); itr!=m_aretes.end(); itr++)
    {
        (*itr)->dessinerArete(svgout,"black",posx,0);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,posx,0);
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

void graphe::setpoiddij(float poid)
{
    this->m_poid[1]=poid;
}
void graphe::setvectpoid(float poid)
{
    m_poid.push_back(poid);
}
float** graphe::graphetomatradj(graphe mon_graphe)
{
    float** ma_matrice;
    int nbsommet= m_sommets.size();
    ma_matrice = (float **) malloc(nbsommet*sizeof(float *));
    if (ma_matrice == NULL)
    {
        printf("espace m�moire insuffisant\n");
        exit(1);
    }
    for (int i=0; i<nbsommet; i++)
    {
        ma_matrice[i] = (float *) malloc(nbsommet*sizeof(float));
        if (ma_matrice[i] == NULL)
        {
            printf("espace m�moire insuffisant\n");
            exit(1);
        }
    }
    for (int i=0; i<nbsommet; i++)
        for(int j=0; j<nbsommet; j++)
            ma_matrice[i][j]=0;
    for(auto it : mon_graphe.getmesaret())
    {
        int idso1 =it->getsommet1()->getid();
        int idso2 =it->getsommet2()->getid();
        ma_matrice[idso1][idso2]=it->getpoidnb(1);
        ma_matrice[idso2][idso1]=it->getpoidnb(1);
    }

    return ma_matrice;
}


//float graphe::djikstra(float**matrice_adjacence)
//{
//    int *sommet_marques;
//    float *long_min;
//    int* pred;
//    int nums1,nums2,smin;
//    float minim;
//    int nb=0;
//    int nbsommet= m_sommets.size();
//    float result;
//    sommet_marques = (int *) malloc(nbsommet*sizeof(int));
//    pred = (int *) malloc(nbsommet*sizeof(int));
//    long_min = (float *) malloc(nbsommet*sizeof(float));
//    int s=0;
//    do
//    {
//        for(int i=0; i<nbsommet; i++)
//        {
//            sommet_marques[i]=0;
//            long_min[i]=INFINI;
//        }
//        long_min[s]=nb=0;
//        while(nb<nbsommet)
//        {
//            minim=INFINI;
//            for (nums1=0 ; nums1<nbsommet ; nums1++)
//            {
//                if (!sommet_marques[nums1] && long_min[nums1]<minim)
//                {
//                    smin = nums1 ;
//                    minim = long_min[nums1] ;
//                }
//            }
//            sommet_marques[smin]=1;
//            nb++;
//            for (nums2=0 ; nums2<nbsommet ; nums2++)
//            {
//                if (matrice_adjacence[smin][nums2] && !sommet_marques[nums2] &&  long_min[smin]+ matrice_adjacence[smin][nums2]<long_min[nums2])
//                {
//                    long_min[nums2] = long_min[smin] + matrice_adjacence[smin][nums2] ;
//                    pred[nums2] = smin ;
//                    result+=long_min[nums2];
//
//                }
//            }
//        }
//        s++;
//
//    }
//    while(s<nbsommet);
//    std::cout<<result<<std::endl;
//    return result;
//}





float graphe::djikstra(float** matrice_adjacence,float yref)
{
    int *sommet_marques;
    float *long_min;
    int* pred;
    int nums1,nums2,smin;
    float minim;
    int nb=0;
    int nbsommet= m_sommets.size();
    float result;
    sommet_marques = (int *) malloc(nbsommet*sizeof(int));
    pred = (int *) malloc(nbsommet*sizeof(int));
    long_min = (float *) malloc(nbsommet*sizeof(float));
    int s=0;
    do
    {
        for(int i=0; i<nbsommet; i++)
        {
            sommet_marques[i]=0;
            long_min[i]=INFINI;
        }
        long_min[s]=nb=0;
        while(nb<nbsommet)
        {
            minim=INFINI;
            for (nums1=0 ; nums1<nbsommet ; nums1++)
            {
                if (!sommet_marques[nums1] && long_min[nums1]<minim)
                {
                    smin = nums1 ;
                    minim = long_min[nums1] ;
                }
            }
            sommet_marques[smin]=1;
            nb++;
            for (nums2=0 ; nums2<nbsommet ; nums2++)
            {
                if (matrice_adjacence[smin][nums2] && !sommet_marques[nums2] &&  long_min[smin]+ matrice_adjacence[smin][nums2]<long_min[nums2])
                {
                    long_min[nums2] = long_min[smin] + matrice_adjacence[smin][nums2] ;
                    pred[nums2] = smin ;
                    result+=long_min[nums2];

                }
            }
        }
        s++;
        if (result>yref)
            break;

    }
    while(s<nbsommet);
    //std::cout<<result<<std::endl;
    return result;
}


std::vector<float> graphe::getvectpoid()const
{
    return m_poid;
}

Couleur graphe::getcoul()const
{
    return m_couleur;

}
