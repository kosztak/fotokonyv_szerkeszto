#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPushButton>
#include <QPixmap>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <string>
#include <list>
#include <map>
#include "projekt.h"
#include "minta.h"
#include "stilus.h"
#include "elrendezes.h"

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

    void on_stilusPushButtonSzerkeszto_clicked();

    void on_kepekPushButtonSzerkeszto_clicked();

    void on_belyegekPushButtonSzerkeszto_clicked();

    void on_belyegMeretHorizontalSliderSzerkeszto_valueChanged(int value);

    void on_betuszinPushButtonSzerkeszto_clicked();

    void on_felkoverCheckBoxSzerkeszto_stateChanged(int arg1);

    void on_doltCheckBoxSzerkeszto_stateChanged(int arg1);

    void on_alahuzottCheckBoxSzerkeszto_stateChanged(int arg1);

    void on_kepHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepVertikalisSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepMeretHorizontalSliderSzerkeszto_valueChanged(int value);

    void on_kepSzelessegSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_kepMagassagSpinBoxSzerkeszto_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    //rendszer
    Projekt jelenlegiProjekt;
    map<string, string> projektek; //nev, eleres
    map<string, string> belyegek; //nev, eleres
    map<string, string> mintak; //nev, eleres
    list<QImage> kepKeretek;
    list<Stilus> stilusok;
    list<Elrendezes> elrendezesek;
    QImage keretAlapHatter;
};
#endif // MAINWINDOW_H
