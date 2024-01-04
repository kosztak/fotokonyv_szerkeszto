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
    Stilus stilus;
    list<Keret> keretek;
    list<Belyeg> belyegek;
    list<Szoveg> szovegek;
public:
    Oldal();
    void stilusAlkalmazas();
    void belyegHozzaadas(Belyeg *ujBelyeg);
    void belyegTorles(Belyeg *belyeg);
    void keretHozzaadas(Keret *ujKeret);
    void keretTorles(Keret *keret);
    void szovegHozzaadas(Szoveg *ujSzoveg);
    void szovegTorles(Szoveg *szoveg);
};

#endif // OLDAL_H
