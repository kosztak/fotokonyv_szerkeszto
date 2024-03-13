#include "projekt.h"

const string &Projekt::getNev() const
{
    return nev;
}

void Projekt::setNev(const string &newNev)
{
    nev = newNev;
}

const unsigned &Projekt::getOldalszam() const
{
    return oldalszam;
}

void Projekt::setOldalszam(const unsigned &newOldalszam)
{
    oldalszam = newOldalszam;
}

void Projekt::oldalHozzaadas(Oldal* oldal)
{
    oldalak.push_back(oldal);
    ++oldalszam;

    if(jelenlegiOldal == nullptr)
        jelenlegiOldal = oldal;
}

void Projekt::oldalTorles(unsigned index)
{

}

const list<string> &Projekt::getKepek() const
{
    return kepek;
}

void Projekt::addKep(string eleres)
{
    kepek.push_back(eleres);
}

Oldal* Projekt::getJelenlegiOldal() const
{
    return jelenlegiOldal;
}

void Projekt::setJelenlegiOldal(const unsigned &newJelenlegiOldal)
{

}

Elem* Projekt::getJelenlegiElem() const
{
    return jelenlegiElem;
}

void Projekt::setJelenlegiElem(Elem *newJelenlegiElem)
{
    jelenlegiElem = newJelenlegiElem;
}

bool Projekt::lapozas(const bool &fel)
{
    if(!((fel && jelenlegiOldal->getOldalszam() == oldalszam) || (!fel && jelenlegiOldal->getOldalszam() == 1)))
    {
        Oldal* ujOldal;
        if(fel)
        {
            ujOldal = oldalak[jelenlegiOldal->getOldalszam()];

        }else{
            ujOldal = oldalak[jelenlegiOldal->getOldalszam()-2];
        }

        //regi elemek elrejtése
        jelenlegiOldal->elemekElrejtese();

        //uj elemek mutatasa
        ujOldal->elemekMutatasa();

        jelenlegiOldal = ujOldal;

        return true;
    }

    return false;
}

string Projekt::getEleresiUt() const
{
    return eleresiUt;
}

Projekt::Projekt(const string &nev, const string &eleresiUt) : nev(nev), eleresiUt(eleresiUt)
{

}
