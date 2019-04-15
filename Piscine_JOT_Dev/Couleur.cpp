#include "couleur.h"
#include "svgfile.h"
#include "util.h"
#include <iostream>
#include "time.h"

Couleur::Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : m_rouge{rouge}, m_vert{vert}, m_bleu{bleu}
{ }


Couleur::Couleur()
    : Couleur(0, 0, 0) // Délégation de constructeur
{ }


void Couleur::afficher() const
{
    std::cout << "(" << (int)m_rouge << ", " << (int)m_vert << ", " << (int)m_bleu << ")" << std::endl;
}

uint8_t saisirCanal()
{
    int val;
    val=rand()%(255-1)+1;
    return (uint8_t)val;
}

void Couleur::saisir()
{
    m_rouge = saisirCanal();
    m_vert = saisirCanal();
    m_bleu = saisirCanal();
}

uint8_t muterCanal(uint8_t v, double amplitude)
{
    int val=v;

    val += util::alea(-amplitude, amplitude);

    if ( val<0 )
        val = 0;

    if ( val>255 )
        val = 255;

    return (uint8_t)val;
}

uint8_t Couleur::getR() const
{
    return m_rouge;
}uint8_t Couleur::getV()const
{
    return m_vert;
}uint8_t Couleur::getB()const
{
    return m_bleu;
}

void Couleur::muter(double amplitude)
{
    m_rouge = muterCanal(m_rouge, amplitude);
    m_vert = muterCanal(m_vert, amplitude);
    m_bleu = muterCanal(m_bleu, amplitude);
}

Couleur::operator std::string() const
{
    return Svgfile::makeRGB(m_rouge, m_vert, m_bleu);
}
