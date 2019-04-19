#include <fstream>
#include <iostream>
#include "graphe.h"
#include "aretes.h"
#include "algorithm"
#include <sstream>
#include <string>
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


bool compaPoidGraph(const graphe m1,const graphe m2)
{
    return m1.getpoid(0)<m2.getpoid(0);
}

void affpareto(std::vector<graphe> dom, std::vector<graphe> nodom, Svgfile& svgout)
{
    svgout.addLine(10,10,10,170, "black");
    svgout.addLine(7,50,50,50,"black");
    svgout.addGrid();
    int d=10.5, nd=10.5, y1=100.5, y2=100.5;

    for(graphe mg:dom)
    {
        svgout.addDisk((mg.getpoid(0)+1)*5,(-mg.getpoid(1)+20)*5,1,"green");
        //d=d+20;
        //y1=y1+10;
    }
    for(graphe mf:nodom)
    {
        svgout.addDisk((mf.getpoid(0)+1)*5,(-mf.getpoid(1)+20)*5,1,"red");
        //y2=y2+10;
        //nd=nd+20;
    }
}

std::vector<graphe> FrontPareto(std::vector<graphe> possi, Svgfile& svgout)
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
        d.getcoul()= {0,255,0};
    }
    for(graphe nd:nndomine)
    {
        nd.getcoul()= {255,0,0};
    }
    affpareto(domine,nndomine,svgout);
    std::cout<<"size pajeto:"<<nndomine.size()<<std::endl;

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
    int nombreAr=0;
    float resltdij=0;
    int ordre=m_sommets.size();
    std::vector<graphe> toutesPossi;
    std::vector<graphe> mon_dijkstra;
    graphe allgraphes= {"files/sous_graphe.txt","files/sous_graphe.txt"};
    ///std::vector<bool> c;
    std::vector<bool> allaretes;
    float** ma_matrice;
    for(int i=0; i<nbaret; i++)
    {
        allaretes.push_back(false);
    }
    for(int h=nbaret; h>-1; h--)
    {
        allaretes[h]=1;
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
            if (dij==1)
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
                        for(int j=0; j<toutesPossi.size(); j++)
                        {
                            ma_matrice=graphetomatradj(toutesPossi[j]);
                            resltdij=0;
                            for(int i=0; i<m_nbsom; i++)
                            {
                                resltdij=djikstra(ma_matrice,toutesPossi[j].m_sommets.at(i)->getid());
                            }
                            toutesPossi[j].setpoiddij(resltdij);
                        }
                    }

                }
            }

            allgraphes.m_aretes.clear();
            allgraphes.m_sommets.clear();
            allgraphes.m_poid.clear();
        }
        while(std::next_permutation(allaretes.begin(),allaretes.end()));
    }
    std::cout<<std::endl;
    std::cout<<"size:"<<toutesPossi.size()<<std::endl;
    mon_dijkstra=FrontPareto(toutesPossi, svgout);
    int oui=5;
    mon_dijkstra[oui].afficher(svgout,0);
    std::cout<<"size dij:"<<mon_dijkstra.size()<<std::endl;
    std::cout<<"monpooiddij :"<<mon_dijkstra[oui].getpoid(1)<<std::endl;

    /*if (dij==1)
    {
        ma_matrice=graphetomatradj(mon_dijkstra[0]);
        for(int i=0; i<m_nbsom; i++)
        {
            resltdij+=djikstra(ma_matrice,toutesPossi[0].m_sommets.at(i)->getid());
        }
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
        printf("espace mémoire insuffisant\n");
        exit(1);
    }
    for (int i=0; i<nbsommet; i++)
    {
        ma_matrice[i] = (float *) malloc(nbsommet*sizeof(float));
        if (ma_matrice[i] == NULL)
        {
            printf("espace mémoire insuffisant\n");
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
float graphe::djikstra(float**matrice_adjacence,int s)
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
            }
        }
    }

    for(int j2=0; j2<nbsommet; j2++)
    {
        result+=long_min[j2];
    }

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


graphe::~graphe()
{
    //dtor
}
