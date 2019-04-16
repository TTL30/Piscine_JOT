#ifndef ARETES_H_INCLUDED
#define ARETES_H_INCLUDED
#include "sommet.h"
#include <vector>


class Aretes
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Aretes(std::string id,std::vector<float> p, Sommet* s1, Sommet* s2, int taille, int tp);
        ~Aretes();
        void afficher()const;
        float getpoid(int i) const {return m_poid[i];}
        int getnbpoid() const {return m_nbpoid;}
        int get_taillep() const {return m_taille;}
        void setnbpoid(int i) { m_nbpoid=i;}


        int add() { return m_nbpoid+1;}
        void dessinerArete(Svgfile& svgout)const;



    protected:


    private:
        /// Données spécifiques du sommet
        int m_taille;
        int m_nbpoid;
        std::string m_id; // Identifiant
        std::vector<float> m_poid;
        Sommet* m_s1;
        Sommet* m_s2;

};

#endif // ARETES_H_INCLUDED
