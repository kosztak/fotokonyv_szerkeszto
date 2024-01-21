#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //stacked widget beallitas
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->stilusPageSzerkeszto);
    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    //inicializalas
    inicializalas();

    //belyegek betoltese
    int counter = 0;
    for(auto i : belyegek)
    {
        QPushButton *tempbutton = new QPushButton;
        tempbutton->setAutoFillBackground(true);
        QPixmap pixmap(QString::fromStdString(i.second));

        QIcon icon(pixmap);
        tempbutton->setIcon(icon);
        tempbutton->setIconSize(QSize(60, 60));

        ui->belyegekGridLayoutSzerkeszto->addWidget(tempbutton, counter/2, counter%2);

        ++counter;

        //funkcio hozzaadas a belyeg gombnak
        connect(tempbutton, &QPushButton::clicked, [=]{
            Belyeg *ujBelyeg = new Belyeg(i.first, pixmap.size(), pixmap, 0, 0, 0, 100);
            ujBelyeg->getKimenet()->setParent(ui->szerkesztoWidgetSzerkeszto);
            ujBelyeg->getKimenet()->setIcon(pixmap);
            ujBelyeg->getKimenet()->setIconSize(pixmap.size());
            ujBelyeg->getKimenet()->resize(pixmap.size());
            ujBelyeg->getKimenet()->show();

            connect(ujBelyeg->getKimenet(), &QPushButton::clicked, [=]{
                ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegPageSzerkeszto);

                jelenlegiProjekt.setJelenlegiElem(ujBelyeg);

                //horizontalis mozgatas
                ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - ujBelyeg->getKimenet()->width());
                ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(ujBelyeg->getKimenet()->x());

                //vertikalis mozgatas
                ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - ujBelyeg->getKimenet()->height());
                ui->belyegVertikalisSpinBoxSzerkeszto->setValue(ujBelyeg->getKimenet()->y());

                //meretezes
                ui->belyegMeretHorizontalSliderSzerkeszto->setValue(ujBelyeg->getMeretArany());
            });

            jelenlegiProjekt.getJelenlegiOldal()->belyegHozzaadas(ujBelyeg);
        });
    }

    //kepek betoltese
    counter = 0;
    list<string> kepLista = jelenlegiProjekt.getKepek();

    for(string i : kepLista)
    {
        QPushButton *tempbutton = new QPushButton;
        QPixmap pixmap(QString::fromStdString(i));

        QIcon icon(pixmap);
        tempbutton->setIcon(icon);
        tempbutton->setIconSize(QSize(60, 60));

        ui->kepekGridLayoutSzerkeszto->addWidget(tempbutton, counter/2, counter%2);

        ++counter;

        //funkcio hozzaadas a kep gombnak
        connect(tempbutton, &QPushButton::clicked, [=]{
            Keret *ujKeret = new Keret(pixmap.size(), pixmap, 0, 0, 0, 100, 100, 100, 0, 0);
            ujKeret->getKimenet()->setParent(ui->szerkesztoWidgetSzerkeszto);
            ujKeret->getKimenet()->setIcon(pixmap);
            ujKeret->getKimenet()->setIconSize(pixmap.size());
            ujKeret->getKimenet()->resize(pixmap.size());
            ujKeret->getKimenet()->show();

            connect(ujKeret->getKimenet(), &QPushButton::clicked, [=]{
                ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

                jelenlegiProjekt.setJelenlegiElem(ujKeret);

                //horizontalis mozgatas
                ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - ujKeret->getKimenet()->width());
                ui->kepHorizontalisSpinBoxSzerkeszto->setValue(ujKeret->getKimenet()->x());

                //vertikalis mozgatas
                ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - ujKeret->getKimenet()->height());
                ui->kepVertikalisSpinBoxSzerkeszto->setValue(ujKeret->getKimenet()->y());

                //meretezes
                ui->kepMeretHorizontalSliderSzerkeszto->setValue(ujKeret->getMeretArany());

                //aranyok
                ui->kepSzelessegSpinBoxSzerkeszto->setValue(ujKeret->getSzelesseg());
                ui->kepMagassagSpinBoxSzerkeszto->setValue(ujKeret->getMagassag());
            });

            jelenlegiProjekt.getJelenlegiOldal()->keretHozzaadas(ujKeret);
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stilusPushButtonSzerkeszto_clicked()
{
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->stilusPageSzerkeszto);
}


void MainWindow::on_kepekPushButtonSzerkeszto_clicked()
{
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->kepekPageSzerkeszto);
}


void MainWindow::on_belyegekPushButtonSzerkeszto_clicked()
{
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegekPageSzerkeszto);
}

