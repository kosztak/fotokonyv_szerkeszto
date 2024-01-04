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

void Abra::meretezes(unsigned szelesseg, unsigned hosszusag)
{

}

Abra::Abra(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog) : Elem(xKoordinata, yKoordinata, dolesszog),
    meret(meret),
    forras(forras)
{}
