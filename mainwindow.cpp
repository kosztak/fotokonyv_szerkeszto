#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ablak beallitasok
    this->setWindowState(Qt::WindowMaximized);
    ui->stilusToolButtonSzerkeszto->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->kepekToolButtonSzerkeszto->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->belyegekToolButtonSzerkeszto->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->elemekToolButtonSzerkeszto->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //szerkeszto widget beallitasa
    szerkesztoWidget = new QWidget;
    szerkesztoWidget->resize(1240, 1754);
    szerkesztoWidget->setObjectName("szerkesztoWidget");
    szerkesztoWidget->setStyleSheet("background-color: #ffffff");

    scene = new QGraphicsScene;
    scene->addWidget(szerkesztoWidget);

    graphicsView = new CustomView();
    ui->dummyGridLayoutSzerkeszto->addWidget(graphicsView);
    graphicsView->setScene(scene);
    graphicsView->setStyleSheet("background-color: rgb(249, 219, 189);");
    graphicsView->setFrameStyle(QFrame::NoFrame);

    //stacked widget beallitas
    ui->kepernyoStackedWidget->setCurrentWidget(ui->fomenuKepernyoPage);
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->stilusPageSzerkeszto);
    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    //inicializalas
    inicializalas();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//RENDSZER
void MainWindow::inicializalas()
{
    QFile file("./adatok/rendszer.json");
    if(file.open(QIODevice::ReadOnly))
    {
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        QJsonObject object = document.object();

        //projektek
        QJsonArray projektArray = object["projektek"].toArray();
        for(auto it = projektArray.begin(); it != projektArray.end(); ++it)
        {
            QJsonObject projektObject = it->toObject();
            projektek[projektObject["nev"].toString().toStdString()] = projektObject["eleres"].toString().toStdString();
        }

        //belyegek
        QJsonArray belyegArray = object["belyegek"].toArray();
        for(auto it = belyegArray.begin(); it != belyegArray.end(); ++it)
        {
            QJsonObject belyegObject = it->toObject();
            belyegek[belyegObject["nev"].toString().toStdString()] = belyegObject["eleres"].toString().toStdString();
        }

        //mintak
        QJsonArray mintaArray = object["mintak"].toArray();
        for(auto it = mintaArray.begin(); it != mintaArray.end(); ++it)
        {
            QJsonObject mintaObject = it->toObject();
            mintak[mintaObject["nev"].toString().toStdString()] = mintaObject["eleres"].toString().toStdString();
        }

        file.close();
    }

    //projekt gombok elkeszitese
    for(auto p: projektek)
    {
        //gomb beallitasa
        QPushButton* button = new QPushButton();
        button->setText(QString::fromStdString("  " + p.first));
        button->setStyleSheet("text-align: left; font-size: 24pt; font-weight: bold; color: #000000; background-color: rgb(249, 219, 189); border: 4px outset #f5c28f;");
        button->setAutoFillBackground(true);

        projektekLista[p.first] = button;
        ui->projektekVerticalLayoutFomenu->addWidget(button);

        //gomb funkcio hozaadas
        connect(button, &QPushButton::clicked, [=](){
            if(kivalasztottProjekt.second != nullptr)
            {
                kivalasztottProjekt.second->setStyleSheet("text-align: left; font-size: 24pt; font-weight: bold; color: #000000; background-color: rgb(249, 219, 189); border: 4px outset #f5c28f;");
            }

            kivalasztottProjekt = pair<string, QPushButton*>(p.second, button);

            button->setStyleSheet("text-align: left; font-size: 24pt; font-weight: bold; color: #000000; background-color: rgb(249, 219, 189); border: 4px inset #f5c28f;");
        });
    }

    //elrendezesek
    unsigned short szegely = 50;
    {
        //1_1
        list<pair<QPoint, QSize>> lista = {pair(QPoint(szegely, szegely), QSize(szerkesztoWidget->width()-szegely*2, szerkesztoWidget->height()-szegely*2))};

        elrendezesek.insert(pair("1_1", Elrendezes(1, lista)));
    }

    {
        //2_1
        list<pair<QPoint, QSize>> lista = {pair(QPoint(szegely, szegely), QSize((szerkesztoWidget->width())-szegely*2, (szerkesztoWidget->height()/2)-szegely*2)),
                                           pair(QPoint(szegely, (szerkesztoWidget->height()/2)+szegely), QSize((szerkesztoWidget->width())-szegely*2, (szerkesztoWidget->height()/2)-szegely*2))};

        elrendezesek.insert(pair("2_1", Elrendezes(2, lista)));
    }

    {
        //2_2
        list<pair<QPoint, QSize>> lista = {pair(QPoint((szerkesztoWidget->width()/2)+szegely, szegely), QSize((szerkesztoWidget->width()/2)-szegely*2, (szerkesztoWidget->height()/2)-szegely*2)),
                                           pair(QPoint(szegely, (szerkesztoWidget->height()/2)+szegely), QSize((szerkesztoWidget->width())-szegely*2, (szerkesztoWidget->height()/2)-szegely*2))};

        elrendezesek.insert(pair("2_2", Elrendezes(2, lista)));
    }

    {
        //3_1
        list<pair<QPoint, QSize>> lista = {pair(QPoint(szegely, szegely), QSize((szerkesztoWidget->width())-szegely*2, (szerkesztoWidget->height()/3)-szegely*2)),
                                           pair(QPoint(szegely, (szerkesztoWidget->height()/3)+szegely), QSize(szerkesztoWidget->width()-szegely*2, (szerkesztoWidget->height()/3)-szegely*2)),
                                           pair(QPoint(szegely, (szerkesztoWidget->height()/3)*2+szegely), QSize((szerkesztoWidget->width())-szegely*2, (szerkesztoWidget->height()/3)-szegely*2))};

        elrendezesek.insert(pair("3_1", Elrendezes(3, lista)));
    }

    {
        //3_2
        list<pair<QPoint, QSize>> lista = {pair(QPoint(szegely, szegely), QSize((szerkesztoWidget->width()/2)-szegely*2, (szerkesztoWidget->height()/2)-szegely*2)),
                                           pair(QPoint((szerkesztoWidget->width()/2)+szegely, szegely), QSize((szerkesztoWidget->width()/2)-szegely*2, (szerkesztoWidget->height()/2)-szegely*2)),
                                           pair(QPoint(szegely, (szerkesztoWidget->height()/2)+szegely), QSize((szerkesztoWidget->width())-szegely*2, (szerkesztoWidget->height()/2)-szegely*2))};

        elrendezesek.insert(pair("3_2", Elrendezes(3, lista)));
    }

    {
        //4_1
        list<pair<QPoint, QSize>> lista = {pair(QPoint(szegely, szegely), QSize((szerkesztoWidget->width()/2)-szegely*2, (szerkesztoWidget->height()/2)-szegely*2)),
                                           pair(QPoint((szerkesztoWidget->width()/2)+szegely, szegely), QSize((szerkesztoWidget->width()/2)-szegely*2, (szerkesztoWidget->height()/2)-szegely*2)),
                                           pair(QPoint(szegely, (szerkesztoWidget->height()/2)+szegely), QSize((szerkesztoWidget->width()/2)-szegely*2, (szerkesztoWidget->height()/2)-szegely*2)),
                                           pair(QPoint((szerkesztoWidget->width()/2)+szegely, (szerkesztoWidget->height()/2)+szegely), QSize((szerkesztoWidget->width()/2)-szegely*2, (szerkesztoWidget->height()/2)-szegely*2))};

        elrendezesek.insert(pair("4_1", Elrendezes(4, lista)));
    }
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

//------------------------------------------------------------------------------------------
//SZERKESZTO
void MainWindow::kepFrissites(Keret *ptr)
{
    kepekLista[ptr]->setIcon(ptr->getKimenet()->pixmap());
}

void MainWindow::listaFrissites()
{
    //regi elemek torlese
    for(auto i: kepekLista)
    {
        delete i.second;
    }
    kepekLista.clear();

    for(auto i: belyegekLista)
    {
        delete i.second;
    }
    belyegekLista.clear();

    for(auto i: szovegekLista)
    {
        delete i.second;
    }
    szovegekLista.clear();

    //uj elemek feltoltese
    list<Keret*> keretLista = jelenlegiProjekt->getJelenlegiOldal()->getKeretek();
    for(auto i: keretLista)
    {
        QPushButton* listaElem = new QPushButton;
        listaElem->setStyleSheet("background-color: #ffffff; border: 3px outset #c2c2c2;");
        listaElem->setAutoFillBackground(true);

        connect(listaElem, &QPushButton::clicked, [=]{
            ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

            if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
            {
                if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                {
                    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                }else{
                    QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                }
            }

            jelenlegiProjekt->setJelenlegiElem(i);
            i->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));


            //horizontalis mozgatas
            unsigned xPont = i->getKimenet()->x();
            ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - i->getKimenet()->width());
            ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

            //vertikalis mozgatas
            unsigned yPont = i->getKimenet()->y();
            ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - i->getKimenet()->height());
            ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

            //meretezes
            ui->kepMeretSpinBoxSzerkeszto->setValue(i->getMeretArany());

            //aranyok
            unsigned szel = i->getSzelesseg();
            ui->kepSzelessegSpinBoxSzerkeszto->setValue(szel);

            unsigned mag = i->getMagassag();
            ui->kepMagassagSpinBoxSzerkeszto->setValue(mag);

            unsigned xKoor = i->getKepXKoordinata();
            ui->keparanyHorizontalisSpinBoxSzerkeszto->setMaximum(i->getMeret().width()*(1-szel/100.0));
            ui->keparanyHorizontalisSpinBoxSzerkeszto->setValue(xKoor);

            unsigned yKoor = i->getKepYKoordinata();
            ui->keparanyVertikalisSpinBoxSzerkeszto->setMaximum(i->getMeret().height()*(1-mag/100.0));
            ui->keparanyVertikalisSpinBoxSzerkeszto->setValue(yKoor);

            //szuro
            ui->kepSzuroComboBoxSzerkeszto->setCurrentIndex(i->getSzuro());
        });

        listaElem->setIcon(i->getKimenet()->pixmap());
        listaElem->setIconSize(QSize(90, 90));

        kepekLista[i] = listaElem;
        ui->kepListaVerticalLayoutSzerkeszto->addWidget(listaElem);
    }

    list<Belyeg*> belyegLista = jelenlegiProjekt->getJelenlegiOldal()->getBelyegek();
    for(auto i: belyegLista)
    {
        QPushButton* listaElem = new QPushButton;
        listaElem->setStyleSheet("background-color: #ffffff; border: 3px outset #c2c2c2;");
        listaElem->setAutoFillBackground(true);

        connect(listaElem, &QPushButton::clicked, [=]{
            ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegPageSzerkeszto);

            if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
            {
                if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                {
                    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                }else{
                    QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                }
            }

            jelenlegiProjekt->setJelenlegiElem(i);
            i->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));

            //horizontalis mozgatas
            unsigned xPont = i->getKimenet()->x();
            ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - i->getKimenet()->width());
            ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

            //vertikalis mozgatas
            unsigned yPont = i->getKimenet()->y();
            ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - i->getKimenet()->height());
            ui->belyegVertikalisSpinBoxSzerkeszto->setValue(yPont);

            //meretezes
            ui->belyegMeretSpinBoxSzerkeszto->setValue(i->getMeretArany());
        });

        listaElem->setIcon(i->getKimenet()->pixmap());
        listaElem->setIconSize(QSize(90, 90));

        belyegekLista[i] = listaElem;
        ui->belyegListaVerticalLayoutSzerkeszto->addWidget(listaElem);
    }

    list<Szoveg*> szovegLista = jelenlegiProjekt->getJelenlegiOldal()->getSzovegek();
    for(auto i: szovegLista)
    {
        QPushButton* listaElem = new QPushButton;
        listaElem->setStyleSheet("background-color: #ffffff; border: 3px outset #c2c2c2; color: #000000");
        listaElem->setAutoFillBackground(true);

        connect(listaElem, &QPushButton::clicked, [=]{
            ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->szovegPageSzerkeszto);

            if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
            {
                if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                {
                    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                }else{
                    Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());
                    QColor szin = jelenlegiSzoveg->getSzin();
                    jelenlegiSzoveg->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                }
            }

            jelenlegiProjekt->setJelenlegiElem(i);
            QColor szin = i->getSzin();
            i->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS + "color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

            ui->betuszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));

            //szoveg
            ui->szovegTextEditSzerkeszto->setText(QString::fromStdString(i->getTartalom()));

            //horizontalis mozgatas
            unsigned xPont = i->getKimenet()->x();
            ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - i->getKimenet()->width());
            ui->szovegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

            //vertikalis mozgatas
            unsigned yPont = i->getKimenet()->y();
            ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - i->getKimenet()->height());
            ui->szovegVertikalisSpinBoxSzerkeszto->setValue(yPont);

            //betumeret
            ui->betumeretSpinBoxSzerkeszto->setValue(i->getKimenet()->font().pointSize());
        });

        unsigned short hatar = 15;
        QString text = QString::fromStdString(i->getTartalom()).split("\n").constFirst();
        if(text.length() <= hatar)
        {
            listaElem->setText(text);
        }else{
            listaElem->setText(text.left(hatar-2).append("..."));
        }

        szovegekLista[i] = listaElem;
        ui->szovegListaVerticalLayoutSzerkeszto->addWidget(listaElem);
    }
}

