#include "keret.h"

void Keret::kepKeszites()
{
    QPixmap ujKep;
}

const QPixmap &Keret::getKep() const
{
    return kep;
}

void Keret::setKeret(unsigned index)
{

}

unsigned short Keret::getSzelesseg() const
{
    return szelesseg;
}

void Keret::setSzelesseg(unsigned short newSzelesseg)
{
    szelesseg = newSzelesseg;
}

unsigned short Keret::getMagassag() const
{
    return magassag;
}

void Keret::setMagassag(unsigned short newMagassag)
{
    magassag = newMagassag;
}

unsigned int Keret::getKepXKoordinata() const
{
    return kepXKoordinata;
}

void Keret::setKepXKoordinata(unsigned int newKepXKoordinata)
{
    kepXKoordinata = newKepXKoordinata;
}

unsigned int Keret::getKepYKoordinata() const
{
    return kepYKoordinata;
}

void Keret::setKepYKoordinata(unsigned int newKepYKoordinata)
{
    kepYKoordinata = newKepYKoordinata;
}

Keret::Keret(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany, unsigned short szelesseg, unsigned short magassag, unsigned kepXKoordinata, unsigned kepYKoordinata) : Abra(meret, forras, xKoordinata, yKoordinata, dolesszog, meretArany),
    szelesseg(szelesseg), magassag(magassag), kepXKoordinata(kepXKoordinata), kepYKoordinata(kepYKoordinata)
{}
