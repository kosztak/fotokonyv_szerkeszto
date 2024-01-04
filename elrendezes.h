#ifndef ELRENDEZES_H
#define ELRENDEZES_H

#include <list>

using namespace std;

class Elrendezes
{
private:
    unsigned kepekSzama;
    list<pair<unsigned, unsigned>> koordinatak;
public:
    Elrendezes();
    const unsigned &getKepekSzama() const;
    const list<pair<unsigned, unsigned> > &getKoordinatak() const;
};

#endif // ELRENDEZES_H
