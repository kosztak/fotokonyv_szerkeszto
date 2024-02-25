#ifndef STILUS_H
#define STILUS_H

#include <QColor>
#include "minta.h"

class Stilus
{
private:
    bool hatterTipus = 0; //0 = szin, 1 = minta
    Minta minta = Minta("", "", QPixmap());
    QColor szin = Qt::white;
public:
    Stilus();
    bool getHatterTipus() const;
    void setHatterTipus(bool newHatterTipus);
    Minta getMinta() const;
    void setMinta(Minta newMinta);
    const QColor &getSzin() const;
    void setSzin(const QColor &newSzin);
};

#endif // STILUS_H
