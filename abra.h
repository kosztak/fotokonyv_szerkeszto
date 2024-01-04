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

public:
    Abra(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog);
    void meretezes(unsigned szelesseg, unsigned hosszusag);
    const QSize &getMeret() const;
    const QPixmap &getForras() const;
    void setForras(const string &eleres);
};

#endif // ABRA_H