void MainWindow::on_stilusToolButtonSzerkeszto_clicked()
{
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->stilusPageSzerkeszto);
}

void MainWindow::on_kepekToolButtonSzerkeszto_clicked()
{
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->kepekPageSzerkeszto);
}

void MainWindow::on_belyegekToolButtonSzerkeszto_clicked()
{
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegekPageSzerkeszto);
}

void MainWindow::on_elemekToolButtonSzerkeszto_clicked()
{
    ui->tartalomStackedWidgetSzerkeszto->setCurrentWidget(ui->elemekPageSzerkeszto);
}

//kepek
void MainWindow::on_kepHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->move(arg1, jelenlegiProjekt->getJelenlegiElem()->getKimenet()->y()); //x, y
}

void MainWindow::on_kepVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->move(jelenlegiProjekt->getJelenlegiElem()->getKimenet()->x(), arg1); //x, y
}

void MainWindow::on_kepSzelessegSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());

    jelenlegiKeret->setSzelesseg(arg1);

    jelenlegiKeret->kepKeszites();

    //lista elem frissitese
    kepFrissites(jelenlegiKeret);

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKeret->getKimenet()->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiKeret->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKeret->getKimenet()->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiKeret->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

    //horizontalis arany
    ui->keparanyHorizontalisSpinBoxSzerkeszto->setMaximum(jelenlegiKeret->getMeret().width()*(1-arg1/100.0));
}

void MainWindow::on_kepMagassagSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());

    jelenlegiKeret->setMagassag(arg1);

    jelenlegiKeret->kepKeszites();

    //lista elem frissitese
    kepFrissites(jelenlegiKeret);

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKeret->getKimenet()->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiKeret->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKeret->getKimenet()->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiKeret->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

    //vertikalis arany
    ui->keparanyVertikalisSpinBoxSzerkeszto->setMaximum(jelenlegiKeret->getMeret().height()*(1-arg1/100.0));
}

void MainWindow::on_keparanyHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());

    jelenlegiKeret->setKepXKoordinata(arg1);

    jelenlegiKeret->kepKeszites();

    //lista elem frissitese
    kepFrissites(jelenlegiKeret);
}

void MainWindow::on_keparanyVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());

    jelenlegiKeret->setKepYKoordinata(arg1);

    jelenlegiKeret->kepKeszites();

    //lista elem frissitese
    kepFrissites(jelenlegiKeret);
}

void MainWindow::on_kepSzuroComboBoxSzerkeszto_currentIndexChanged(int index)
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());

    jelenlegiKeret->setSzuro(index);

    jelenlegiKeret->kepKeszites();

    //lista elem frissitese
    kepFrissites(jelenlegiKeret);
}

