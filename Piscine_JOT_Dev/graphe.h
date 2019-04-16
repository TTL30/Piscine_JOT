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
        void trier();
        //bool compaPoid(const float m1,const float m2);
        //std::vector<bool> possibilites(std::vector<bool> allaretes);
        void Pareto();
        std::vector<bool> possibilites(std::vector<bool> allaretes);
    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<float> m_poid;
        std::vector<Aretes*> m_aretes;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        int nbaret;
};

#endif // GRAPHE_H
