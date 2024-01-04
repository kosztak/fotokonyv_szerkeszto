#ifndef PROJEKT_H
#define PROJEKT_H

#include <string>
#include <list>
#include "oldal.h"
#include "keret.h"
#include "belyeg.h"
#include "szoveg.h"

using namespace std;

class Projekt
{
private:
    string nev;
    string elresiUt;
    unsigned oldalszam;
    list<Oldal> oldalak;
    list<string> kepek;
    list<Keret> keretek;
    list<Belyeg> belyegek;
    list<Szoveg> szovegek;
    Oldal *jelenlegiOldal = new Oldal();
    Elem* jelenlegiElem = nullptr;
    ElemTipus jelenlegiElemTipus;
public:
    Projekt();

    const string &getNev() const;
    void setNev(const string &newNev);
    const unsigned &getOldalszam() const;
    void setOldalszam(const unsigned &newOldalszam);
    void oldalHozzaadas(unsigned meret);
    void oldalTorles(unsigned index);
    const list<string> &getKepek() const;
    void addKep(string eleres);
    Oldal* getJelenlegiOldal() const;
    void setJelenlegiOldal(const unsigned &newJelenlegiOldal);
    Elem* getJelenlegiElem() const;
    void setJelenlegiElem(Elem *newJelenlegiElem);
};

#endif // PROJEKT_H
