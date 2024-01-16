#include "abra.h"

const QSize &Abra::getMeret() const
{
    return meret;
}

const QPixmap &Abra::getForras() const
{
    return forras;
}

void Abra::setForras(const string &eleres)
{

}

unsigned short Abra::getMeretArany() const
{
    return meretArany;
}

void Abra::setMeretArany(unsigned short newMeretArany)
{
    meretArany = newMeretArany;
}

Abra::Abra(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany) : Elem(xKoordinata, yKoordinata, dolesszog),
    meret(meret),
    forras(forras),
    meretArany(meretArany)
{}
