#include "elem.h"

int Elem::getDolesszog() const
{
    return dolesszog;
}

ElemTipus Elem::getTipus() const
{
    return tipus;
}

Kimenet *Elem::getKimenet() const
{
    return kimenet;
}

Elem::Elem(unsigned xKoordinata, unsigned yKoordinata, int dolesszog):
    dolesszog(dolesszog)
{
    kimenet->move(xKoordinata, yKoordinata);
}

void Elem::forgatas(int szog)
{
    dolesszog = szog;
}
