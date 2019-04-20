#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "aretes.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string, std::string);
        ~graphe(){};
        void afficher(Svgfile& svgout,int posx) const;
        Sommet getSom() const;
        void trier();

        std::vector<Aretes*> kruskal (Svgfile& svgout,int i);
        float mon_poidtot(std::vector<Aretes*> Krusk,int poid);
        Aretes* get_aret(){return m_aretes[0];}
        std::vector<Aretes*> getmesaret(){return m_aretes;}
        float** graphetomatradj(graphe  mon_graphe);
        float djikstra(float**matrice_adjacence,int s);
        void Pareto(Svgfile& svgout,int dij);

        std::vector<bool> possibilites(std::vector<bool> allaretes);
        int Connexite();
        void setar(Aretes* unearete);
        int racine(Sommet i,std::vector<Sommet> foret);
        ///std::vector<Aretes*> get_aret(){return m_aretes;}
        void ajouter(Aretes* are,int i);
        float getpoid( int i) const;
        int getnbarete()const {return nbaret;}
        int getnbpoid()const;
        Couleur getcoul()const;
        void setvectpoid(float poid);
        std::vector<float> getvectpoid() const;
        void setpoiddij(float poiddij);


    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<float> m_poid;
        std::vector<Aretes*> m_aretes;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        int nbaret;
        int m_nbsom;
        int m_nbpoid;
        Couleur m_couleur;
};

#endif // GRAPHE_H
