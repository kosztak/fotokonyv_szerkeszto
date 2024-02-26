#ifndef ELEM_H
#define ELEM_H

#include <string>
#include <kimenet.h>

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
    int dolesszog;
    ElemTipus tipus;
    Kimenet *kimenet = new Kimenet();

public:
    Elem(unsigned xKoordinata, unsigned yKoordinata, int dolesszog);
    virtual ~Elem(){delete kimenet;};
    void forgatas(int szog);
    int getDolesszog() const;
    ElemTipus getTipus() const;
    Kimenet *getKimenet() const;
    virtual void semmi(){}
};

#endif // ELEM_H
