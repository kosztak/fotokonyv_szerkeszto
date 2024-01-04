#ifndef RENDSZER_H
#define RENDSZER_H

#include <QImage>
#include <string>
#include <list>
#include <map>
#include "projekt.h"
#include "minta.h"
#include "stilus.h"
#include "elrendezes.h"

class Rendszer
{
private:
    static Projekt jelenlegiProjekt;
    static map<string, string> projektek;
    static map<string, string> belyegek;
    static map<string, string> mintak;
    static list<QImage> kepKeretek;
    static list<Stilus> stilusok;
    static list<Elrendezes> elrendezesek;
    static QImage keretAlapHatter;
public:
    static void inicializalas(){
        //belyegek
        belyegek["ball"] = "/belyegek/ball.png";
        belyegek["dog"] = "/belyegek/dog.png";

        //mintak
        mintak["beige"] = "mintak/beige.jpg";
        mintak["blue"] = "mintak/blue.png";

        //projekt
        jelenlegiProjekt = Projekt();
    }
    static void projektekBetoltese(){}
    static void belyegekBetoltese(){}
    static void mintakBetoltese(){}
    static void projektBetoltes(){}
    static void projektBezaras(){}
    static void projektekMentese(){}
    static void belyegekMentese(){}
    static void mintakMentese(){}
    static void projektHozzaadas(string nev, string eleres){}
    static void belyegHozzaadas(string nev, string eleres){}
    static void mintaHozzaadas(string nev, string eleres){}
    static void stilusHozzaadas(Stilus ujStilus){}
    static map<string, string> getProjektek(){
        return projektek;
    };
    static map<string, string> getBelyegek(){
        return belyegek;
    };
    static map<string, string> getMintak(){
        return mintak;
    };
};

#endif // RENDSZER_H
