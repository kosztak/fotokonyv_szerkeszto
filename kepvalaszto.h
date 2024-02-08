#ifndef KEPVALASZTO_H
#define KEPVALASZTO_H

#include <QDialog>
#include <QPixmap>
#include <list>
#include <string>

namespace Ui {
class kepValaszto;
}

using namespace std;

class KepValaszto : public QDialog
{
    Q_OBJECT

    //rendszer
    void inicializalas();

public:
    explicit KepValaszto(QWidget *parent = nullptr, list<string> lista = list<string>());
    ~KepValaszto();
    string getJelenlegiKep();

private slots:
    void on_valasztPushButton_clicked();

    void on_megsePushButton_clicked();

private:
    Ui::kepValaszto *ui;

    //rendszer
    string jelenlegiKep = "";
    list<string> kepLista;
};

#endif // KEPVALASZTO_H
