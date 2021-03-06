#include <fstream>
#include <iostream>
#include "graphe.h"
#include "aretes.h"
#include "algorithm"
#include "functional"
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <queue>
#include <vector>
#include <functional>
#include <string>

/**  \def  valeur maximun  */
#define Infini 10000
#define INFINI 10000.0

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

/**
 * \brief       comparaison poid arete
 * \details    on compare le poids que l'on veut
 * \param    m1      arete 1
 * \param    m2      arete 2
* \return    le poid de l'arete qui a le poid inferieur.
 */
bool compaPoid(const Aretes* m1,const Aretes* m2)
{
    return m1->getpoidnb(m1->getnbpoid())<m2->getpoidnb(m2->getnbpoid());
}

/**
 * \brief       comparaison poid arete
 * \details    on compare le poids 1
 * \param    m1      arete 1
 * \param    m2      arete 2
 * \return    le poid de l'arete qui a le poid inferieur.
 */
bool compaPoidar(const Aretes* m1,const Aretes* m2)
{
    return m1->getpoidnb(1)<m2->getpoidnb(1);
}
/**
 * \brief       comparaison poid graphe
 * \param    m1      poid 1
 * \param    m2      poid 2
 * \return   le poid inferieur.
 */
bool compaPoid1Graph(const float m1,const float m2)
{
    return m1<m2;
}

/**
 * \brief       comparaison poid graphe que l'on veut
 * \param    m1      poid 1
 * \param    m2      poid 2
 * \return   le poid inferieur.
 */
bool compaPoid0Graph(const graphe m1,const graphe m2, int i)
{
    return m1.getpoid(i)<m2.getpoid(i);
}

/**
 * \brief       Affichage de pareto
 * \details    Affiche le pareto sans dijkstra
 * \param    dom        les graphes domines
 * \param    nodom      les graphes nondomines
 * \param    mespoids   les poids pour l'affichage
 * \param    svgout     la feuille svg
* \param    choix      inutile
 */

void affpareto(std::vector<graphe> dom, std::vector<graphe> nodom,std::vector<float> mespoids, Svgfile& svgout, int choix)
{
    int d=7;
    std::sort(mespoids.begin(),mespoids.end(),compaPoid1Graph);
    svgout.addText(10,15, "cout 2", "black");
    svgout.addText(750,790, "cout 1", "black");
    svgout.addLine(0, 5,5,0,"black" );
    svgout.addLine(5,0,10,5,"black");
    svgout.addLine(795, 790,800,795, "black");
    svgout.addLine(800,795,795,800, "black");
    svgout.addLine(5,1,5,800, "black");
    svgout.addLine(1,795,800, 795,"black");
    int y=15;
    int i=0;


    for(graphe mg:dom)
    {
        svgout.addDisk((mg.getpoid(0)*d),(795-mg.getpoid(1)*(d))+mespoids[mespoids.size()-1],2.5,"green");
        svgout.addText(650, y, "Poids graphe", "black");
        svgout.addText(735 , y, i, "black");
        svgout.addText(740, y, " ", "black");
        svgout.addText(750, y, mg.getpoid(0), "black");
        svgout.addText(780, y," // ", "black");
        svgout.addText(795, y, mg.getpoid(1), "black");
        y=y+40;
        i++;
    }
}



/**
 * \brief       Affichage de pareto
 * \details    Affiche le pareto avec plus de 2 poids
 * \param    dom        les graphes domines
 * \param    nodom      les graphes nondomines
 * \param    mespoids   les poids pour l'affichage
 * \param    svgout     la feuille svg
 * \param    x     ?
 * \param    y     ?
 */
