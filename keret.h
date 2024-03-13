#ifndef KERET_H
#define KERET_H

#include "abra.h"
#include <QPixmap>
#include <QPainter>
#include <QtSvg/QSvgRenderer>

#include <stdio.h>

class Keret : public Abra
{
private:
    unsigned short szelesseg;
    unsigned short magassag;
    unsigned kepXKoordinata;
    unsigned kepYKoordinata;
    unsigned short szuro;
    unsigned short kepKeret;

public:
    Keret(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany, unsigned short szelesseg, unsigned short magassag, unsigned kepXKoordinata, unsigned kepYKoordinata, unsigned short szuro, unsigned short kepKeret);
    Keret(const QSize &meret, const string &eleres, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany, unsigned short szelesseg, unsigned short magassag, unsigned kepXKoordinata, unsigned kepYKoordinata, unsigned short szuro, unsigned short kepKeret);

    void kepKeszites();
    void setKeret(unsigned short index);
    unsigned short getKeret() const;
    void setXKoordinata(int ertek);
    void setYKoordinata(int ertek);
    unsigned short getSzelesseg() const;
    void setSzelesseg(unsigned short newSzelesseg);
    unsigned short getMagassag() const;
    void setMagassag(unsigned short newMagassag);
    unsigned int getKepXKoordinata() const;
    void setKepXKoordinata(unsigned int newKepXKoordinata);
    unsigned int getKepYKoordinata() const;
    void setKepYKoordinata(unsigned int newKepYKoordinata);
    unsigned short getSzuro() const;
    void setSzuro(unsigned short newSzuro);
};

#endif // KERET_H
