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
    unsigned getMeret() const;
    void setMeret(unsigned ujMeret);
    bool isFelkover() const;
    void setFelkover(bool ertek);
    bool isDolt() const;
    void setDolt(bool ertek);
    void setBetutipus(const QFont &newBetutipus);
};

#endif // SZOVEG_H
