#ifndef MINTA_H
#define MINTA_H

#include <string>
#include <QPixmap>

using namespace std;

class Minta
{
private:
    string nev;
    string eleresiUt;
    QPixmap kep;
public:
    Minta(const string &nev, const string &eleresiUt);
    const string &getNev() const;
    void setNev(const string &newNev);
    const string &getEleresiUt() const;
    const QPixmap &getKep() const;
};

#endif // MINTA_H
