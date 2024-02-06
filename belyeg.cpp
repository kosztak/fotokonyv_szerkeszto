#include "belyeg.h"

const string &Belyeg::getNev() const
{
    return nev;
}

void Belyeg::setNev(const string &newNev)
{
    nev = newNev;
}

Belyeg::Belyeg(const string &nev, const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany) : Abra(meret, forras, xKoordinata, yKoordinata, dolesszog, meretArany),
    nev(nev)
{
    tipus = belyeg;
}
