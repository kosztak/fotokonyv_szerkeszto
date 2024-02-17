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

    //belyegek betoltese szerkesztobe
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
            ujBelyeg->getKimenet()->setStyleSheet("background-color: transparent");
            ujBelyeg->getKimenet()->setParent(ui->szerkesztoWidgetSzerkeszto);
            ujBelyeg->getKimenet()->setPixmap(pixmap);
            ujBelyeg->getKimenet()->resize(pixmap.size());
            ujBelyeg->getKimenet()->resize(pixmap.size());
            ujBelyeg->getKimenet()->show();

            connect(ujBelyeg->getKimenet(), &Kimenet::clicked, [=]{
                ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegPageSzerkeszto);

                if(jelenlegiProjekt.getJelenlegiElem() != nullptr)
                {
                    if(jelenlegiProjekt.getJelenlegiElem()->getTipus() != szoveg)
                    {
                        jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                    }else{
                        QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt.getJelenlegiElem())->getSzin();
                        jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                    }
                }

                jelenlegiProjekt.setJelenlegiElem(ujBelyeg);
                ujBelyeg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));

                //horizontalis mozgatas
                unsigned xPont = ujBelyeg->getKimenet()->x();
                ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - ujBelyeg->getKimenet()->width());
                ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                //vertikalis mozgatas
                unsigned yPont = ujBelyeg->getKimenet()->y();
                ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - ujBelyeg->getKimenet()->height());
                ui->belyegVertikalisSpinBoxSzerkeszto->setValue(yPont);

                //meretezes
                ui->belyegMeretHorizontalSliderSzerkeszto->setValue(ujBelyeg->getMeretArany());
            });

            jelenlegiProjekt.getJelenlegiOldal()->belyegHozzaadas(ujBelyeg);
        });
    }

    //mintak betoltese szerkesztobe
    counter = 0;
    for(auto i : mintak)
    {
        QPushButton *tempbutton = new QPushButton;
        tempbutton->setAutoFillBackground(true);
        QPixmap pixmap(QString::fromStdString(i.second));

        QIcon icon(pixmap);
        tempbutton->setIcon(icon);
        tempbutton->setIconSize(QSize(100, 100));

        ui->mintakGridLayoutSzerkeszto->addWidget(tempbutton, counter/2, counter%2);

        ++counter;

        //funkcio hozzaadas a minta gombnak
        connect(tempbutton, &QPushButton::clicked, [=]{
            Minta ujMinta = Minta(i.first, i.second, pixmap);

            jelenlegiProjekt.getJelenlegiOldal()->getStilus()->setMinta(ujMinta);
            jelenlegiProjekt.getJelenlegiOldal()->getStilus()->setHatterTipus(1);

            ui->szerkesztoWidgetSzerkeszto->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidgetSzerkeszto{border-image: url(" + i.second + ") 0 0 0 0 stretch stretch;}"));
        });
    }

    //kepek betoltese szerkesztobe
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
            Keret *ujKeret = new Keret(pixmap.size(), pixmap, 0, 0, 0, 100, 100, 100, 0, 0, 0, 0);
            ujKeret->getKimenet()->setStyleSheet("background-color: transparent");
            ujKeret->getKimenet()->setParent(ui->szerkesztoWidgetSzerkeszto);
            ujKeret->getKimenet()->setPixmap(pixmap);
            ujKeret->getKimenet()->resize(pixmap.size());
            ujKeret->getKimenet()->resize(pixmap.size());
            ujKeret->getKimenet()->show();

            connect(ujKeret->getKimenet(), &Kimenet::clicked, [=]{
                ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

                if(jelenlegiProjekt.getJelenlegiElem() != nullptr)
                {
                    if(jelenlegiProjekt.getJelenlegiElem()->getTipus() != szoveg)
                    {
                        jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                    }else{
                        QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt.getJelenlegiElem())->getSzin();
                        jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                    }
                }

                jelenlegiProjekt.setJelenlegiElem(ujKeret);
                ujKeret->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));


                //horizontalis mozgatas
                unsigned xPont = ujKeret->getKimenet()->x();
                ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - ujKeret->getKimenet()->width());
                ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                //vertikalis mozgatas
                unsigned yPont = ujKeret->getKimenet()->y();
                ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - ujKeret->getKimenet()->height());
                ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

                //meretezes
                ui->kepMeretHorizontalSliderSzerkeszto->setValue(ujKeret->getMeretArany());

                //aranyok
                unsigned szel = ujKeret->getSzelesseg();
                ui->kepSzelessegSpinBoxSzerkeszto->setValue(szel);

                unsigned mag = ujKeret->getMagassag();
                ui->kepMagassagSpinBoxSzerkeszto->setValue(mag);

                unsigned xKoor = ujKeret->getKepXKoordinata();
                ui->keparanyHorizontalisSpinBoxSzerkeszto->setMaximum(ujKeret->getMeret().width()*(1-szel/100.0));
                ui->keparanyHorizontalisSpinBoxSzerkeszto->setValue(xKoor);

                unsigned yKoor = ujKeret->getKepYKoordinata();
                ui->keparanyVertikalisSpinBoxSzerkeszto->setMaximum(ujKeret->getMeret().height()*(1-mag/100.0));
                ui->keparanyVertikalisSpinBoxSzerkeszto->setValue(yKoor);

                //szuro
                ui->kepSzuroComboBoxSzerkeszto->setCurrentIndex(ujKeret->getSzuro());
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
    ujSzoveg->getKimenet()->setStyleSheet("background-color: transparent");
    ujSzoveg->getKimenet()->setParent(ui->szerkesztoWidgetSzerkeszto);
    ujSzoveg->getKimenet()->setText(QString::fromStdString(ujSzoveg->getTartalom()));
    ujSzoveg->getKimenet()->setAlignment(Qt::AlignCenter);
    ujSzoveg->getKimenet()->show();

    connect(ujSzoveg->getKimenet(), &Kimenet::clicked, [=]{
        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->szovegPageSzerkeszto);

        if(jelenlegiProjekt.getJelenlegiElem() != nullptr)
        {
            if(jelenlegiProjekt.getJelenlegiElem()->getTipus() != szoveg)
            {
                jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
            }else{
                Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt.getJelenlegiElem());
                QColor szin = jelenlegiSzoveg->getSzin();
                jelenlegiSzoveg->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
            }
        }

        jelenlegiProjekt.setJelenlegiElem(ujSzoveg);
        QColor szin = ujSzoveg->getSzin();
        ujSzoveg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS + "color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

        ui->betuszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

        //szoveg
        ui->szovegTextEditSzerkeszto->setText(QString::fromStdString(ujSzoveg->getTartalom()));

        //horizontalis mozgatas
        unsigned xPont = ujSzoveg->getKimenet()->x();
        ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - ujSzoveg->getKimenet()->width());
        ui->szovegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

        //vertikalis mozgatas
        unsigned yPont = ujSzoveg->getKimenet()->y();
        ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - ujSzoveg->getKimenet()->height());
        ui->szovegVertikalisSpinBoxSzerkeszto->setValue(yPont);

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
    Kimenet* jelenlegiKimenet = jelenlegiBelyeg->getKimenet();
    jelenlegiBelyeg->kepKeszites();

    //tooltip beallitas
    ui->belyegMeretHorizontalSliderSzerkeszto->setToolTip(QString::number(value));

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKimenet->x();
    ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiKimenet->width());
    ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKimenet->y();
    ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiKimenet->height());
    ui->belyegVertikalisSpinBoxSzerkeszto->setValue(yPont);
}

