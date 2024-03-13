#ifndef PROJEKT_H
#define PROJEKT_H

#include <string>
#include <list>
#include <algorithm>
#include "oldal.h"
#include "keret.h"
#include "belyeg.h"
#include "szoveg.h"

using namespace std;

class Projekt
{
private:
    string nev;
    string eleresiUt;
    unsigned oldalszam = 0;
    vector<Oldal*> oldalak;
    list<string> kepek;
    Oldal* jelenlegiOldal = nullptr;
    Elem* jelenlegiElem = nullptr;
public:
    Projekt(const string &nev, const string &eleresiUt);
    ~Projekt();

    const string &getNev() const;
    void setNev(const string &newNev);
    const unsigned &getOldalszam() const;
    void setOldalszam(const unsigned &newOldalszam);
    void oldalHozzaadas(Oldal* oldal);
    void oldalTorles();
    const list<string> &getKepek() const;
    void addKep(string eleres);
    Oldal* getJelenlegiOldal() const;
    void setJelenlegiOldal(const unsigned &newJelenlegiOldal);
    Elem* getJelenlegiElem() const;
    void setJelenlegiElem(Elem *newJelenlegiElem);
    bool lapozas(const bool &fel);
    string getEleresiUt() const;
};

#endif // PROJEKT_H
