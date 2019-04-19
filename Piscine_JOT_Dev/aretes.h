#ifndef ARETES_H_INCLUDED
#define ARETES_H_INCLUDED
#include "sommet.h"
#include <vector>


class Aretes
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Aretes(int id,std::vector<float> p, Sommet* s1, Sommet* s2, int taille, std::vector<bool> bolAr,int tp);
        ~Aretes();
        void afficher()const;
        float getpoidnb(int i) const {return m_poid[i];}
        void setnbpoid(int i) { m_nbpoid=i;}
        int add() { return m_nbpoid+1;}
        int getnbpoid() const {return m_nbpoid;}
        std::vector<float> getpoid() const {return m_poid;}
        int gettaille()const {return m_taille;}
        Sommet* getsommet1()const {return m_s1;}
        Sommet* getsommet2()const {return m_s2;}
        bool getbolAr(int i) const {return m_bolAr[i];}
        std::vector<bool> getbolArr() const {return m_bolAr;}
        int getid();
        void dessinerArete(Svgfile& svgout,std::string m_couleur,int posxinit,int posyinit)const;



    protected:


    private:
        /// Données spécifiques du sommet
        int m_taille;
        int m_id; // Identifiant
        int m_nbpoid;
        std::vector<float> m_poid;
        Sommet* m_s1;
        Sommet* m_s2;
        std::vector<bool> m_bolAr;


};

#endif // ARETES_H_INCLUDED
