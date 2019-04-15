#ifndef ARETES_H_INCLUDED
#define ARETES_H_INCLUDED
#include "sommet.h"
#include <vector>


class Aretes
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Aretes(std::string id,std::vector<float> p, Sommet* s1, Sommet* s2, int taille);
        ~Aretes();
        void afficher()const;
        std::vector<float> getpoid() const {return m_poid;}


    protected:


    private:
        /// Données spécifiques du sommet
        int m_taille;
        std::string m_id; // Identifiant
        std::vector<float> m_poid;
        Sommet* m_s1;
        Sommet* m_s2;

};

#endif // ARETES_H_INCLUDED