void affpareto2(std::vector<graphe> dom, std::vector<graphe> nodom,std::vector<float> mespoids, Svgfile& svgout, int x, int y, int choix)
{
    int d=1;
    if(choix <=2)
    {
        d=2;
    }
    int aa=50;
        int i=0;
    if((x==0)&(y==1))
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
            if(mg.getpoid(y)>1000)
            {
                if(mg.getpoid(y)>10000)
                    aa=100;
                mg.setpoiddij(mg.getpoid(y)/aa, y);
            }
            if(mg.getpoid(x)>1000)
            {
                if(mg.getpoid(x)>10000)
                    aa=100;
                 mg.setpoiddij(mg.getpoid(x)/aa, x);
            }

            svgout.addDisk((mg.getpoid(x)*d),(266-mg.getpoid(y)*d),2,"green");
            svgout.addText(100, 15, "cout 1 // cout 2", "black");
            svgout.addText(100, aa, "Poids graphe", "black");
            svgout.addText(185 , aa, i, "black");
            svgout.addText(200, aa, mg.getpoid(0), "black");
            svgout.addText(230, aa," // ", "black");
            svgout.addText(245, aa, mg.getpoid(1), "black");
            aa=aa+40;
            i++;
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
            if(mg.getpoid(y)>1000)
            {
                if(mg.getpoid(y)>10000)
                    aa=100;
                mg.setpoiddij(mg.getpoid(y)/aa, y);
            }
            if(mg.getpoid(x)>1000)
            {
                if(mg.getpoid(x)>10000)
                    aa=100;
                 mg.setpoiddij(mg.getpoid(x)/aa, x);
            }
            svgout.addDisk((mg.getpoid(x)*d)+266,(532-mg.getpoid(y)*d),2,"green");
            svgout.addText(400, 15, "cout 1 // cout 2", "black");
            svgout.addText(400, aa, "Poids graphe", "black");
            svgout.addText(485 , aa, i, "black");
            svgout.addText(500,aa, mg.getpoid(0), "black");
            svgout.addText(530, aa," // ", "black");
            svgout.addText(545, aa, mg.getpoid(1), "black");
            aa=aa+40;
            i++;
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
            if(mg.getpoid(y)>1000)
            {
                if(mg.getpoid(y)>10000)
                    aa=100;
                mg.setpoiddij(mg.getpoid(y)/aa, y);
            }
            if(mg.getpoid(x)>1000)
            {
                if(mg.getpoid(x)>10000)
                    aa=100;
                 mg.setpoiddij(mg.getpoid(x)/aa, x);
            }
            svgout.addDisk((mg.getpoid(x)*d)+532,(798-mg.getpoid(y)*d),2,"green");
            svgout.addText(650, 15, "cout 1 // cout 2", "black");
            svgout.addText(650, aa, "Poids graphe", "black");
            svgout.addText(735 , aa, i, "black");
            svgout.addText(740, aa, " ", "black");
            svgout.addText(750, aa, mg.getpoid(0), "black");
            svgout.addText(780, aa," // ", "black");
            svgout.addText(795, aa, mg.getpoid(1), "black");
            aa=aa+40;
            i++;
        }
    }

}

/**
 * \brief       Affichage de pareto
 * \details    Affiche le pareto avec dijkstra
 * \param    dom        les graphes domines
 * \param    mespoids   les poids pour l'affichage
 * \param    svgout     la feuille svg
 * \param    choix     poid sur lequel on travaille
 */
void affparetodij(std::vector<graphe> dom,std::vector<float> mespoids, Svgfile& svgout, int choix)
{
    int i=0;
    int aa=40;
svgout.addText(10,15, "cout 2", "black");
    svgout.addText(750,790, "cout 1", "black");
    svgout.addLine(0, 5,5,0,"black" );
    svgout.addLine(5,0,10,5,"black");
    svgout.addLine(795, 790,800,795, "black");
    svgout.addLine(800,795,795,800, "black");
    svgout.addLine(5,1,5,800, "black");
    svgout.addLine(1,795,800, 795,"black");
    for(graphe mg:dom)
    {
        if(choix==4)
        {
            mg.setpoiddij(mg.getpoid(1)/10, 1);///Pour manhattan
        }
        else if(choix==3)
        {
            mg.setpoiddij(mg.getpoid(1)/5, 1);
        }
        else if(choix==1)
        {
            mg.setpoiddij(mg.getpoid(1)*2, 1);
            mg.setpoiddij(mg.getpoid(0)*5,0);
        }
        svgout.addDisk(mg.getpoid(0),(799-mg.getpoid(1)),5,"green");
             svgout.addText(650, 15, "cout 1 // cout 2", "black");
            svgout.addText(650, aa, "Poids graphe", "black");
            svgout.addText(735 , aa, i, "black");
            svgout.addText(740, aa, " ", "black");
            svgout.addText(750, aa, mg.getpoid(0), "black");
            svgout.addText(780, aa," // ", "black");
            svgout.addText(795, aa, mg.getpoid(1), "black");
            aa=aa+40;
            i++;
    }
}
/**
 * \brief       Pareto
 * \details    creation de la frontiere de pareto
 * \param    possi      les graphes possibles
 * \param    svgout     feuille svg
 * \param    dij        1 on fait dijkstra 0 on fait pareto normal
 * \param    poidselec  poid sur lequel on fait le dijkstra
 */

