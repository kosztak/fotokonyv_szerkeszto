#include "ujprojekt.h"
#include "ui_ujprojekt.h"

UjProjekt::UjProjekt(QWidget *parent, map<string, string> projketek)
    : QDialog(parent)
    , ui(new Ui::UjProjekt)
    , projektek(projketek)
{
    ui->setupUi(this);
}

UjProjekt::~UjProjekt()
{
    delete ui;
}

string UjProjekt::getNev() const
{
    return nev;
}

unsigned short UjProjekt::getOldalszam() const
{
    return oldalszam;
}

void UjProjekt::on_megsePushButton_clicked()
{
    reject();
}


void UjProjekt::on_letrehozasPushButton_clicked()
{
    if(ui->nevLineEdit->text() != "")
    {
        if(projektek.count(ui->nevLineEdit->text().toStdString()) == 0)
        {
            nev = ui->nevLineEdit->text().toStdString();
            oldalszam = ui->oldalszamSpinBox->value();

            accept();
        }else{
            QMessageBox::warning(this, "Figyelem!", "A megadott névvel már létezik projekt!");
        }

    }else{
        QMessageBox::warning(this, "Figyelem!", "Nem lett megadva név!");
    }
}

