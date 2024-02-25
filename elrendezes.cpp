#include "elrendezes.h"

const unsigned &Elrendezes::getKepekSzama() const
{
    return kepekSzama;
}

const list<pair<QPoint, QSize>> &Elrendezes::getElhelyezkedesek() const
{
    return elhelyezkedesek;
}

Elrendezes::Elrendezes(unsigned int kepekSzama, const list<pair<QPoint, QSize>> &elhelyezkedesek) : kepekSzama(kepekSzama),
    elhelyezkedesek(elhelyezkedesek)
{}
