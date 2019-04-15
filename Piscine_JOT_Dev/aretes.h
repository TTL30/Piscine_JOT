#ifndef ARETES_H_INCLUDED
#define ARETES_H_INCLUDED
#include "sommet.h"

class Aretes
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Aretes(std::string id,float* p, Sommet* s1, Sommet* s2, int taille);
        ~Aretes();
        void afficher()const;
        void dessinerAretes(Svgfile& svgout)const;



    protected:


    private:
        /// Données spécifiques du sommet
        int m_taille;
        std::string m_id; // Identifiant
        float* m_poid;
        Sommet* m_s1;
        Sommet* m_s2;

};

#endif // ARETES_H_INCLUDED
