#include "oldal.h"

unsigned int Oldal::getOldalszam() const
{
    return oldalszam;
}

void Oldal::elemekElrejtese()
{
    //keretek elrejteese
    for(auto i : keretek)
    {
        i->getKimenet()->hide();
    }

    //bejegek elrejteese
    for(auto i : belyegek)
    {
        i->getKimenet()->hide();
    }

    //szovegek elrejteese
    for(auto i : szovegek)
    {
        i->getKimenet()->hide();
    }
}

void Oldal::elemekMutatasa()
{
    //keretek mutatasa
    for(auto i : keretek)
    {
        i->getKimenet()->show();
    }

    //bejegek mutatasa
    for(auto i : belyegek)
    {
        i->getKimenet()->show();
    }

    //szovegek mutatasa
    for(auto i : szovegek)
    {
        i->getKimenet()->show();
    }
}

void Oldal::egysegesKeret(unsigned short index)
{
    for(auto i : keretek)
    {
        i->setKeret(index);
        i->kepKeszites();
    }
}

list<Keret*> Oldal::getKeretek() const
{
    return keretek;
}

list<Belyeg *> Oldal::getBelyegek() const
{
    return belyegek;
}

list<Szoveg*> Oldal::getSzovegek() const
{
    return szovegek;
}

Oldal::Oldal(const unsigned &oldalszam): oldalszam(oldalszam)
{
}

Stilus* Oldal::getStilus()
{
    return &stilus;
}

void Oldal::belyegHozzaadas(Belyeg *ujBelyeg)
{
    belyegek.push_back(ujBelyeg);
}

void Oldal::belyegTorles(Belyeg *belyeg)
{
    belyegek.remove(belyeg);
}

void Oldal::keretHozzaadas(Keret *ujKeret)
{
    keretek.push_back(ujKeret);
}

void Oldal::keretTorles(Keret *keret)
{
    keretek.remove(keret);
}

void Oldal::szovegHozzaadas(Szoveg *ujSzoveg)
{
    szovegek.push_back(ujSzoveg);
}

void Oldal::szovegTorles(Szoveg *szoveg)
{
    szovegek.remove(szoveg);
}