void MainWindow::on_kepTorlesPushButtonSzerkeszto_clicked()
{
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());

    //lista elem torlese
    delete kepekLista[jelenlegiKeret];
    kepekLista.erase(jelenlegiKeret);

    //oldalrol torles
    jelenlegiProjekt->getJelenlegiOldal()->keretTorles(jelenlegiKeret);

    //keret torlese
    delete jelenlegiProjekt->getJelenlegiElem();

    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    jelenlegiProjekt->setJelenlegiElem(nullptr);
}

void MainWindow::on_keretValasztasPushButtonSzerleszto_clicked()
{
    KeretValaszto* k = new KeretValaszto(this);
    if(k->exec() == QDialog::Accepted)
    {
        if(k->getIndex() != 1000)
        {
            Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());
            jelenlegiKeret->setKeret(k->getIndex());
            jelenlegiKeret->kepKeszites();

            //lista elem frissitese
            kepFrissites(jelenlegiKeret);
        }
    }
}

void MainWindow::on_kepValasztasPushButtonSzerkeszto_clicked()
{
    KepValaszto* k = new KepValaszto(this, jelenlegiProjekt->getKepek());
    if(k->exec() == QDialog::Accepted)
    {
        string forras = k->getJelenlegiKep();
        if(forras != "")
        {
            Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());
            jelenlegiKeret->setForras(forras);
            jelenlegiKeret->kepKeszites();

            //lista elem frissitese
            kepFrissites(jelenlegiKeret);
        }
    }
}

void MainWindow::on_kepElorehozasPushButtonSzerkeszto_clicked()
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->raise();
}

void MainWindow::on_kepHatrakuldesPushButtonSzerkeszto_clicked()
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->lower();
}

void MainWindow::on_kepDolesszogSpinBoxSzerkeszto_valueChanged(int arg1)
{
    //dolesszog beallitasa
    Keret* jelenlegiKeret = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());
    jelenlegiProjekt->getJelenlegiElem()->forgatas(arg1);
    jelenlegiKeret->kepKeszites();

    //lista elem frissitese
    kepFrissites(jelenlegiKeret);

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKeret->getKimenet()->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiKeret->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKeret->getKimenet()->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiKeret->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);
}

void MainWindow::on_kepMeretSpinBoxSzerkeszto_valueChanged(int arg1)
{
    //meret arany megvaltoztatasa
    Keret* jelenlegiKep = dynamic_cast<Keret*>(jelenlegiProjekt->getJelenlegiElem());
    jelenlegiKep->setMeretArany(arg1);

    //kep meretenek megvaltoztatasa
    QLabel* jelenlegiKimenet = jelenlegiKep->getKimenet();
    jelenlegiKep->kepKeszites();

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKimenet->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiKimenet->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKimenet->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiKimenet->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);
}

//belyegek
void MainWindow::on_belyegHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->move(arg1, jelenlegiProjekt->getJelenlegiElem()->getKimenet()->y()); //x, y
}

void MainWindow::on_belyegVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->move(jelenlegiProjekt->getJelenlegiElem()->getKimenet()->x(), arg1); //x, y
}

void MainWindow::on_belyegTorlesPushButtonSzerkeszto_clicked()
{
    Belyeg* jelenlegiBelyeg = dynamic_cast<Belyeg*>(jelenlegiProjekt->getJelenlegiElem());

    //lista elem torlese
    delete belyegekLista[jelenlegiBelyeg];
    belyegekLista.erase(jelenlegiBelyeg);

    //oldalrol torles
    jelenlegiProjekt->getJelenlegiOldal()->belyegTorles(jelenlegiBelyeg);

    //belyeg torlese
    delete jelenlegiProjekt->getJelenlegiElem();

    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    jelenlegiProjekt->setJelenlegiElem(nullptr);
}

void MainWindow::on_belyegElorehozasPushButtonSzerkeszto_clicked()
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->raise();
}

void MainWindow::on_belyegHatrakuldesPushButtonSzerkeszto_clicked()
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->lower();
}

void MainWindow::on_belyegDolesszogSpinBoxSzerkeszto_valueChanged(int arg1)
{
    //dolesszog beallitasa
    Belyeg* jelenlegiBelyeg = dynamic_cast<Belyeg*>(jelenlegiProjekt->getJelenlegiElem());
    jelenlegiProjekt->getJelenlegiElem()->forgatas(arg1);
    jelenlegiBelyeg->kepKeszites();

    //horizontalis mozgatas
    unsigned xPont = jelenlegiBelyeg->getKimenet()->x();
    ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiBelyeg->getKimenet()->width());
    ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiBelyeg->getKimenet()->y();
    ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiBelyeg->getKimenet()->height());
    ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);
}

void MainWindow::on_belyegMeretSpinBoxSzerkeszto_valueChanged(int arg1)
{
    //meret arany megvaltoztatasa
    Belyeg* jelenlegiBelyeg = dynamic_cast<Belyeg*>(jelenlegiProjekt->getJelenlegiElem());
    jelenlegiBelyeg->setMeretArany(arg1);

    //belyeg meretenek megvaltoztatasa
    Kimenet* jelenlegiKimenet = jelenlegiBelyeg->getKimenet();
    jelenlegiBelyeg->kepKeszites();

    //horizontalis mozgatas
    unsigned xPont = jelenlegiKimenet->x();
    ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiKimenet->width());
    ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

    //vertikalis mozgatas
    unsigned yPont = jelenlegiKimenet->y();
    ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiKimenet->height());
    ui->belyegVertikalisSpinBoxSzerkeszto->setValue(yPont);
}

//szovegek
void MainWindow::on_ujSzovegPushButtonSzerkeszto_clicked()
{
    Szoveg *ujSzoveg = new Szoveg(0, 0, 0, "szöveg");
                       ujSzoveg->getKimenet()->setStyleSheet("background-color: transparent");
    ujSzoveg->getKimenet()->setParent(szerkesztoWidget);
    ujSzoveg->getKimenet()->setText(QString::fromStdString(ujSzoveg->getTartalom()));
    ujSzoveg->getKimenet()->setAlignment(Qt::AlignCenter);
    ujSzoveg->getKimenet()->show();

    //kimenet funkcio
    connect(ujSzoveg->getKimenet(), &Kimenet::clicked, [=]{
        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->szovegPageSzerkeszto);

        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
        {
            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
            {
                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
            }else{
                Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());
                QColor szin = jelenlegiSzoveg->getSzin();
                jelenlegiSzoveg->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
            }
        }

        jelenlegiProjekt->setJelenlegiElem(ujSzoveg);
        QColor szin = ujSzoveg->getSzin();
        ujSzoveg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS + "color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

        //betuszin
        ui->betuszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));

        //szoveg
        ui->szovegTextEditSzerkeszto->setText(QString::fromStdString(ujSzoveg->getTartalom()));

        //horizontalis mozgatas
        unsigned xPont = ujSzoveg->getKimenet()->x();
        ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujSzoveg->getKimenet()->width());
        ui->szovegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

        //vertikalis mozgatas
        unsigned yPont = ujSzoveg->getKimenet()->y();
        ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujSzoveg->getKimenet()->height());
        ui->szovegVertikalisSpinBoxSzerkeszto->setValue(yPont);

        //betumeret
        ui->betumeretSpinBoxSzerkeszto->setValue(ujSzoveg->getKimenet()->font().pointSize());

        //betutipus
        ui->betutipusComboBoxSzerkeszto->setCurrentFont(ujSzoveg->getBetutipus());

        //felkover
        ui->felkoverCheckBoxSzerkeszto->setChecked(ujSzoveg->getBetutipus().bold());

        //dolt
        ui->doltCheckBoxSzerkeszto->setChecked(ujSzoveg->getBetutipus().italic());

        //alahuzott
        ui->alahuzottCheckBoxSzerkeszto->setChecked(ujSzoveg->getBetutipus().underline());
    });

    //lista elem
    QPushButton* listaElem = new QPushButton;
    listaElem->setAutoFillBackground(true);
    connect(listaElem, &QPushButton::clicked, [=]{
        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->szovegPageSzerkeszto);

        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
        {
            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
            {
                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
            }else{
                Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());
                QColor szin = jelenlegiSzoveg->getSzin();
                jelenlegiSzoveg->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
            }
        }

        jelenlegiProjekt->setJelenlegiElem(ujSzoveg);
        QColor szin = ujSzoveg->getSzin();
        ujSzoveg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS + "color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

        ui->betuszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));

        //szoveg
        ui->szovegTextEditSzerkeszto->setText(QString::fromStdString(ujSzoveg->getTartalom()));

        //horizontalis mozgatas
        unsigned xPont = ujSzoveg->getKimenet()->x();
        ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujSzoveg->getKimenet()->width());
        ui->szovegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

        //vertikalis mozgatas
        unsigned yPont = ujSzoveg->getKimenet()->y();
        ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujSzoveg->getKimenet()->height());
        ui->szovegVertikalisSpinBoxSzerkeszto->setValue(yPont);

        //betumeret
        ui->betumeretSpinBoxSzerkeszto->setValue(ujSzoveg->getKimenet()->font().pointSize());
    });

    listaElem->setText("szöveg");
        listaElem->setStyleSheet("color: rgb(255,255,255)");

    szovegekLista[ujSzoveg] = listaElem;
    ui->szovegListaVerticalLayoutSzerkeszto->addWidget(listaElem);

    //keret projekthez adas
    jelenlegiProjekt->getJelenlegiOldal()->szovegHozzaadas(ujSzoveg);

    QFont font = ujSzoveg->getKimenet()->font();
    font.setFamily(QString("Arial"));
    font.setPointSize(24);
    ujSzoveg->getKimenet()->setFont(font);
    ujSzoveg->getKimenet()->adjustSize();
}

