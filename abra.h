#ifndef ABRA_H
#define ABRA_H

#include "elem.h"

#include <QSize>
#include <QPixmap>

class Abra : public Elem
{
protected:
    QSize meret;
    QPixmap forras;
    unsigned short meretArany;

public:
    Abra(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany);
    const QSize &getMeret() const;
    const QPixmap &getForras() const;
    void setForras(const string &eleres);
    unsigned short getMeretArany() const;
    void setMeretArany(unsigned short newMeretArany);
};

#endif // ABRA_H
