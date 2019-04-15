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
        ~graphe();
        void afficher(Svgfile& svgout) const;
        Sommet getSom() const;
        void trier();
        void Kruskal();
        int getTaillear()const;

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Aretes*> m_aretes;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)

};

#endif // GRAPHE_H