void MainWindow::on_szovegHorizontalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->move(arg1, jelenlegiProjekt->getJelenlegiElem()->getKimenet()->y()); //x, y
}

void MainWindow::on_szovegVertikalisSpinBoxSzerkeszto_valueChanged(int arg1)
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->move(jelenlegiProjekt->getJelenlegiElem()->getKimenet()->x(), arg1); //x, y
}

void MainWindow::on_szovegTextEditSzerkeszto_textChanged()
{
    //tartalom beallitas
    Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());
    jelenlegiSzoveg->setTartalom(ui->szovegTextEditSzerkeszto->toPlainText().toStdString());

    //gomb meret beallitas
    jelenlegiSzoveg->getKimenet()->adjustSize();

    //mozgatas
    ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiSzoveg->getKimenet()->width());
    ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiSzoveg->getKimenet()->height());

    //lista elem frissitese
    unsigned short hatar = 15;
    QString text = QString::fromStdString(jelenlegiSzoveg->getTartalom()).split("\n").constFirst();
    if(text.length() <= hatar)
    {
        szovegekLista[jelenlegiSzoveg]->setText(text);
    }else{
        szovegekLista[jelenlegiSzoveg]->setText(text.left(hatar-2).append("..."));
    }
}

void MainWindow::on_betumeretSpinBoxSzerkeszto_valueChanged(int arg1)
{
    QFont font = jelenlegiProjekt->getJelenlegiElem()->getKimenet()->font();
    font.setPointSize(arg1);
    dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->setBetutipus(font);

    //mozgatas
    ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiProjekt->getJelenlegiElem()->getKimenet()->width());
    ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiProjekt->getJelenlegiElem()->getKimenet()->height());
}

void MainWindow::on_betutipusComboBoxSzerkeszto_currentIndexChanged(int index)
{
    QFont font = jelenlegiProjekt->getJelenlegiElem()->getKimenet()->font();
    font.setFamily(ui->betutipusComboBoxSzerkeszto->currentText());
    dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->setBetutipus(font);

    //mozgatas
    ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiProjekt->getJelenlegiElem()->getKimenet()->width());
    ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiProjekt->getJelenlegiElem()->getKimenet()->height());
}

void MainWindow::on_betuszinPushButtonSzerkeszto_clicked()
{
    QColor ujSzin = QColorDialog::getColor(Qt::black, this, "Betűszín Választó");

    //betuszin
    dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->setSzin(ujSzin);
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS + "color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + ");"));

    //hatterszin
    ui->betuszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + "); border: 3px inset #bb1133;"));
}

void MainWindow::on_felkoverCheckBoxSzerkeszto_stateChanged(int arg1)
{
    //gomb beallitasa
    QFont font = jelenlegiProjekt->getJelenlegiElem()->getKimenet()->font();
    font.setBold(arg1);
    Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());
    dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->setBetutipus(font);

    //mozgatas
    ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - jelenlegiSzoveg->getKimenet()->width());
    ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - jelenlegiSzoveg->getKimenet()->height());
}

void MainWindow::on_doltCheckBoxSzerkeszto_stateChanged(int arg1)
{
    QFont font = jelenlegiProjekt->getJelenlegiElem()->getKimenet()->font();
    font.setItalic(arg1);
    dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->setBetutipus(font);
}

void MainWindow::on_alahuzottCheckBoxSzerkeszto_stateChanged(int arg1)
{
    QFont font = jelenlegiProjekt->getJelenlegiElem()->getKimenet()->font();
    font.setUnderline(arg1);
    dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->setBetutipus(font);
}

void MainWindow::on_szovegTorlesPushButtonSzerkeszto_clicked()
{
    Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());

    //lista elem torlese
    delete szovegekLista[jelenlegiSzoveg];
    szovegekLista.erase(jelenlegiSzoveg);

    //oldalrol torles
    jelenlegiProjekt->getJelenlegiOldal()->szovegTorles(jelenlegiSzoveg);

    //szoveg torlese
    delete jelenlegiProjekt->getJelenlegiElem();

    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

    jelenlegiProjekt->setJelenlegiElem(nullptr);
}

void MainWindow::on_szovegElorehozasPushButtonSzerkeszto_clicked()
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->raise();
}

void MainWindow::on_szovegHatrakuldesPushButtonSzerkeszto_clicked()
{
    jelenlegiProjekt->getJelenlegiElem()->getKimenet()->lower();
}

//oldalak
void MainWindow::on_hatterszinMegvaltoztatPushButtonSzerkeszto_clicked()
{
    QColor ujSzin = QColorDialog::getColor(Qt::black, this, "Háttérszín Választó");

    //oldalszin
    jelenlegiProjekt->getJelenlegiOldal()->getStilus()->setSzin(ujSzin);
    jelenlegiProjekt->getJelenlegiOldal()->getStilus()->setHatterTipus(0);
    szerkesztoWidget->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + ");"));

    //hatterszin
    ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(ujSzin.red()) + "," + to_string(ujSzin.green()) + "," + to_string(ujSzin.blue()) + "," + to_string(ujSzin.alphaF()) + "); border: 3px inset #bb1133;"));
}

void MainWindow::on_hatterPushButtonSzerkeszto_clicked()
{
    ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->hatterPageSzerkeszto);

    //hatterszin
    QColor szin = jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getSzin();
    ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));
}

void MainWindow::on_lapozasLePushButtonSzerkeszto_clicked()
{
    if(jelenlegiProjekt->lapozas(false))
    {
        if(jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getHatterTipus() == 0)
        {
            QColor szin = jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getSzin();

            //oldalszin
            szerkesztoWidget->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

            //hatterszin
            ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));
        }else{
            Minta minta = jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getMinta();

            //minta beallitas
            szerkesztoWidget->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidget{border-image: url(" + minta.getEleresiUt() + ") 0 0 0 0 stretch stretch;}"));
        }

        //oldal beállítása
        ui->oldalszamLabelSzerkeszto->setText(QString::fromStdString("" + to_string(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam()) + "/" + to_string(jelenlegiProjekt->getOldalszam())));

        //listak frissitese
        listaFrissites();
    }
}

void MainWindow::on_lapozasFelPushButtonSzerkeszto_clicked()
{
    if(jelenlegiProjekt->lapozas(true))
    {
        if(jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getHatterTipus() == 0)
        {
            QColor szin = jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getSzin();

            //oldalszin
            szerkesztoWidget->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

            //hatterszin
            ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));
        }else{
            Minta minta = jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getMinta();

            //minta beallitas
            szerkesztoWidget->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidget{border-image: url(" + minta.getEleresiUt() + ") 0 0 0 0 stretch stretch;}"));
        }

        //oldal beállítása
        ui->oldalszamLabelSzerkeszto->setText(QString::fromStdString("" + to_string(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam()) + "/" + to_string(jelenlegiProjekt->getOldalszam())));

        //listak frissitese
        listaFrissites();
    }
}

