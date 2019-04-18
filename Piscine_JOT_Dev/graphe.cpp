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

int graphe::connex2(int nbsom)
{
    int con=0;
    int k=0;
    int ordre=m_sommets.size();
    int taille=m_aretes.size();
    int nbar=0;
    std::vector<Sommet*> messom;
    //nmessom.push_back(m_aretes[0]->getsommet1());
    int** connection;
    connection=(int**) malloc(ordre*sizeof(int*));
    int nbcon=0;
    int cpt=0;
    int var=0;
    if (connection == NULL)
    {
        printf("pb espace connexe");
        exit(1);
    }
    for (int i=0; i<ordre; i++)
    {
        connection[i]=(int*)malloc(ordre* sizeof(int));
        if(connection[i]==NULL)
        {
            printf("pb espace connexe");
            exit(1);
        }
    }
    for (int i=0; i<nbsom; ++i)
    {
        for(int j=0; j<nbsom; ++j)
        {
            connection[i][j]=i;

        }
    }


    for(auto testcon : m_aretes)
    {
        nbar++;
        //std::cout<<"aretes"<<testcon->getsommet1()->getid()<<";"<<testcon->getsommet2()->getid()<<std::endl;
        int val=testcon->getsommet2()->getid();
        int s1=testcon->getsommet1()->getid();
        int k=0;


        //connex[testcon->getsommet2()->getid()][testcon->getsommet1()->getid()]=connex[testcon->getsommet1()->getid()][testcon->getsommet1()->getid()];
        for(int c=s1; c<ordre; c++)
        {
            int cpt=c;
            var=connection[val][c];
            connection[val][c]=connection[s1][s1];
            //connection[var][c]=connection[s1][s1];

            for (int i=0; i<nbsom; ++i)
            {
                //std::cout<<"ouiief "<<connection[i][c-1]<<std::endl;
                //std::cout<<"ouiiefdsqdsq "<<connection[var][c-1]<<std::endl;

              if(connection[i][c-1]==connection[var][c-1])
              {
                connection[i][c]= connection[s1][s1];
              }
            }
            //std::cout<<connection[c][val]<<std::endl;

        }
    }
    for(int j=0; j<ordre; j++)
    {
        //std::cout<<connection[j][ordre-1]<<std::endl;

    }
    while(k<ordre-1)
    {
        //printf("test\n");

        if(connection[k][ordre-1]!=connection[k+1][ordre-1])
        {
            printf("A\n");
            nbcon=1;
            k=ordre-1;
        }
        else
        {
            k++;
        }
    }
    //std::cout<<nbcon<<std::endl;


    return nbcon;

}




/*for(Aretes* are:m_aretes)
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
    con++;*/



//}

//}*/


/*if(messom.size()==nbsom) {con=0;}
 messom.clear();
return con;
}*/


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

/*void graphe::Pareto(Svgfile& svgout)
{
    std::vector<graphe> toutesPossi;
    std::vector<graphe> paretoo;

    //graphe allgraphes={"files/sous_graphe.txt","files/sous_graphe.txt"};
    std::vector<bool> allaretes(nbaret,false);
    std::vector<Sommet*> allsom;
    int con=0;


    for(int i=0; i<pow(2,nbaret)-1;++i)
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
    toutesPossi[0].afficher(svgout);


}*/

void graphe::Pareto(Svgfile &svgout)
{
    //std::vector<graphe> salut;
    //std::vector<graphe> paretoo;
    std::vector<std::vector<bool>> graphepossibles;
    int nombreAr=0;
    int ordre=m_sommets.size();
    std::vector<graphe> toutesPossi;
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
        /*for(int k=0;k<allaretes.size();++k)
        {
            std::cout<<allaretes[k];

        }*/

        //allgraphes.m_aretes.push_back(allaretes);

        std::vector<graphe> paretoo;

        //graphe allgraphes={"files/sous_graphe.txt","files/sous_graphe.txt"};
        std::vector<Sommet*> allsom;
        int con;


        //for(int i=0; i<pow(2,nbaret)-1;++i)
        //{
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


        if(cas==m_nbsom-1)
        {
            con=allgraphes.connex2(m_nbsom);
            printf("connexe: %d\n",con);

            if(con==0)
            {
                toutesPossi.push_back(allgraphes);
            }

        }
        allgraphes.m_aretes.clear();
        allgraphes.m_sommets.clear();

        //}
        /*for(int i=0;i<toutesPossi.size();++i)
        {
            toutesPossi[i].afficher(svgout);

        }*/
    }
    while(std::next_permutation(allaretes.begin(),allaretes.end()));
    std::cout<<std::endl;
    int oui=0;
    int non=toutesPossi.size();
    int cones=toutesPossi[non-1].connex2(m_nbsom);
    toutesPossi[oui].afficher(svgout);
    int cone=toutesPossi[oui].connex2(m_nbsom);
    std::cout<<"monnb "<<cone<<cones<<std::endl;
    /*int cone=toutesPossi[oui].connex2(ordre);
    if (cone==0)
    {
        printf("connexe");
        toutesPossi[oui].afficher(svgout);

    }
    else
    {
        printf("pas connexe");
    }*/
    std::cout<<"size"<<toutesPossi.size()<<std::endl;

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
/*<<<<<<< HEAD // ancien algo possibilités
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

}*/

/*std::vector<bool> graphe::possibilites(std::vector<bool> allaretes)
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
}*/


void graphe::setar(Aretes* unearete)
{
    m_aretes.push_back(unearete);
}


