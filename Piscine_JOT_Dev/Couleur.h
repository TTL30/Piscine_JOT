#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

#include <string>
#include <cstdint>

class Couleur
{
    public :
        Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu);
        Couleur();
        ~Couleur(){};
        void afficher() const;
        void saisir();
        void muter(double amplitude);
        uint8_t getR()const;
        uint8_t getB()const;
        uint8_t getV()const;


        operator std::string() const;

    private :
        // uint8_t équivalent à unsigned char :
        // unsigned 8 bits (8 bits non signé)
        uint8_t m_rouge, m_vert, m_bleu;
};

#endif // COULEUR_H_INCLUDED