std::vector<graphe> graphe::FrontPareto(std::vector<graphe> possi, Svgfile& svgout,int dij,int poidselec, int x, int y, int nbpoid, int choix)
{
    std::vector<graphe> domine;
    std::vector<graphe> nndomine;
    std::vector<float> mespoid;


    int nbsommet= m_sommets.size();
    float res=0;
    float** ma_matrice= new float*[nbsommet];
    for (int i = 0; i < nbsommet; i++)
    ma_matrice[i] = new float[nbsommet];
    std::sort(possi.begin(),possi.end(),std::bind(compaPoid0Graph, std::placeholders::_1, std::placeholders::_2, x));
    if(dij==0)
    {
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
            }
            else if(mesGr.getpoid(y)<yref)
            {
                domine.push_back(mesGr);
                yref=mesGr.getpoid(y);
            }
            else
            {
                if((mesGr.getpoid(y)!=yref)&&(nbpoid!=3))
                nndomine.push_back(mesGr);
            }
        }
       // std::cout<<"nb frontiere juste pajeto: "<<domine.size()<<std::endl;
        std::sort(mespoid.begin(),mespoid.end(),compaPoid1Graph);

    if(nbpoid==2)
    {
                affpareto(domine,nndomine,mespoid,svgout, choix);
    }
    else if(nbpoid==3)
    {
        affpareto2(domine,nndomine,mespoid,svgout, x, y, choix);
    }
    }


    if(dij==1)
    {
        graphetomatradj(possi[0],ma_matrice,poidselec);
        possi[0].setpoiddij(mon_djiskstra(ma_matrice,INFINI),poidselec);
        domine.push_back(possi[0]);
        float yref=domine[0].getpoid(poidselec);
        float dij_maillon=0;
        for(graphe mesGr:possi)
        {
            for (int i = 0; i < nbsommet; i++)
            {
                for (int j = 0; j < nbsommet; j++)
                {
                    ma_matrice[i][j]=0;
                }
            }
            graphetomatradj(mesGr,ma_matrice,poidselec);
            dij_maillon=mon_djiskstra(ma_matrice,yref);
            if((dij_maillon<yref)&&(mesGr.getpoid(0)==domine[domine.size()-1].getpoid(0)))
            {
                mesGr.setpoiddij(dij_maillon,poidselec);
                domine.pop_back();
                domine.push_back(mesGr);
                yref=dij_maillon;
            }
            if(dij_maillon<yref)
            {

                mesGr.setpoiddij(dij_maillon,poidselec);
                mespoid.push_back(mesGr.getpoid(poidselec));
                domine.push_back(mesGr);
                yref=dij_maillon;
            }
        }
    }
    for (int i = 0; i < nbsommet; i++)
        delete[] ma_matrice[i];
    delete[] ma_matrice;
    return domine;

}

/**
 * \brief    mon poid total de graphe
 * \details  addition des poids
 * \param    krusk      vector d'aretes du graphe
 * \param    poid       poid sur lequel on travaille
 * \return un float mon poid total
 */

float graphe::mon_poidtot(std::vector<Aretes*> Krusk,int poid)
{
    float mon_poidtot=0.0;
    for(Aretes* j:Krusk)
    {
        mon_poidtot+=j->getpoidnb(poid);
    }
    return mon_poidtot;
}

