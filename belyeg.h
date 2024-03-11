#ifndef BELYEG_H
#define BELYEG_H

#include "abra.h"

class Belyeg : public Abra
{
private:
    string nev;
public:
    Belyeg(const string &nev, const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany);
    Belyeg(const string &nev, const QSize &meret, const string &eleres, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany);
    const string &getNev() const;
    void setNev(const string &newNev);
    void kepKeszites();
};

#endif // BELYEG_H