void MainWindow::on_betuszinPushButtonSzerkeszto_clicked()
{
    QColor ujSzin = QColorDialog::getColor(Qt::black, this, "Betűszín Választó");

    //betuszin
    dynamic_cast<Szoveg*>(jelenlegiProjekt.getJelenlegiElem())->setSzin(ujSzin);
    jelenlegiProjekt.getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS + "color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + ");"));

    //hatterszin
    ui->betuszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + ");"));
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
    QLabel* jelenlegiKimenet = jelenlegiKep->getKimenet();
    jelenlegiKep->kepKeszites();

    //tooltip beallitas
    ui->kepMeretHorizontalSliderSzerkeszto->setToolTip(QString::number(value));

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKimenet->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiKimenet->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKimenet->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiKimenet->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);
}

void MainWindow::on_kepSzelessegSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setSzelesseg(arg1);

    jelenlegiKeret->kepKeszites();

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKeret->getKimenet()->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiKeret->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKeret->getKimenet()->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiKeret->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

    //horizontalis arany
    ui->keparanyHorizontalisSpinBoxSzerkeszto->setMaximum(jelenlegiKeret->getMeret().width()*(1-arg1/100.0));
}

void MainWindow::on_kepMagassagSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setMagassag(arg1);

    jelenlegiKeret->kepKeszites();

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKeret->getKimenet()->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->width() - jelenlegiKeret->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKeret->getKimenet()->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(ui->szerkesztoWidgetSzerkeszto->height() - jelenlegiKeret->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

    //vertikalis arany
    ui->keparanyVertikalisSpinBoxSzerkeszto->setMaximum(jelenlegiKeret->getMeret().height()*(1-arg1/100.0));
}

void MainWindow::on_keparanyHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setKepXKoordinata(arg1);

    jelenlegiKeret->kepKeszites();
}

void MainWindow::on_keparanyVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setKepYKoordinata(arg1);

    jelenlegiKeret->kepKeszites();
}

