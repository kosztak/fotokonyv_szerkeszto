#ifndef OLDAL_H
#define OLDAL_H

#include <list>
#include "stilus.h"
#include "elem.h"
#include "keret.h"
#include "belyeg.h"
#include "szoveg.h"

#include <iostream>

class Oldal
{
private:
    Stilus stilus = Stilus();
    list<Keret*> keretek;
    list<Belyeg*> belyegek;
    list<Szoveg*> szovegek;
    unsigned oldalszam;
public:
    Oldal(const unsigned &oldalszam);
    Stilus *getStilus();
    void stilusAlkalmazas();
    void belyegHozzaadas(Belyeg *ujBelyeg);
    void belyegTorles(Belyeg *belyeg);
    void keretHozzaadas(Keret *ujKeret);
    void keretTorles(Keret *keret);
    void szovegHozzaadas(Szoveg *ujSzoveg);
    void szovegTorles(Szoveg *szoveg);
    unsigned int getOldalszam() const;
    void elemekElrejtese();
    void elemekMutatasa();
};

#endif // OLDAL_H
