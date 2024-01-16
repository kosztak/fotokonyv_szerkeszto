#include "keret.h"

void Keret::kepKeszites()
{

}

const QPixmap &Keret::getKep() const
{
    return kep;
}

void Keret::setKeret(unsigned index)
{

}

void Keret::setXKoordinata(int ertek)
{

}

void Keret::setYKoordinata(int ertek)
{

}

Keret::Keret(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany) : Abra(meret, forras, xKoordinata, yKoordinata, dolesszog, meretArany)
{}
