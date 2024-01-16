#include "szoveg.h"

const string &Szoveg::getTartalom() const
{
    return tartalom;
}

void Szoveg::setTartalom(const string &newTartalom)
{
    tartalom = newTartalom;
    kimenet->setText(QString::fromStdString(newTartalom));
}

const QColor &Szoveg::getSzin() const
{
    return szin;
}

void Szoveg::setSzin(const QColor &newSzin)
{
    szin = newSzin;
}

const QFont &Szoveg::getBetutipus() const
{
    return betutipus;
}

unsigned Szoveg::getMeret() const
{

}

void Szoveg::setMeret(unsigned ujMeret)
{

}

bool Szoveg::isFelkover() const
{

}

void Szoveg::setFelkover(bool ertek)
{

}

bool Szoveg::isDolt() const
{

}

void Szoveg::setDolt(bool ertek)
{

}

void Szoveg::setBetutipus(const QFont &newBetutipus)
{
    betutipus = newBetutipus;
}

Szoveg::Szoveg(const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog) : Elem(xKoordinata, yKoordinata, dolesszog)
{
    tartalom = "szöveg";
}
