#include "kepvalaszto.h"
#include "ui_kepvalaszto.h"

KepValaszto::KepValaszto(QWidget *parent, list<string> lista)
    : QDialog(parent)
    , ui(new Ui::kepValaszto),
    kepLista(lista)
{
    ui->setupUi(this);

    inicializalas();
}

void KepValaszto::inicializalas()
{
    int counter = 0;
    for(auto i : kepLista)
    {
        QPushButton *tempbutton = new QPushButton;
        tempbutton->setStyleSheet("background-color: #ffffff; border: 3px outset #c2c2c2;");
        QPixmap pixmap(QString::fromStdString(i));

        tempbutton->setIconSize(QSize(128, 128));
        tempbutton->setIcon(pixmap);

        ui->kepekGridLayout->addWidget(tempbutton, counter/3, counter%3);

        ++counter;
        //funkcio hozzaadas a kep gombnak
        connect(tempbutton, &QPushButton::clicked, [=]{
            if(jelenlegiButton != nullptr)
            {
                jelenlegiButton->setStyleSheet("background-color: #ffffff; border: 3px outset #c2c2c2;");
            }
            jelenlegiButton = tempbutton;
            tempbutton->setStyleSheet("background-color: #ffffff; border: 3px inset #c2c2c2;");

            jelenlegiKep = i;
        });
    }
}

KepValaszto::~KepValaszto()
{
    delete ui;
}

string KepValaszto::getJelenlegiKep()
{
    return jelenlegiKep;
}

void KepValaszto::on_valasztPushButton_clicked()
{
    accept();
}


void KepValaszto::on_megsePushButton_clicked()
{
    reject();
}