void MainWindow::on_kepSzuroComboBoxSzerkeszto_currentIndexChanged(int index)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());

    jelenlegiKeret->setSzuro(index);

    jelenlegiKeret->kepKeszites();
}

void MainWindow::on_kepTorlesPushButtonSzerkeszto_2_clicked()
{
    delete jelenlegiProjekt.getJelenlegiElem();

    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    jelenlegiProjekt.setJelenlegiElem(nullptr);
}

void MainWindow::on_belyegTorlesPushButtonSzerkeszto_clicked()
{
    delete jelenlegiProjekt.getJelenlegiElem();

    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    jelenlegiProjekt.setJelenlegiElem(nullptr);
}

void MainWindow::on_szovegTorlesPushButtonSzerkeszto_clicked()
{
    delete jelenlegiProjekt.getJelenlegiElem();

    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    jelenlegiProjekt.setJelenlegiElem(nullptr);
}

void MainWindow::on_hatterszinMegvaltoztatPushButtonSzerkeszto_clicked()
{
    QColor ujSzin = QColorDialog::getColor(Qt::black, this, "Háttérszín Választó");

    //oldalszin
    jelenlegiProjekt.getJelenlegiOldal()->getStilus()->setSzin(ujSzin);
    jelenlegiProjekt.getJelenlegiOldal()->getStilus()->setHatterTipus(0);
    ui->szerkesztoWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + ");"));

    //hatterszin
    ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + ");"));
}

void MainWindow::on_hatterPushButtonSzerkeszto_clicked()
{
    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->hatterPageSzerkeszto);

    //hatterszin
    QColor szin = jelenlegiProjekt.getJelenlegiOldal()->getStilus()->getSzin();
    ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
}

void MainWindow::on_lapozasLePushButtonSzerkeszto_clicked()
{
    if(jelenlegiProjekt.lapozas(false))
    {
        if(jelenlegiProjekt.getJelenlegiOldal()->getStilus()->getHatterTipus() == 0)
        {
            QColor szin = jelenlegiProjekt.getJelenlegiOldal()->getStilus()->getSzin();

            //oldalszin
            ui->szerkesztoWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

            //hatterszin
            ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
        }else{
            Minta minta = jelenlegiProjekt.getJelenlegiOldal()->getStilus()->getMinta();

            //minta beallitas
            ui->szerkesztoWidgetSzerkeszto->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidgetSzerkeszto{border-image: url(" + minta.getEleresiUt() + ") 0 0 0 0 stretch stretch;}"));
        }

        //oldal beállítása
        ui->oldalszamLabelSzerkeszto->setText(QString::fromStdString(to_string((ui->oldalszamLabelSzerkeszto->text().toInt())-1)));
    }
}

void MainWindow::on_lapozasFelPushButtonSzerkeszto_clicked()
{
    if(jelenlegiProjekt.lapozas(true))
    {
        if(jelenlegiProjekt.getJelenlegiOldal()->getStilus()->getHatterTipus() == 0)
        {
            QColor szin = jelenlegiProjekt.getJelenlegiOldal()->getStilus()->getSzin();

            //oldalszin
            ui->szerkesztoWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

            //hatterszin
            ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
        }else{
            Minta minta = jelenlegiProjekt.getJelenlegiOldal()->getStilus()->getMinta();

            //minta beallitas
            ui->szerkesztoWidgetSzerkeszto->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidgetSzerkeszto{border-image: url(" + minta.getEleresiUt() + ") 0 0 0 0 stretch stretch;}"));
        }

        //oldal beállítása
        ui->oldalszamLabelSzerkeszto->setText(QString::fromStdString(to_string((ui->oldalszamLabelSzerkeszto->text().toInt())+1)));
    }
}


void MainWindow::on_keretValasztasPushButtonSzerleszto_clicked()
{
    KeretValaszto* k = new KeretValaszto(this);
    if(k->exec() == QDialog::Accepted)
    {
        Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());
        jelenlegiKeret->setKeret(k->getIndex());
        jelenlegiKeret->kepKeszites();
    }
}

void MainWindow::on_egysegeskeretPushButtonSzerkeszto_clicked()
{
    KeretValaszto* k = new KeretValaszto(this);
    if(k->exec() == QDialog::Accepted)
    {
        jelenlegiProjekt.getJelenlegiOldal()->egysegesKeret(k->getIndex());
    }
}


void MainWindow::on_kepValasztasPushButtonSzerkeszto_clicked()
{
    KepValaszto* k = new KepValaszto(this, jelenlegiProjekt.getKepek());
    if(k->exec() == QDialog::Accepted)
    {
        string forras = k->getJelenlegiKep();
        if(forras != "")
        {
            Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt.getJelenlegiElem());
            jelenlegiKeret->setForras(forras);
            jelenlegiKeret->kepKeszites();
        }
    }
}
