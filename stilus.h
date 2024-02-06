#ifndef STILUS_H
#define STILUS_H

#include <QColor>
#include "elrendezes.h"
#include "minta.h"

class Stilus
{
private:
    Elrendezes elrendezes;
    bool elrendezesAktiv = 0;
    bool hatterTipus = 0; //0 = szin, 1 = minta
    Minta minta = Minta("", "", QPixmap());
    QColor szin = Qt::white;
public:
    Stilus();
    void setAktiv(bool ertek);
    const Elrendezes &getElrendezes() const;
    void setElrendezes(Elrendezes uj);
    bool getElrendezesAktiv() const;
    void setElrendezesAktiv(bool ertek);
    bool getHatterTipus() const;
    void setHatterTipus(bool newHatterTipus);
    Minta getMinta() const;
    void setMinta(Minta newMinta);
    const QColor &getSzin() const;
    void setSzin(const QColor &newSzin);
};

#endif // STILUS_H
