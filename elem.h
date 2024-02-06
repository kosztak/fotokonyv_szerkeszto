#ifndef ELEM_H
#define ELEM_H

#include <string>
#include <QPushButton>

using namespace std;

enum ElemTipus
{
    belyeg,
    keret,
    szoveg
};

class Elem
{
protected:
    unsigned xKoordinata;
    unsigned yKoordinata;
    int dolesszog;
    ElemTipus tipus;
    QPushButton *kimenet = new QPushButton();

public:
    Elem(unsigned xKoordinata, unsigned yKoordinata, int dolesszog);
    virtual ~Elem(){delete kimenet;};
    void mozgatas(unsigned xPont, unsigned yPont);
    const unsigned &getXKoordinata() const;
    const unsigned &getYKoordinata() const;
    void forgatas(int szog);
    int getDolesszog() const;
    ElemTipus getTipus() const;
    QPushButton *getKimenet() const;
    virtual void semmi(){}
};

#endif // ELEM_H
