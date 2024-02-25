#include "stilus.h"

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

}