void MainWindow::on_egysegeskeretPushButtonSzerkeszto_clicked()
{
    KeretValaszto* k = new KeretValaszto(this);
    if(k->exec() == QDialog::Accepted)
    {
        if(k->getIndex() != 1000)
            jelenlegiProjekt->getJelenlegiOldal()->egysegesKeret(k->getIndex());
    }
}

void MainWindow::on_elrendezesPushButtonSzerkeszto_clicked()
{
    ElrendezesValaszto* e = new ElrendezesValaszto(this, elrendezesek, jelenlegiProjekt->getJelenlegiOldal()->getKeretek().size());
    if(e->exec() == QDialog::Accepted)
    {
        //jelenlegi elem uritese
        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
        {
            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
            {
                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
            }else{
                Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());
                QColor szin = jelenlegiSzoveg->getSzin();
                jelenlegiSzoveg->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
            }
        }

        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

        //elrendezes alkalmazasa
        Elrendezes jelenlegiElrendezes = elrendezesek.at(e->getValasztas());

        list<Keret*> jelenlegiKeretek = jelenlegiProjekt->getJelenlegiOldal()->getKeretek();
        auto jelenlegiPoz = jelenlegiElrendezes.getElhelyezkedesek().begin();
        for(Keret* i: jelenlegiKeretek)
        {
            Kimenet* jelenlegiKimenet = i->getKimenet();

            //elhelyezes
            jelenlegiKimenet->move(jelenlegiPoz->first);

            //meretezes
            unsigned szelArany = ((jelenlegiPoz->second.width()*1.0)/(jelenlegiKimenet->width()*1.0))*100.0;
            unsigned magArany = ((jelenlegiPoz->second.height()*1.0)/(jelenlegiKimenet->height()*1.0))*100.0;

            if(szelArany >= magArany)
            {
                if((szelArany/100.0)*i->getMeretArany() > 300)
                {
                    i->setMeretArany(300);
                }else{
                    i->setMeretArany((szelArany/100.0)*i->getMeretArany());
                }

                i->kepKeszites();
                if(jelenlegiKimenet->height() > jelenlegiPoz->second.height())
                {
                    i->setMagassag((jelenlegiPoz->second.height()/(jelenlegiKimenet->height()*1.0))*i->getMagassag());
                    i->kepKeszites();
                }
            }else{
                if((magArany/100.0)*i->getMeretArany() > 300)
                {
                    i->setMeretArany(300);
                }else{
                    i->setMeretArany((magArany/100.0)*i->getMeretArany());
                }

                i->kepKeszites();
                if(jelenlegiKimenet->width() > jelenlegiPoz->second.width())
                {
                    i->setSzelesseg((jelenlegiPoz->second.width()/(jelenlegiKimenet->width()*1.0))*i->getSzelesseg());
                    i->kepKeszites();
                }
            }

            // i->kepKeszites();

            jelenlegiPoz++;
        }

        for(;jelenlegiPoz != jelenlegiElrendezes.getElhelyezkedesek().end(); jelenlegiPoz++)
        {
            QPixmap pixmap(jelenlegiPoz->second);
            QPainter painter(&pixmap);
            keretAlapHatter.render(&painter);

            //funkcio hozzaadas a kep gombnak
            Keret *ujKeret = new Keret(pixmap.size(), pixmap, jelenlegiPoz->first.x(), jelenlegiPoz->first.y(), 0, 100, 100, 100, 0, 0, 0, 0);
            ujKeret->getKimenet()->setStyleSheet("background-color: transparent");
            ujKeret->getKimenet()->setParent(szerkesztoWidget);
            ujKeret->getKimenet()->setPixmap(pixmap);
            ujKeret->getKimenet()->resize(pixmap.size());
            ujKeret->getKimenet()->resize(pixmap.size());
            ujKeret->getKimenet()->move(jelenlegiPoz->first);
            ujKeret->getKimenet()->show();

            //kimenet funkcio
            connect(ujKeret->getKimenet(), &Kimenet::clicked, [=]{
                ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

                if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                {
                    if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                    {
                        jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                    }else{
                        QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                        jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                    }
                }

                jelenlegiProjekt->setJelenlegiElem(ujKeret);
                ujKeret->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));


                //horizontalis mozgatas
                unsigned xPont = ujKeret->getKimenet()->x();
                ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujKeret->getKimenet()->width());
                ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                //vertikalis mozgatas
                unsigned yPont = ujKeret->getKimenet()->y();
                ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujKeret->getKimenet()->height());
                ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

                //meretezes
                ui->kepMeretSpinBoxSzerkeszto->setValue(ujKeret->getMeretArany());

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

            //lista elem
            QPushButton* listaElem = new QPushButton;
            listaElem->setAutoFillBackground(true);
            connect(listaElem, &QPushButton::clicked, [=]{
                ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

                if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                {
                    if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                    {
                        jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                    }else{
                        QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                        jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                    }
                }

                jelenlegiProjekt->setJelenlegiElem(ujKeret);
                ujKeret->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));


                //horizontalis mozgatas
                unsigned xPont = ujKeret->getKimenet()->x();
                ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujKeret->getKimenet()->width());
                ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                //vertikalis mozgatas
                unsigned yPont = ujKeret->getKimenet()->y();
                ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujKeret->getKimenet()->height());
                ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

                //meretezes
                ui->kepMeretSpinBoxSzerkeszto->setValue(ujKeret->getMeretArany());

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

            listaElem->setIcon(pixmap);
            listaElem->setIconSize(QSize(100, 100));

            kepekLista[ujKeret] = listaElem;
            ui->kepListaVerticalLayoutSzerkeszto->addWidget(listaElem);

            //keret projekthez adas
            jelenlegiProjekt->getJelenlegiOldal()->keretHozzaadas(ujKeret);
        }
    }
}

void MainWindow::on_oldalHozaadasPushButtonSzerkeszto_clicked()
{
    if(jelenlegiProjekt->getOldalszam() < 200)
    {
        //oldal letrehozasa
        Oldal* ujOldal = new Oldal(jelenlegiProjekt->getOldalszam()+1);
        jelenlegiProjekt->oldalHozzaadas(ujOldal);

        //oldal beállítása
        ui->oldalszamLabelSzerkeszto->setText(QString::fromStdString("" + to_string(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam()) + "/" + to_string(jelenlegiProjekt->getOldalszam())));
    }else{
        QMessageBox::warning(this, "Figyelmeztetés!", "A projekt oldalszáma már elérte a maximális mennyiséget! Nem lehet több oldalt adni hozzá!");
    }
}

void MainWindow::on_oldalTorlesPushButtonSzerkeszto_clicked()
{
    if(jelenlegiProjekt->getOldalszam() > 1)
    {
        //oldal torles
        jelenlegiProjekt->oldalTorles();

        //oldal beállítása
        if(jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getHatterTipus() == 0)
        {
            QColor szin = jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getSzin();

            //oldalszin
            szerkesztoWidget->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

            //hatterszin
            ui->hatterszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));
        }else{
            Minta minta = jelenlegiProjekt->getJelenlegiOldal()->getStilus()->getMinta();

            //minta beallitas
            szerkesztoWidget->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidget{border-image: url(" + minta.getEleresiUt() + ") 0 0 0 0 stretch stretch;}"));
        }

        ui->oldalszamLabelSzerkeszto->setText(QString::fromStdString("" + to_string(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam()) + "/" + to_string(jelenlegiProjekt->getOldalszam())));

        //listak frissitese
        listaFrissites();
    }else{
        QMessageBox::warning(this, "Figyelmeztetés!", "A projekt oldalszáma már elérte a minimális mennyiséget! Nem lehet több oldalt Törölni!");
    }
}

