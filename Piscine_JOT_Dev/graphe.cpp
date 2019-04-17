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

int graphe::connex(int nbsom)
{
    int con=1;
    std::vector<Sommet*> messom;
    messom.push_back(m_aretes[0]->getsommet1());

    for(Aretes* are:m_aretes)
    {
        {
            if(std::find(messom.begin(),messom.end(),are->getsommet1())==messom.end())
            {
                messom.push_back(are->getsommet1());


            }
            if(std::find(messom.begin(),messom.end(),are->getsommet2())==messom.end())
            {
                messom.push_back(are->getsommet2());



            }
            con++;
            //}

        }
    }


    if(messom.size()==nbsom)
    {
        con=0;
        printf("E2\n");
    }
    messom.clear();

    return con;
}


float graphe::mon_poidtot(std::vector<Aretes*> Krusk,int poid)
{
    float mon_poidtot;
    for(auto j:Krusk)
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

void graphe::Pareto(Svgfile& svgout)
{
    std::vector<graphe> toutesPossi;
    std::vector<graphe> paretoo;

    graphe allgraphes= {"files/sous_graphe.txt","files/sous_graphe.txt"};
    std::vector<bool> allaretes(nbaret,false);
    std::vector<Sommet*> allsom;
    int con=0;
    int posx=0;
    int resltdij=0;


    for(int i=0; i<pow(2,nbaret)-1; ++i)
    {
        allaretes=possibilites(allaretes);
        int cas=0;
        int j= nbaret-1;
        for(Aretes* k : m_aretes)
        {
            if(allaretes[j]==1)
            {
                cas++;
                allgraphes.m_aretes.push_back(k);
            }
            if(j!=0)
            {
                j--;
            }
        }

        allgraphes.m_sommets=m_sommets;
        allgraphes.m_nbsom=m_nbsom;
        allgraphes.nbaret=cas;


        if(cas==m_nbsom-1)
        {
            con=allgraphes.connex(m_nbsom);
            if(con==0)
            {
                toutesPossi.push_back(allgraphes);
            }

        }
        allgraphes.m_aretes.clear();
        allgraphes.m_sommets.clear();
    }
    float** ma_matrice;
    toutesPossi[1].afficher(svgout,0);
    ma_matrice=graphetomatradj(toutesPossi[1]);
    for(int i=0;i<m_nbsom;i++)
    {
        resltdij+=djikstra(ma_matrice,toutesPossi[1].m_sommets.at(i)->getid());
    }

}

void graphe::trier()
{
    std::sort(m_aretes.begin(),m_aretes.end(),compaPoid);
}


void graphe::afficher(Svgfile& svgout,int posx) const
{
    for(auto itr=m_aretes.begin(); itr!=m_aretes.end(); itr++)
    {
        (*itr)->afficher();
        (*itr)->dessinerArete(svgout,"black",posx,0);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,posx,0);
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
    {
        allaretes[nbaret-1] = false;
        int k=nbaret-1;
        do
        {
            if( allaretes[k-1]==true)
            {
                allaretes[k-1]=false;
                k--;
            }
        }
        while(allaretes[k-1]==true);
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
        //std::cout<<it->getsommet1()->getid()<<" "<<it->getsommet2()->getid()<<" "<<ma_matrice[idso1][idso2]<<std::endl;
    }

    /*for(int i2=0; i2<nbsommet; i2++)
    {
        for(int j2=0; j2<nbsommet; j2++)
        {
            std::cout<<ma_matrice[i2][j2]<<std::endl;
        }
    }*/
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
            std::cout<<result<<std::endl;

        return result;
}


        graphe::~graphe()
        {
            //dtor
        }
