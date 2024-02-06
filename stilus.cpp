#include "stilus.h"

bool Stilus::getElrendezesAktiv() const
{
    return elrendezesAktiv;
}

void Stilus::setElrendezesAktiv(bool ertek)
{
    elrendezesAktiv = ertek;
}

const Elrendezes &Stilus::getElrendezes() const
{
    return elrendezes;
}

void Stilus::setElrendezes(Elrendezes uj)
{
}

bool Stilus::getHatterTipus() const
{
    return hatterTipus;
}

void Stilus::setHatterTipus(bool newHatterTipus)
{
    hatterTipus = newHatterTipus;
}

Minta Stilus::getMinta() const
{
    return minta;
}

void Stilus::setMinta(Minta newMinta)
{
    minta = newMinta;
}

const QColor &Stilus::getSzin() const
{
    return szin;
}

void Stilus::setSzin(const QColor &newSzin)
{
    szin = newSzin;
}

Stilus::Stilus()
{
    elrendezes = Elrendezes();
}

void Stilus::setAktiv(bool ertek)
{

}
