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
        Sommet(std::string,double,double);
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins() const;
void dessinerSommet(Svgfile& svgout, int posinitx,int posinity)const;

        ~Sommet();
        double getX() const;
        double getY() const;
        std::vector<const Sommet*> getVois()const {return m_voisins;}
        std::string getid()const {return m_id;}
        std::unordered_map<std::string,std::string> parcoursDFS() const;




    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
