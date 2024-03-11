#include "belyeg.h"

const string &Belyeg::getNev() const
{
    return nev;
}

void Belyeg::setNev(const string &newNev)
{
    nev = newNev;
}

void Belyeg::kepKeszites()
{
    QPixmap ujKep = forras;

    //meretezes
    if(meretArany != 100)
    {
        ujKep = ujKep.scaled(ujKep.width()*(meretArany/100.0), ujKep.height()*(meretArany/100.0), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    //forgatas
    if(dolesszog != 0)
    {
        QSize size = ujKep.size();

        QTransform trans;
        trans.rotate(dolesszog);
        ujKep = ujKep.transformed(trans).scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    //kep gombra helyezese
    kimenet->resize(ujKep.size());
    kimenet->setPixmap(ujKep);
}

Belyeg::Belyeg(const string &nev, const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany) : Abra(meret, forras, xKoordinata, yKoordinata, dolesszog, meretArany),
    nev(nev)
{
    tipus = belyeg;
}

Belyeg::Belyeg(const string &nev, const QSize &meret, const string &eleres, const unsigned int &xKoordinata, const unsigned int &yKoordinata, int dolesszog, unsigned short meretArany) : Abra(meret, eleres, xKoordinata, yKoordinata, dolesszog, meretArany),
    nev(nev)
{
    tipus = belyeg;
}
