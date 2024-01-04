#ifndef MINTA_H
#define MINTA_H

#include <string>
#include <QImage>

using namespace std;

class Minta
{
private:
    string nev;
    string eleresiUt;
    QImage kep;
public:
    Minta(const string &nev, const string &eleresiUt, const QImage &kep);
    const string &getNev() const;
    void setNev(const string &newNev);
    const string &getEleresiUt() const;
    const QImage &getKep() const;
};

#endif // MINTA_H
