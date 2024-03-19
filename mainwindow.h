#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QPushButton>
#include <QPixmap>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QtSvg/QSvgRenderer>
#include <QGraphicsBlurEffect>
#include <QtPrintSupport/QPrinter>
#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <string>
#include <list>
#include <map>

#include "customview.h"
#include "kimenet.h"
#include "projekt.h"
#include "minta.h"
#include "stilus.h"
#include "elrendezes.h"
#include "keretvalaszto.h"
#include "kepvalaszto.h"
#include "elrendezesvalaszto.h"
#include "exportwindow.h"
#include "ujprojekt.h"

#include <iostream>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //rendszer
    void inicializalas();
    void projektekBetoltese();
    void belyegekBetoltese();
    void mintakBetoltese();
    void projektBetoltes();
    void projektBezaras();
    void projektekMentese();
    void belyegekMentese();
    void mintakMentese();
    void projektHozzaadas(string nev, string eleres);
    void belyegHozzaadas(string nev, string eleres);
    void mintaHozzaadas(string nev, string eleres);
    void stilusHozzaadas(Stilus ujStilus);
    map<string, string> getProjektek();
    map<string, string> getBelyegek();
    map<string, string> getMintak();
    void kepFrissites(Keret* ptr);
    void listaFrissites();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_belyegHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_belyegVertikalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_ujSzovegPushButtonSzerkeszto_clicked();

    void on_szovegHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_szovegVertikalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_szovegTextEditSzerkeszto_textChanged();

    void on_betumeretSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_betutipusComboBoxSzerkeszto_currentIndexChanged(int index);

    void on_stilusToolButtonSzerkeszto_clicked();

    void on_kepekToolButtonSzerkeszto_clicked();

    void on_belyegekToolButtonSzerkeszto_clicked();

    void on_betuszinPushButtonSzerkeszto_clicked();

    void on_felkoverCheckBoxSzerkeszto_stateChanged(int arg1);

    void on_doltCheckBoxSzerkeszto_stateChanged(int arg1);

    void on_alahuzottCheckBoxSzerkeszto_stateChanged(int arg1);

    void on_kepHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepVertikalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepSzelessegSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepMagassagSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_keparanyHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_keparanyVertikalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepSzuroComboBoxSzerkeszto_currentIndexChanged(int index);

    void on_kepTorlesPushButtonSzerkeszto_clicked();

    void on_belyegTorlesPushButtonSzerkeszto_clicked();

    void on_szovegTorlesPushButtonSzerkeszto_clicked();

    void on_hatterszinMegvaltoztatPushButtonSzerkeszto_clicked();

    void on_hatterPushButtonSzerkeszto_clicked();

    void on_lapozasLePushButtonSzerkeszto_clicked();

    void on_lapozasFelPushButtonSzerkeszto_clicked();

    void on_keretValasztasPushButtonSzerleszto_clicked();

    void on_egysegeskeretPushButtonSzerkeszto_clicked();

    void on_kepValasztasPushButtonSzerkeszto_clicked();

    void on_elemekToolButtonSzerkeszto_clicked();

    void on_kepElorehozasPushButtonSzerkeszto_clicked();

    void on_kepHatrakuldesPushButtonSzerkeszto_clicked();

    void on_belyegElorehozasPushButtonSzerkeszto_clicked();

    void on_belyegHatrakuldesPushButtonSzerkeszto_clicked();

    void on_szovegElorehozasPushButtonSzerkeszto_clicked();

    void on_szovegHatrakuldesPushButtonSzerkeszto_clicked();

    void on_kepDolesszogSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepMeretSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_belyegDolesszogSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_belyegMeretSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_elrendezesPushButtonSzerkeszto_clicked();

    void on_ujProjektPushButtonFomenu_clicked();

    void on_projektBetoltesePushButtonFomenu_clicked();

    void on_belyegekPushButtonFomenu_clicked();

    void on_mintakPushButtonFomenu_clicked();

    void on_projektTorlesePushButtonFomenu_clicked();

    void on_kilepesPushButtonFomenu_clicked();

    void on_bezarasPushButtonSzerkeszto_clicked();

    void on_ujBelyegPushButtonBelyeg_clicked();

    void on_belyegTorlesePushButtonBelyeg_clicked();

    void on_visszalepesPushButtonBelyeg_clicked();

    void on_ujMintaPushButtonMinta_clicked();

    void on_mintaTorlesePushButtonMinta_clicked();

    void on_visszalepesPushButtonMinta_clicked();

    void on_exportalasPushButtonSzerkeszto_clicked();

    void on_oldalHozaadasPushButtonSzerkeszto_clicked();

    void on_oldalTorlesPushButtonSzerkeszto_clicked();

    void on_kepHozzaadasPushButtonSzerkeszto_clicked();

    void on_mentesPushButtonSzerkeszto_clicked();

private:
    Ui::MainWindow *ui;

    CustomView* graphicsView;
    QWidget* szerkesztoWidget;
    QGraphicsScene* scene;

    string kijeloltElemQSS = "background-color: transparent;"
                             "border-style: dotted;"
                             "border-width: 5px;"
                             "border-color: blue;";

    //rendszer
    Projekt* jelenlegiProjekt = nullptr;
    pair<string, QPushButton*> kivalasztottProjekt = pair<string, QPushButton*>("", nullptr); //eleres, gomb
    map<string, string> projektek; //nev, eleres
    map<string, string> belyegek; //nev, eleres
    map<string, string> mintak; //nev, eleres
    map<string ,Elrendezes> elrendezesek;
    QSvgRenderer keretAlapHatter = QSvgRenderer(QString::fromStdString("./image.svg"));
    map<string, QPushButton*> projektekLista;
    map<Keret*, QPushButton*> kepekLista;
    map<Belyeg*, QPushButton*> belyegekLista;
    map<Szoveg*, QPushButton*> szovegekLista;
    list<QPushButton*> gombok;
    map<string, string> ujKepek; // regi, uj
};
#endif // MAINWINDOW_H
