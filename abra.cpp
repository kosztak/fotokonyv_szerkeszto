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
    QPixmap ujKep(QString::fromStdString(eleres));
    forras = ujKep;
    meret = ujKep.size();
}

unsigned short Abra::getMeretArany() const
{
    return meretArany;
}

void Abra::setMeretArany(unsigned short newMeretArany)
{
    meretArany = newMeretArany;
}

string Abra::getEleres() const
{
    return eleres;
}

void Abra::setEleres(const string &newEleres)
{
    eleres = newEleres;
}

Abra::Abra(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany) : Elem(xKoordinata, yKoordinata, dolesszog),
    meret(meret),
    forras(forras),
    meretArany(meretArany)
{}

Abra::Abra(const QSize &meret, const string &eleres, const unsigned int &xKoordinata, const unsigned int &yKoordinata, int dolesszog, unsigned short meretArany) : Elem(xKoordinata, yKoordinata, dolesszog),
    meret(meret),
    forras(QPixmap(QString::fromStdString(eleres))),
    eleres(eleres),
    meretArany(meretArany)
{

}