//menu
void MainWindow::on_bezarasPushButtonSzerkeszto_clicked()
{
    //jelenlegi projekt torlese
    delete jelenlegiProjekt;
    jelenlegiProjekt = nullptr;

    //regi elemek torlese
    for(auto i: kepekLista)
    {
        delete i.second;
    }
    kepekLista.clear();

    for(auto i: belyegekLista)
    {
        delete i.second;
    }
    belyegekLista.clear();

    for(auto i: szovegekLista)
    {
        delete i.second;
    }
    szovegekLista.clear();

    //regi gombok torlese
    for(auto i: gombok)
    {
        delete i;
    }
    gombok.clear();

    //fomenu betoltese
    ui->kepernyoStackedWidget->setCurrentWidget(ui->fomenuKepernyoPage);
}

void MainWindow::on_exportalasPushButtonSzerkeszto_clicked()
{
    ExportWindow* e = new ExportWindow(this);
    if(e->exec() == QDialog::Accepted)
    {
        unsigned oldalakSzama = jelenlegiProjekt->getOldalszam();

        //jelenlegi elem nullazasa
        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->uresPageSzerkeszto);

        jelenlegiProjekt->setJelenlegiElem(nullptr);

        //elore lapozas
        while(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam() != 1)
        {
            ui->lapozasLePushButtonSzerkeszto->click();
        }

        //exportalas
        if(e->getTipus())
        {
            QPrinter printer;
            printer.setFullPage(true);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(QString::fromStdString(e->getUtvonal()+ "/" + jelenlegiProjekt->getNev() + ".pdf"));

            //kep nyomtatas
            QSize oldalMeret(szerkesztoWidget->width()-310, szerkesztoWidget->height()-438);
            printer.setPageSize(QPageSize(oldalMeret));
            QPainter painter(&printer);

            while(true)
            {
                szerkesztoWidget->render(&painter);

                if(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam() < oldalakSzama)
                {
                    ui->lapozasFelPushButtonSzerkeszto->click();
                    printer.newPage();
                }else{
                    break;
                }
            }

        }else{
            QPixmap kimenet(szerkesztoWidget->width(), szerkesztoWidget->height());
            QPainter painter(&kimenet);

            string kiterjesztes;
            if(e->getFormatum())
            {
                kiterjesztes = "jpg";
            }else{
                kiterjesztes = "png";
            }

            while(true)
            {
                szerkesztoWidget->render(&painter);

                QDir dir;
                dir.mkdir(QString::fromStdString(e->getUtvonal() + "/" + jelenlegiProjekt->getNev()));
                QFile file(QString::fromStdString(e->getUtvonal() + "/" + jelenlegiProjekt->getNev() + "/" + to_string(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam()) + "." + kiterjesztes));
                file.open(QIODevice::WriteOnly);
                kimenet.save(&file);
                file.close();

                if(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam() < oldalakSzama)
                {
                    ui->lapozasFelPushButtonSzerkeszto->click();
                }else{
                    break;
                }
            }
        }
    }
}

//------------------------------------------------------------------------------------------
//FOMENU
void MainWindow::on_ujProjektPushButtonFomenu_clicked()
{
    ui->kepernyoStackedWidget->setCurrentWidget(ui->szerkesztoKepernyoPage);
}

