#ifndef ELRENDEZESVALASZTO_H
#define ELRENDEZESVALASZTO_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QPoint>
#include <QSize>
#include <string>
#include <map>
#include <list>

#include "elrendezes.h"

using namespace std;

namespace Ui {
class ElrendezesValaszto;
}

class ElrendezesValaszto : public QDialog
{
    Q_OBJECT

    //rendszer
    void inicializalas();

public:
    explicit ElrendezesValaszto(QWidget *parent = nullptr, map<string, Elrendezes> elrendezesek = map<string, Elrendezes>(), unsigned minimum = 1);
    ~ElrendezesValaszto();

    string getValasztas() const;

private slots:
    void on_megsePushButton_clicked();

    void on_kepekSzamaSpinBox_valueChanged(int arg1);

private:
    Ui::ElrendezesValaszto *ui;

    //rendszer
    list<QPushButton*> gombok;
    string valasztas = "";
    map<string ,Elrendezes> elrendezesek;
    unsigned minimum;
};

#endif // ELRENDEZESVALASZTO_H
