#include "belyeg.h"

const string &Belyeg::getNev() const
{
    return nev;
}

void Belyeg::setNev(const string &newNev)
{
    nev = newNev;
}

Belyeg::Belyeg(const string &nev, const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog) : Abra(meret, forras, xKoordinata, yKoordinata, dolesszog),
    nev(nev)
{}
