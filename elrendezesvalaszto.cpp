#include "elrendezesvalaszto.h"
#include "ui_elrendezesvalaszto.h"

void ElrendezesValaszto::inicializalas()
{
    int counter = 0;
    for(auto i : elrendezesek)
    {
        if(i.second.getKepekSzama() == ui->kepekSzamaSpinBox->value())
        {
            QPushButton *tempbutton = new QPushButton;
            gombok.push_back(tempbutton);
            QPixmap pixmap(QString::fromStdString("./elrendezesek/" + i.first + ".png"));

            tempbutton->setIconSize(QSize(140, 200));
            tempbutton->setIcon(pixmap);

            ui->gridLayout->addWidget(tempbutton, counter/2, counter%2);

            ++counter;

            //funkcio hozzaadas a kep gombnak
            connect(tempbutton, &QPushButton::clicked, [=]{
                valasztas = i.first;
                accept();
            });
        }
    }
}

ElrendezesValaszto::ElrendezesValaszto(QWidget *parent, map<string, Elrendezes> elrendezesek, unsigned minimum)
    : QDialog(parent)
    , ui(new Ui::ElrendezesValaszto)
    , elrendezesek(elrendezesek)
    ,minimum(minimum)
{
    ui->setupUi(this);

    if(minimum != 0)
        ui->kepekSzamaSpinBox->setMinimum(minimum);

    inicializalas();
}

ElrendezesValaszto::~ElrendezesValaszto()
{
    delete ui;
}

void ElrendezesValaszto::on_megsePushButton_clicked()
{
    reject();
}

string ElrendezesValaszto::getValasztas() const
{
    return valasztas;
}

void ElrendezesValaszto::on_kepekSzamaSpinBox_valueChanged(int arg1)
{
    for(auto i: gombok)
    {
        delete i;
    }

    gombok.clear();

    inicializalas();
}
