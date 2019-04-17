#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "aretes.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string, std::string);
        ~graphe();
        void afficher(Svgfile& svgout) const;
        Sommet getSom() const;
        std::vector<Aretes*> kruskal (Svgfile& svgout,int i);
        float mon_poidtot(std::vector<Aretes*> Krusk,int poid);
        Aretes* get_aret(){return m_aretes[0];}

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<Aretes*> m_aretes;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)

};

#endif // GRAPHE_H
