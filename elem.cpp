#include "elem.h"

int Elem::getDolesszog() const
{
    return dolesszog;
}

ElemTipus Elem::getTipus() const
{
    return tipus;
}

QPushButton *Elem::getKimenet() const
{
    return kimenet;
}

Elem::Elem(unsigned xKoordinata, unsigned yKoordinata, int dolesszog):
    xKoordinata(xKoordinata), yKoordinata(yKoordinata), dolesszog(dolesszog)
{

}

void Elem::mozgatas(unsigned xPont, unsigned yPont)
{
}

const unsigned &Elem::getXKoordinata() const
{
    return xKoordinata;
}

const unsigned &Elem::getYKoordinata() const
{
    return yKoordinata;
}

void Elem::forgatas(int szog)
{

}
