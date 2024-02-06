#include "minta.h"

const string &Minta::getNev() const
{
    return nev;
}

void Minta::setNev(const string &newNev)
{
    nev = newNev;
}

const string &Minta::getEleresiUt() const
{
    return eleresiUt;
}

const QPixmap &Minta::getKep() const
{
    return kep;
}

Minta::Minta(const string &nev, const string &eleresiUt, const QPixmap &kep) : nev(nev),
    eleresiUt(eleresiUt),
    kep(kep)
{}