//rendszer
void MainWindow::inicializalas()
{
    //belyegek
    belyegek["ball"] = "./belyegek/ball.png";
    belyegek["dog"] = "./belyegek/dog.png";

    //mintak
    mintak["beige"] = "./mintak/beige.jpg";
    mintak["blue"] = "./mintak/blue.png";

    //projekt
    jelenlegiProjekt = Projekt();

    //kepek
    jelenlegiProjekt.addKep("./kepek/cat.jpg");
    jelenlegiProjekt.addKep("./kepek/flower.png");
}

map<string, string> MainWindow::getProjektek()
{
    return projektek;
}

map<string, string> MainWindow::getBelyegek()
{
    return belyegek;
}

map<string, string> MainWindow::getMintak()
{
    return mintak;
}

void MainWindow::on_belyegHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->move(arg1, jelenlegiProjekt.getJelenlegiElem()->getKimenet()->y()); //x, y
}


void MainWindow::on_belyegVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->move(jelenlegiProjekt.getJelenlegiElem()->getKimenet()->x(), arg1); //x, y
}


void MainWindow::on_ujSzovegPushButtonSzerkeszto_clicked()
{
    Szoveg *ujSzoveg = new Szoveg(0, 0, 0);
    ujSzoveg->getKimenet()->setParent(ui->szerkesztoWidgetSzerkeszto);
    ujSzoveg->getKimenet()->setText(QString::fromStdString(ujSzoveg->getTartalom()));
    ujSzoveg->getKimenet()->show();

    connect(ujSzoveg->getKimenet(), &QPushButton::clicked, [=]{
        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->szovegPageSzerkeszto);

        jelenlegiProjekt.setJelenlegiElem(ujSzoveg);

        //szoveg
        ui->szovegTextEditSzerkeszto->setText(QString::fromStdString(ujSzoveg->getTartalom()));

        //horizontalis mozgatas
        ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - ujSzoveg->getKimenet()->width());
        ui->szovegHorizontalisSpinBoxSzerkeszto->setValue(ujSzoveg->getKimenet()->x());

        //vertikalis mozgatas
        ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - ujSzoveg->getKimenet()->height());
        ui->szovegVertikalisSpinBoxSzerkeszto->setValue(ujSzoveg->getKimenet()->y());

        //betumeret
        ui->betumeretSpinBoxSzerkeszto->setValue(ujSzoveg->getKimenet()->font().pointSize());
    });

    jelenlegiProjekt.getJelenlegiOldal()->szovegHozzaadas(ujSzoveg);

    QFont font = ujSzoveg->getKimenet()->font();
    font.setFamily(QString("Arial"));
    ujSzoveg->getKimenet()->setFont(font);
}

void MainWindow::on_szovegHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->move(arg1, jelenlegiProjekt.getJelenlegiElem()->getKimenet()->y()); //x, y
}


void MainWindow::on_szovegVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->move(jelenlegiProjekt.getJelenlegiElem()->getKimenet()->x(), arg1); //x, y
}


void MainWindow::on_szovegTextEditSzerkeszto_textChanged()
{
    //tartalom beallitas
    dynamic_cast<Szoveg*>(jelenlegiProjekt.getJelenlegiElem())->setTartalom(ui->szovegTextEditSzerkeszto->toPlainText().toStdString());

    //gomb meret beallitas
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->adjustSize();

    //mozgatas
    ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiProjekt.getJelenlegiElem()->getKimenet()->width());
    ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiProjekt.getJelenlegiElem()->getKimenet()->height());
}


void MainWindow::on_betumeretSpinBoxSzerkeszto_valueChanged(int arg1)
{
    QFont font = jelenlegiProjekt.getJelenlegiElem()->getKimenet()->font();
    font.setPointSize(arg1);
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setFont(font);
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->adjustSize();

    //mozgatas
    ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiProjekt.getJelenlegiElem()->getKimenet()->width());
    ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiProjekt.getJelenlegiElem()->getKimenet()->height());
}


void MainWindow::on_betutipusComboBoxSzerkeszto_currentIndexChanged(int index)
{
    QFont font = jelenlegiProjekt.getJelenlegiElem()->getKimenet()->font();
    font.setFamily(ui->betutipusComboBoxSzerkeszto->currentText());
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setFont(font);

    //gomb meretezes
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->adjustSize();

    //mozgatas
    ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiProjekt.getJelenlegiElem()->getKimenet()->width());
    ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiProjekt.getJelenlegiElem()->getKimenet()->height());
}