/**
 * \brief    algo Kruskal
 * \details  on cherche l'arbre de poids couvrants minimun
 * \param    svgout     feuille svg
 * \param    p       poid sur lequel on travaille
 * \return   l'arbre
 */
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
        (*itr)->dessinerArete(svgout,"red",posx,50);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,posx,50);
    }
    auto poidstring=std::to_string(p);
    poidarbre=mon_poidtot(Arbre,p);
    auto poidtotstring=std::to_string(poidarbre);
    svgout.addText(posx+100,100+m_sommets[m_sommets.size()-1]->getX(),"Kruskal pour le poids ("+poidstring+"), le poids total : ("+poidtotstring+")","black");
    return Arbre;

}

/**
 * \brief    algo connexite
 * \details  on fait un tableau de connexit�
 * \return   le tableau de connexe
 */
int graphe::Connexite()
{
    int ordre=m_sommets.size();
    int* tab_connexe=new int[ordre];
    int val_prede,val_s1,val_s2,connexe=0;
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
    delete[]tab_connexe;
    return connexe;
}

/**
 * \brief    algo Pareto
 * \details  on cherche toutes les possibilites admissibles avec (pour dijkstra) et sans cycle
 * \param    svgout     feuille svg
 * \param    dij     choix realise dans le main si on fait dijkstra ou non
 * \param    poidselec     poid sur lequel on travaille le dijkstra
 */
void graphe::Pareto(Svgfile &svgout,int dij,int poidselec, int choix)
{
    std::vector<std::vector<bool>> graphepossibles;
    std::vector<bool> last;
    int ordre=m_sommets.size();
    std::vector<graphe> toutesPossi;
    std::vector<graphe>mes_dijkstra;
    graphe allgraphes= {"files/sous_graphe.txt","files/sous_graphe.txt"};
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
    //std::cout<<"size:"<<toutesPossi.size()<<std::endl;
    std::vector<graphe> domine;
    std::vector<graphe> domine1;
    std::vector<graphe> domine2;
    std::vector<graphe> domine3;
    int d=1;
    if(choix<=2)
    {
        d=2;
    }

    if((m_nbpoid==2)||(dij==1))
        domine=FrontPareto(toutesPossi, svgout,dij,poidselec, 0, 1, m_nbpoid, choix);
    else if((m_nbpoid==3)&&(dij==0))
    {
        domine1=FrontPareto(toutesPossi, svgout,dij,poidselec, 0, 1, m_nbpoid, choix);
        domine2=FrontPareto(toutesPossi, svgout,dij,poidselec,1, 2, m_nbpoid, choix);
        domine3=FrontPareto(toutesPossi, svgout,dij,poidselec, 0, 2, m_nbpoid, choix);
        for(graphe dom:domine1)
        {
            for(graphe dim:domine2)
            {
                for(graphe dam :domine3)
                {
                     if((dom.getpoid(0)==dim.getpoid(0))&&(dom.getpoid(0)==dam.getpoid(0)))
                    {
                        svgout.addDisk(725,695,4,"blue");
                        svgout.addText(750,700, "graphe en commun au trois Frontires de Pareto ", "black");
                        svgout.addDisk(dom.getpoid(0)*d,(266-dom.getpoid(1)*d),2,"blue");
                        svgout.addDisk(dim.getpoid(1)*d+266,(532-dim.getpoid(2)*d),2,"blue");
                        svgout.addDisk(dam.getpoid(0)*d+532,(798-dam.getpoid(2)*d),2,"blue");
                    }
                }

            }


        }
    }


    std::cout<<std::endl;
    //std::cout<<"nb sol admissibles:"<<toutesPossi.size()<<std::endl;
}

/**
 * \brief      trie des aretes
 * \details    trie des aretes d'un graphe en fonction de leur poids
 */
void graphe::trier()
{
    std::sort(m_aretes.begin(),m_aretes.end(),compaPoid);
}


/**
 * \brief      dessin des graphes
  * \details   dessin des sommets et des aretes du graphe
 * \param    svgout         feuille de dessin.
 * \param    posx         position ou l'on va dessiner le graphe.
 */
