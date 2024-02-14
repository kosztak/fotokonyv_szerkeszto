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

    //meretezes
    if(meretArany != 100)
    {
        QPixmap ujKep = forras;

        ujKep = ujKep.scaled(ujKep.width()*(meretArany/100.0), ujKep.height()*(meretArany/100.0), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        //kep gombra helyezese
        kimenet->resize(ujKep.size());
        kimenet->setPixmap(ujKep);
    }
}

Belyeg::Belyeg(const string &nev, const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany) : Abra(meret, forras, xKoordinata, yKoordinata, dolesszog, meretArany),
    nev(nev)
{
    tipus = belyeg;
}