void MainWindow::on_belyegMeretHorizontalSliderSzerkeszto_valueChanged(int value)
{
    //meret arany megvaltoztatasa
    Belyeg* jelenlegiBelyeg = dynamic_cast<Belyeg*>(jelenlegiProjekt.getJelenlegiElem());
    jelenlegiBelyeg->setMeretArany(value);

    //belyeg meretenek megvaltoztatasa
    QPushButton* jelenlegiButton = jelenlegiBelyeg->getKimenet();
    QSize jelenlegiMeret = jelenlegiBelyeg->getMeret();
    jelenlegiMeret.setWidth((jelenlegiMeret.width()/100.0)*value);
    jelenlegiMeret.setHeight((jelenlegiMeret.height()/100.0)*value);

    jelenlegiButton->resize(jelenlegiMeret);
    jelenlegiButton->setIconSize(jelenlegiMeret);

    //tooltip beallitas
    ui->belyegMeretHorizontalSliderSzerkeszto->setToolTip(QString::number(value));

    //horizontalis mozgatas
    ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiButton->width());
    ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(jelenlegiButton->x());

    //vertikalis mozgatas
    ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiButton->height());
    ui->belyegVertikalisSpinBoxSzerkeszto->setValue(jelenlegiButton->y());
}


void MainWindow::on_betuszinPushButtonSzerkeszto_clicked()
{
    QColor ujSzin = QColorDialog::getColor(Qt::black, this, "Betűszín Választó");

    //betuszin
    QPalette betuPal = jelenlegiProjekt.getJelenlegiElem()->getKimenet()->palette();
    betuPal.setColor(QPalette::ButtonText, ujSzin);
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setPalette(betuPal);

    //hatterszin
    // QPalette hatterPal = ui->betuszinWidgetSzerkeszto->palette();
    // hatterPal.setColor(QPalette::Window, ujSzin);
    // ui->betuszinWidgetSzerkeszto->setAutoFillBackground(true);
    // ui->betuszinWidgetSzerkeszto->setPalette(hatterPal);
    // ui->betuszinWidgetSzerkeszto->show();
}

void MainWindow::on_felkoverCheckBoxSzerkeszto_stateChanged(int arg1)
{
    QFont font = jelenlegiProjekt.getJelenlegiElem()->getKimenet()->font();
    font.setBold(arg1);
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setFont(font);
}


void MainWindow::on_doltCheckBoxSzerkeszto_stateChanged(int arg1)
{
    QFont font = jelenlegiProjekt.getJelenlegiElem()->getKimenet()->font();
    font.setItalic(arg1);
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setFont(font);
}


void MainWindow::on_alahuzottCheckBoxSzerkeszto_stateChanged(int arg1)
{
    QFont font = jelenlegiProjekt.getJelenlegiElem()->getKimenet()->font();
    font.setUnderline(arg1);
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setFont(font);
}


void MainWindow::on_kepHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->move(arg1, jelenlegiProjekt.getJelenlegiElem()->getKimenet()->y()); //x, y
}


void MainWindow::on_kepVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->move(jelenlegiProjekt.getJelenlegiElem()->getKimenet()->x(), arg1); //x, y
}


void MainWindow::on_kepMeretHorizontalSliderSzerkeszto_valueChanged(int value)
{
    //meret arany megvaltoztatasa
    Keret* jelenlegiKep = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());
    jelenlegiKep->setMeretArany(value);

    //kep meretenek megvaltoztatasa
    QPushButton* jelenlegiButton = jelenlegiKep->getKimenet();
    QSize jelenlegiMeret = jelenlegiKep->getMeret();
    jelenlegiMeret.setWidth((jelenlegiMeret.width()/100.0)*value);
    jelenlegiMeret.setHeight((jelenlegiMeret.height()/100.0)*value);

    jelenlegiButton->resize(QSize(jelenlegiMeret.width()*(jelenlegiKep->getSzelesseg()/100.0), jelenlegiMeret.height()*(jelenlegiKep->getMagassag()/100.0)));
    jelenlegiButton->setIconSize(jelenlegiMeret);

    //tooltip beallitas
    ui->kepMeretHorizontalSliderSzerkeszto->setToolTip(QString::number(value));

    //horizontalis mozgatas
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiButton->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(jelenlegiButton->x());

    //vertikalis mozgatas
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiButton->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(jelenlegiButton->y());
}

void MainWindow::on_kepSzelessegSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setSzelesseg(arg1);

    jelenlegiKeret->getKimenet()->resize(QSize(jelenlegiKeret->getMeret().width()*(arg1/100.0), jelenlegiKeret->getMeret().height()*(jelenlegiKeret->getMagassag()/100.0)));

    //horizontalis mozgatas
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiKeret->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(jelenlegiKeret->getKimenet()->x());

    //vertikalis mozgatas
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiKeret->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(jelenlegiKeret->getKimenet()->y());
}

void MainWindow::on_kepMagassagSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setMagassag(arg1);

    jelenlegiKeret->getKimenet()->resize(QSize(jelenlegiKeret->getMeret().width()*(jelenlegiKeret->getSzelesseg()/100.0), jelenlegiKeret->getMeret().height()*(arg1/100.0)));

    //horizontalis mozgatas
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiKeret->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(jelenlegiKeret->getKimenet()->x());

    //vertikalis mozgatas
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiKeret->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(jelenlegiKeret->getKimenet()->y());
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setXKoordinata(arg1);

    jelenlegiKeret->kepKeszites();
}
