#ifndef BELYEG_H
#define BELYEG_H

#include "abra.h"

class Belyeg : public Abra
{
private:
    string nev;
public:
    Belyeg(const string &nev, const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog);

    const string &getNev() const;
    void setNev(const string &newNev);
};

#endif // BELYEG_H
