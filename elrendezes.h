#ifndef ELRENDEZES_H
#define ELRENDEZES_H

#include <list>
#include <QPoint>
#include <QSize>

using namespace std;

class Elrendezes
{
private:
    unsigned kepekSzama;
    list<pair<QPoint, QSize>> elhelyezkedesek;
public:
    Elrendezes(unsigned int kepekSzama, const list<pair<QPoint, QSize>> &elhelyezkedesek);
    const unsigned &getKepekSzama() const;
    const list<pair<QPoint, QSize>> &getElhelyezkedesek() const;
};

#endif // ELRENDEZES_H
