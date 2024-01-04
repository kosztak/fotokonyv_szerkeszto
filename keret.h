#ifndef KERET_H
#define KERET_H

#include "abra.h"

#include <QPixmap>

class Keret : public Abra
{
private:
    unsigned kepKeret;
    QPixmap kep;
    int forrasXKoordinata;
    int forrasYKoordinata;
public:
    Keret(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog);
    void kepKeszites();
    const QPixmap &getKep() const;
    void setKeret(unsigned index);
    void setXKoordinata(int ertek);
    void setYKoordinata(int ertek);
};

#endif // KERET_H
