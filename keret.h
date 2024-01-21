#ifndef KERET_H
#define KERET_H

#include "abra.h"

#include <QPixmap>

class Keret : public Abra
{
private:
    unsigned kepKeret;
    QPixmap kep;
    unsigned kepXKoordinata;
    unsigned kepYKoordinata;
    unsigned short szelesseg;
    unsigned short magassag;

public:
    Keret(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany, unsigned short szelesseg, unsigned short magassag, unsigned kepXKoordinata, unsigned kepYKoordinata);
    void kepKeszites();
    const QPixmap &getKep() const;
    void setKeret(unsigned index);
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
};

#endif // KERET_H