void MainWindow::on_projektBetoltesePushButtonFomenu_clicked()
{
    if(kivalasztottProjekt.second != nullptr)
    {
        QFile file(QString::fromStdString(kivalasztottProjekt.first));
        if(file.open(QIODevice::ReadOnly))
        {
            QJsonDocument document = QJsonDocument::fromJson(file.readAll());
            QJsonObject projektObject = document.object();

            Projekt* projekt = new Projekt(projektObject["nev"].toString().toStdString(), kivalasztottProjekt.first);

            //oldalak beallitatsa
            QJsonArray oldalArray = projektObject["oldalak"].toArray();
            for(auto it = oldalArray.begin(); it != oldalArray.end(); ++it)
            {
                QJsonObject oldalObject = it->toObject();
                Oldal* oldal = new Oldal(oldalObject["oldalszam"].toInt());
                QJsonObject stilusObject = oldalObject["stilus"].toObject();
                QJsonObject mintaObject = stilusObject["minta"].toObject();
                QJsonObject szinObject = stilusObject["szin"].toObject();

                //stilus beallitasa
                oldal->getStilus()->setHatterTipus(stilusObject["hatterTipus"].toBool());
                oldal->getStilus()->setMinta(Minta(mintaObject["nev"].toString().toStdString(), mintaObject["eleres"].toString().toStdString()));
                oldal->getStilus()->setSzin(QColor(szinObject["piros"].toInt(), szinObject["zold"].toInt(), szinObject["kek"].toInt()));

                //keretek beallisata
                QJsonArray keretArray = oldalObject["keretek"].toArray();
                for(auto it2 = keretArray.begin(); it2 != keretArray.end(); ++it2)
                {
                    QJsonObject keretObject = it2->toObject();
                    QJsonObject meretObject = keretObject["meret"].toObject();
                    Keret* keret = new Keret(QSize(meretObject["szelesseg"].toInt(), meretObject["magassag"].toInt()), keretObject["eleres"].toString().toStdString(), keretObject["x"].toInt(), keretObject["y"].toInt(), keretObject["dolesszog"].toInt(), keretObject["meretArany"].toInt(), keretObject["szelesseg"].toInt(), keretObject["magassag"].toInt(), keretObject["kepXKoordinata"].toInt(), keretObject["kepYKoordinata"].toInt(), keretObject["szuro"].toInt(), keretObject["kepKeret"].toInt());
                    oldal->keretHozzaadas(keret);
                    keret->kepKeszites();
                    keret->getKimenet()->setParent(szerkesztoWidget);

                    //kimenet funkcio
                    connect(keret->getKimenet(), &Kimenet::clicked, [=]{
                        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

                        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                        {
                            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                            {
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                            }else{
                                QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                            }
                        }

                        jelenlegiProjekt->setJelenlegiElem(keret);
                        keret->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));


                        //horizontalis mozgatas
                        unsigned xPont = keret->getKimenet()->x();
                        ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - keret->getKimenet()->width());
                        ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                        //vertikalis mozgatas
                        unsigned yPont = keret->getKimenet()->y();
                        ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - keret->getKimenet()->height());
                        ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

                        //meretezes
                        ui->kepMeretSpinBoxSzerkeszto->setValue(keret->getMeretArany());

                        //aranyok
                        unsigned szel = keret->getSzelesseg();
                        ui->kepSzelessegSpinBoxSzerkeszto->setValue(szel);

                        unsigned mag = keret->getMagassag();
                        ui->kepMagassagSpinBoxSzerkeszto->setValue(mag);

                        unsigned xKoor = keret->getKepXKoordinata();
                        ui->keparanyHorizontalisSpinBoxSzerkeszto->setMaximum(keret->getMeret().width()*(1-szel/100.0));
                        ui->keparanyHorizontalisSpinBoxSzerkeszto->setValue(xKoor);

                        unsigned yKoor = keret->getKepYKoordinata();
                        ui->keparanyVertikalisSpinBoxSzerkeszto->setMaximum(keret->getMeret().height()*(1-mag/100.0));
                        ui->keparanyVertikalisSpinBoxSzerkeszto->setValue(yKoor);

                        //szuro
                        ui->kepSzuroComboBoxSzerkeszto->setCurrentIndex(keret->getSzuro());
                    });
                }

                //belyegek beallitasa
                QJsonArray belyegArray = oldalObject["belyegek"].toArray();
                for(auto it2 = belyegArray.begin(); it2 != belyegArray.end(); ++it2)
                {
                    QJsonObject belyegObject = it2->toObject();
                    QJsonObject meretObject = belyegObject["meret"].toObject();
                    Belyeg* belyeg = new Belyeg(belyegObject["nev"].toString().toStdString(), QSize(meretObject["szelesseg"].toInt(), meretObject["magassag"].toInt()), belyegObject["eleres"].toString().toStdString(), belyegObject["x"].toInt(), belyegObject["y"].toInt(), belyegObject["dolesszog"].toInt(), belyegObject["meretArany"].toInt());
                    oldal->belyegHozzaadas(belyeg);
                    belyeg->kepKeszites();
                    belyeg->getKimenet()->setParent(szerkesztoWidget);

                    //kimenet funkcio
                    connect(belyeg->getKimenet(), &Kimenet::clicked, [=]{
                        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegPageSzerkeszto);

                        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                        {
                            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                            {
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                            }else{
                                QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                            }
                        }

                        jelenlegiProjekt->setJelenlegiElem(belyeg);
                        belyeg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));

                        //horizontalis mozgatas
                        unsigned xPont = belyeg->getKimenet()->x();
                        ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - belyeg->getKimenet()->width());
                        ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                        //vertikalis mozgatas
                        unsigned yPont = belyeg->getKimenet()->y();
                        ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - belyeg->getKimenet()->height());
                        ui->belyegVertikalisSpinBoxSzerkeszto->setValue(yPont);

                        //meretezes
                        ui->belyegMeretSpinBoxSzerkeszto->setValue(belyeg->getMeretArany());
                    });
                }
                // list<Belyeg*> lista = projekt.getJelenlegiOldal()->getBelyegek();

                //szovegek beallitasa
                QJsonArray szovegArray = oldalObject["szovegek"].toArray();
                for(auto it2 = szovegArray.begin(); it2 != szovegArray.end(); ++it2)
                {
                    QJsonObject szovegObject = it2->toObject();
                    QJsonObject szinObject = szovegObject["szin"].toObject();
                    Szoveg* szoveg = new Szoveg(szovegObject["x"].toInt(), szovegObject["y"].toInt(), szovegObject["dolesszog"].toInt(), szovegObject["tartalom"].toString().toStdString());
                    QColor szin(szinObject["piros"].toInt(), szinObject["zold"].toInt(), szinObject["kek"].toInt());
                    szoveg->setSzin(szin);
                    szoveg->getKimenet()->setStyleSheet(QString::fromStdString("color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

                    QFont font = szoveg->getBetutipus();
                    font.setPointSize(szovegObject["betumeret"].toInt());
                    font.setFamily(szovegObject["betutipus"].toString());
                    font.setBold(szovegObject["felkover"].toBool());
                    font.setItalic(szovegObject["dolt"].toBool());
                    font.setUnderline(szovegObject["alahuzott"].toBool());
                    szoveg->setBetutipus(font);

                    oldal->szovegHozzaadas(szoveg);
                    szoveg->getKimenet()->setParent(szerkesztoWidget);

                    //kimenet funkcio
                    connect(szoveg->getKimenet(), &Kimenet::clicked, [=]{
                        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->szovegPageSzerkeszto);

                        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                        {
                            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != ElemTipus::szoveg)
                            {
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                            }else{
                                Szoveg* jelenlegiSzoveg = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem());
                                QColor szin = jelenlegiSzoveg->getSzin();
                                jelenlegiSzoveg->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                            }
                        }

                        jelenlegiProjekt->setJelenlegiElem(szoveg);
                        QColor szin = szoveg->getSzin();
                        szoveg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS + "color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));

                        //betuszin
                        ui->betuszinWidgetSzerkeszto->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + "); border: 3px inset #bb1133;"));

                        //szoveg
                        ui->szovegTextEditSzerkeszto->setText(QString::fromStdString(szoveg->getTartalom()));

                        //horizontalis mozgatas
                        unsigned xPont = szoveg->getKimenet()->x();
                        ui->szovegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - szoveg->getKimenet()->width());
                        ui->szovegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                        //vertikalis mozgatas
                        unsigned yPont = szoveg->getKimenet()->y();
                        ui->szovegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - szoveg->getKimenet()->height());
                        ui->szovegVertikalisSpinBoxSzerkeszto->setValue(yPont);

                        //betumeret
                        ui->betumeretSpinBoxSzerkeszto->setValue(szoveg->getKimenet()->font().pointSize());

                        //betutipus
                        ui->betutipusComboBoxSzerkeszto->setCurrentFont(szoveg->getBetutipus());

                        //felkover
                        ui->felkoverCheckBoxSzerkeszto->setChecked(szoveg->getBetutipus().bold());

                        //dolt
                        ui->doltCheckBoxSzerkeszto->setChecked(szoveg->getBetutipus().italic());

                        //alahuzott
                        ui->alahuzottCheckBoxSzerkeszto->setChecked(szoveg->getBetutipus().underline());
                    });
                }

                //oldal hozzaadas
                projekt->oldalHozzaadas(oldal);
            }

            //kepek betoltese
            QJsonArray kepekArray = projektObject["kepek"].toArray();
            for(auto it = kepekArray.begin(); it != kepekArray.end(); ++it)
            {
                projekt->addKep(it->toString().toStdString());
            }

            //projekt alkalmazasa
            if(jelenlegiProjekt != nullptr)
            {
                delete jelenlegiProjekt;
            }
            jelenlegiProjekt = projekt;
            listaFrissites();
            jelenlegiProjekt->getJelenlegiOldal()->elemekMutatasa();

            //oldal hatter beallitasa
            if(projekt->getJelenlegiOldal()->getStilus()->getHatterTipus())
            {
                szerkesztoWidget->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidget{border-image: url(" + projekt->getJelenlegiOldal()->getStilus()->getMinta().getEleresiUt() + ") 0 0 0 0 stretch stretch;}"));
            }else{
                QColor szin = projekt->getJelenlegiOldal()->getStilus()->getSzin();
                szerkesztoWidget->setStyleSheet(QString::fromStdString("background-color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
            }

            //belyegek betoltese szerkesztobe
            for(auto i : belyegek)
            {
                QPushButton *tempbutton = new QPushButton;
                tempbutton->setAutoFillBackground(true);
                tempbutton->setStyleSheet("border: 3px outset #c2c2c2;");
                QPixmap pixmap(QString::fromStdString(i.second));

                tempbutton->setIcon(pixmap);
                tempbutton->setIconSize(QSize(100, 100));

                ui->belyegekVerticalLayoutSzerkeszto->addWidget(tempbutton);
                gombok.push_back(tempbutton);

                //funkcio hozzaadas a belyeg gombnak
                connect(tempbutton, &QPushButton::clicked, [=]{
                    Belyeg *ujBelyeg = new Belyeg(i.first, pixmap.size(), i.second, 0, 0, 0, 100);
                    ujBelyeg->getKimenet()->setStyleSheet("background-color: transparent");
                    ujBelyeg->getKimenet()->setParent(szerkesztoWidget);
                    ujBelyeg->getKimenet()->setPixmap(pixmap);
                    ujBelyeg->getKimenet()->resize(pixmap.size());
                    ujBelyeg->getKimenet()->resize(pixmap.size());
                    ujBelyeg->getKimenet()->show();

                    //kimenet funkcio
                    connect(ujBelyeg->getKimenet(), &Kimenet::clicked, [=]{
                        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegPageSzerkeszto);

                        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                        {
                            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                            {
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                            }else{
                                QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                            }
                        }

                        jelenlegiProjekt->setJelenlegiElem(ujBelyeg);
                        ujBelyeg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));

                        //horizontalis mozgatas
                        unsigned xPont = ujBelyeg->getKimenet()->x();
                        ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujBelyeg->getKimenet()->width());
                        ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                        //vertikalis mozgatas
                        unsigned yPont = ujBelyeg->getKimenet()->y();
                        ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujBelyeg->getKimenet()->height());
                        ui->belyegVertikalisSpinBoxSzerkeszto->setValue(yPont);

                        //meretezes
                        ui->belyegMeretSpinBoxSzerkeszto->setValue(ujBelyeg->getMeretArany());
                    });

                    //lista elem
                    QPushButton* listaElem = new QPushButton;
                    listaElem->setAutoFillBackground(true);
                    listaElem->setStyleSheet("border: 3px outset #c2c2c2;");

                    connect(listaElem, &QPushButton::clicked, [=]{
                        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->belyegPageSzerkeszto);

                        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                        {
                            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                            {
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                            }else{
                                QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                            }
                        }

                        jelenlegiProjekt->setJelenlegiElem(ujBelyeg);
                        ujBelyeg->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));

                        //horizontalis mozgatas
                        unsigned xPont = ujBelyeg->getKimenet()->x();
                        ui->belyegHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujBelyeg->getKimenet()->width());
                        ui->belyegHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                        //vertikalis mozgatas
                        unsigned yPont = ujBelyeg->getKimenet()->y();
                        ui->belyegVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujBelyeg->getKimenet()->height());
                        ui->belyegVertikalisSpinBoxSzerkeszto->setValue(yPont);

                        //meretezes
                        ui->belyegMeretSpinBoxSzerkeszto->setValue(ujBelyeg->getMeretArany());
                    });

                    listaElem->setIcon(pixmap);
                    listaElem->setIconSize(QSize(100, 100));

                    belyegekLista[ujBelyeg] = listaElem;
                    ui->belyegListaVerticalLayoutSzerkeszto->addWidget(listaElem);

                    //belyeg projekthez adas
                    jelenlegiProjekt->getJelenlegiOldal()->belyegHozzaadas(ujBelyeg);
                });
            }

            //mintak betoltese szerkesztobe
            for(auto i : mintak)
            {
                QPushButton *tempbutton = new QPushButton;
                tempbutton->setAutoFillBackground(true);
                tempbutton->setStyleSheet("border: 3px outset #c2c2c2;");
                QPixmap pixmap(QString::fromStdString(i.second));

                tempbutton->setIcon(pixmap);
                tempbutton->setIconSize(QSize(200, 200));

                ui->mintakVerticalLayoutSzerkeszto->addWidget(tempbutton);
                gombok.push_back(tempbutton);

                //funkcio hozzaadas a minta gombnak
                connect(tempbutton, &QPushButton::clicked, [=]{
                    Minta ujMinta = Minta(i.first, i.second);

                    jelenlegiProjekt->getJelenlegiOldal()->getStilus()->setMinta(ujMinta);
                    jelenlegiProjekt->getJelenlegiOldal()->getStilus()->setHatterTipus(1);

                    szerkesztoWidget->setStyleSheet(QString::fromStdString("QWidget#szerkesztoWidget{border-image: url(" + i.second + ") 0 0 0 0 stretch stretch;}"));
                });
            }

            //kepek betoltese szerkesztobe
            list<string> kepLista = jelenlegiProjekt->getKepek();
            for(string i : kepLista)
            {
                cout << i << endl;
                QPushButton *tempbutton = new QPushButton;
                tempbutton->setStyleSheet("border: 3px outset #c2c2c2;");
                QPixmap pixmap(QString::fromStdString(i));

                tempbutton->setIcon(pixmap);
                tempbutton->setIconSize(QSize(100, 100));

                ui->kepekVerticalLayoutSzerkeszto->addWidget(tempbutton);
                gombok.push_back(tempbutton);

                //funkcio hozzaadas a kep gombnak
                connect(tempbutton, &QPushButton::clicked, [=]{
                    Keret *ujKeret = new Keret(pixmap.size(), i, 0, 0, 0, 100, 100, 100, 0, 0, 0, 0);
                    ujKeret->getKimenet()->setStyleSheet("background-color: transparent");
                    ujKeret->getKimenet()->setParent(szerkesztoWidget);
                    ujKeret->getKimenet()->setPixmap(pixmap);
                    ujKeret->getKimenet()->resize(pixmap.size());
                    ujKeret->getKimenet()->resize(pixmap.size());
                    ujKeret->getKimenet()->show();

                    //kimenet funkcio
                    connect(ujKeret->getKimenet(), &Kimenet::clicked, [=]{
                        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

                        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                        {
                            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                            {
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                            }else{
                                QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                            }
                        }

                        jelenlegiProjekt->setJelenlegiElem(ujKeret);
                        ujKeret->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));


                        //horizontalis mozgatas
                        unsigned xPont = ujKeret->getKimenet()->x();
                        ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujKeret->getKimenet()->width());
                        ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                        //vertikalis mozgatas
                        unsigned yPont = ujKeret->getKimenet()->y();
                        ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujKeret->getKimenet()->height());
                        ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

                        //meretezes
                        ui->kepMeretSpinBoxSzerkeszto->setValue(ujKeret->getMeretArany());

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

                    //lista elem
                    QPushButton* listaElem = new QPushButton;
                    listaElem->setAutoFillBackground(true);
                    listaElem->setStyleSheet("border: 3px outset #c2c2c2;");

                    connect(listaElem, &QPushButton::clicked, [=]{
                        ui->tulajdonsagokStackedWidgetSzerkeszto->setCurrentWidget(ui->kepPageSzerkeszto);

                        if(jelenlegiProjekt->getJelenlegiElem() != nullptr)
                        {
                            if(jelenlegiProjekt->getJelenlegiElem()->getTipus() != szoveg)
                            {
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet("background-color: transparent");
                            }else{
                                QColor szin = dynamic_cast<Szoveg*>(jelenlegiProjekt->getJelenlegiElem())->getSzin();
                                jelenlegiProjekt->getJelenlegiElem()->getKimenet()->setStyleSheet(QString::fromStdString("background-color: transparent; color: rgba(" + to_string(szin.red()) + "," + to_string(szin.green()) + "," + to_string(szin.blue()) + "," + to_string(szin.alphaF()) + ");"));
                            }
                        }

                        jelenlegiProjekt->setJelenlegiElem(ujKeret);
                        ujKeret->getKimenet()->setStyleSheet(QString::fromStdString(kijeloltElemQSS));


                        //horizontalis mozgatas
                        unsigned xPont = ujKeret->getKimenet()->x();
                        ui->kepHorizontalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->width() - ujKeret->getKimenet()->width());
                        ui->kepHorizontalisSpinBoxSzerkeszto->setValue(xPont);

                        //vertikalis mozgatas
                        unsigned yPont = ujKeret->getKimenet()->y();
                        ui->kepVertikalisSpinBoxSzerkeszto->setMaximum(szerkesztoWidget->height() - ujKeret->getKimenet()->height());
                        ui->kepVertikalisSpinBoxSzerkeszto->setValue(yPont);

                        //meretezes
                        ui->kepMeretSpinBoxSzerkeszto->setValue(ujKeret->getMeretArany());

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

                    listaElem->setIcon(pixmap);
                    listaElem->setIconSize(QSize(100, 100));

                    kepekLista[ujKeret] = listaElem;
                    ui->kepListaVerticalLayoutSzerkeszto->addWidget(listaElem);

                    //keret projekthez adas
                    jelenlegiProjekt->getJelenlegiOldal()->keretHozzaadas(ujKeret);
                });
            }

            //oldal beállítása
            ui->oldalszamLabelSzerkeszto->setText(QString::fromStdString("" + to_string(jelenlegiProjekt->getJelenlegiOldal()->getOldalszam()) + "/" + to_string(jelenlegiProjekt->getOldalszam())));

            //szerkeszto oldal betoltese
            ui->kepernyoStackedWidget->setCurrentWidget(ui->szerkesztoKepernyoPage);

            file.close();
        }
    }else{
        QMessageBox::warning(this, "Figyelem!", "Nincs kiválasztva projekt!");
    }
}

