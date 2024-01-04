#ifndef SZOVEG_H
#define SZOVEG_H

#include "elem.h"

#include <QColor>
#include <QFont>

class Szoveg : public Elem
{
private:
    string tartalom;
    QColor szin;
    QFont betutipus;
public:
    Szoveg(const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog);

    const string &getTartalom() const;
    void setTartalom(const string &newTartalom);
    const QColor &getSzin() const;
    void setSzin(const QColor &newSzin);
    const QFont &getBetutipus() const;
    void setBetutipus(const string &nev);
    unsigned getMeret() const;
    void setMeret(unsigned ujMeret);
    bool isFelkover() const;
    void setFelkover(bool ertek);
    bool isDolt() const;
    void setDolt(bool ertek);
};

#endif // SZOVEG_H
