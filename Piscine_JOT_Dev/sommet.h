#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "svgfile.h"

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(int,double,double);
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        void dessinerSommet(Svgfile& svgout, int posinitx,int posinity)const;

        ~Sommet();
        int getX() const;
        int getY() const;
        std::vector<const Sommet*> getVois()const {return m_voisins;}
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        void dessinerSommet(Svgfile& svgout)const;
        std::vector <const Sommet*> getvoisin() const;
        int getid() const;




    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;

        /// Données spécifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