void MainWindow::on_belyegekPushButtonFomenu_clicked()
{
    ui->kepernyoStackedWidget->setCurrentWidget(ui->belyegekKepernyoPage);
}

void MainWindow::on_mintakPushButtonFomenu_clicked()
{
    ui->kepernyoStackedWidget->setCurrentWidget(ui->mintakKepernyoPage);
}

void MainWindow::on_projektTorlesePushButtonFomenu_clicked()
{

}

void MainWindow::on_kilepesPushButtonFomenu_clicked()
{
    QCoreApplication::quit();
}

//------------------------------------------------------------------------------------------
//BELYEGEK
void MainWindow::on_ujBelyegPushButtonBelyeg_clicked()
{

}

void MainWindow::on_belyegTorlesePushButtonBelyeg_clicked()
{

}

void MainWindow::on_visszalepesPushButtonBelyeg_clicked()
{
    ui->kepernyoStackedWidget->setCurrentWidget(ui->fomenuKepernyoPage);
}

//------------------------------------------------------------------------------------------
//MINTAK
void MainWindow::on_ujMintaPushButtonMinta_clicked()
{

}

void MainWindow::on_mintaTorlesePushButtonMinta_clicked()
{

}

void MainWindow::on_visszalepesPushButtonMinta_clicked()
{
    ui->kepernyoStackedWidget->setCurrentWidget(ui->fomenuKepernyoPage);
}
