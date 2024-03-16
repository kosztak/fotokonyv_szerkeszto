#ifndef UJPROJEKT_H
#define UJPROJEKT_H

#include <QDialog>
#include <QMessageBox>
#include <string>
#include <map>

using namespace std;

namespace Ui {
class UjProjekt;
}

class UjProjekt : public QDialog
{
    Q_OBJECT

public:
    explicit UjProjekt(QWidget *parent = nullptr, map<string, string> projektek = map<string, string>());
    ~UjProjekt();

    string getNev() const;

    unsigned short getOldalszam() const;

private slots:
    void on_megsePushButton_clicked();

    void on_letrehozasPushButton_clicked();

private:
    Ui::UjProjekt *ui;

    map<string, string> projektek;
    string nev;
    unsigned short oldalszam;
};

#endif // UJPROJEKT_H