void graphe::afficher(Svgfile& svgout,int posx) const
{
    for(auto itr=m_aretes.begin(); itr!=m_aretes.end(); itr++)
    {
        (*itr)->dessinerArete(svgout,"black",posx,50);
    }
    for(auto it=m_sommets.begin(); it!=m_sommets.end(); it++)
    {
        it->second->dessinerSommet(svgout,posx,50);
    }
}
/**
 * \brief    setteur d'arete
 * \param    unearete     arete que l'on definit.
 */
void graphe::setar(Aretes* unearete)
{
    m_aretes.push_back(unearete);
}
/**
 * \brief    getteur du nombre de poid
 * \return    m_nbpoid    le nombre de poid du graphe.
 */
int graphe::getnbpoid()const
{
    return m_nbpoid;
}
/**
 * \brief    getteur du poid que l'on veut du graphe
  * \param    i    le numero du poid sur lequel on travaille.
 * \return    m_nbpoid    le poid reel du graphe.
 */
float graphe::getpoid(int i) const
{
    return m_poid[i];
}

/**
 * \brief    setteur de poid
* \details   on set le poid sur lequel on realise le dijkstra avec le poid calcule
  * \param    poid    poid reel dijkstra calcule.
 * \param    poidselec    poid sur lequel on fait le dijkstra.
 */
void graphe::setpoiddij(float poid,int poidselec)
{
    this->m_poid[poidselec]=poid;
}

/**
 * \brief    setteur de vecteur de poid du graphe
  * \param    poid    poid reel  calcule.
 */
void graphe::setvectpoid(float poid)
{
    m_poid.push_back(poid);
}


/**
 * \brief    matrice d'adjacence d'un graphe
 * \details  on convertie le graphe en matrice d'adjacence
  * \param    mon_graphe    graphe que l'on etudie.
  * \param    ma_matrice    matrice d'adjacence.
  * \param    poidselec    poid sur lequel on travaille.
 */
void graphe::graphetomatradj(graphe mon_graphe,float** ma_matrice,int poidselec)
{
    for(auto it : mon_graphe.getmesaret())
    {
        int idso1 =it->getsommet1()->getid();
        int idso2 =it->getsommet2()->getid();
        ma_matrice[idso1][idso2]=it->getpoidnb(poidselec);
        ma_matrice[idso2][idso1]=it->getpoidnb(poidselec);
    }
}

/**
 * \brief    algo dijkstra
 * \details  on realise le dijkstra sur tout les sommets tant que la valeur ne soit pas superieur a notre dijkstra de reference (on evite aisni de nombreux calculs)
  * \param    matrice_adjacence    matrice d'adjacence du graphe.
  * \param    yref    valeur dijkstra de reference.
  * \return   un reel, le resultat dijkstra de la possibilite du graphe.
 */
float graphe::mon_djiskstra(float** matrice_adjacence,float yref)
{
    float resultdij=0;
    for(int i=0; i<m_sommets.size(); i++)
    {
        resultdij+=djikstra(matrice_adjacence,i,yref);
        if(resultdij>yref)
            break;
    }
    return resultdij;
}

/**
 * \brief    algo dijkstra
 * \details  on realise le dijkstra sur 1 sommet passer en parametre
  * \param    matrice_adjacence    matrice d'adjacence du graphe.
  * \param    s    id du sommet sur lequel on travaille.
  * \param    yref    inutile.
  * \return   un reel, le resultat dijkstra d'un sommet.
 */
float graphe::djikstra(float** matrice_adjacence,int s,float yref)
{
    int nbsommet= m_sommets.size();
    int *sommet_marques=new int[nbsommet];
    float *long_min=new float[nbsommet];
    int* pred=new int[nbsommet];
    int nums1,nums2,smin=0;
    float minim;
    int nb=0;
    float result=0.0;

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
    free(sommet_marques);
    free(long_min);
    free(pred);
    return result;
}


/**
 * \brief    getteur de vecteur de poid
  * \return  mon vecteur de poid du graphe.
 */
std::vector<float> graphe::getvectpoid()const
{
    return m_poid;
}

Couleur graphe::getcoul()const
{
    return m_couleur;

}
