#include "keretvalaszto.h"
#include "ui_keretvalaszto.h"


KeretValaszto::KeretValaszto(QWidget *parent, unsigned short jelenlegi)
    : QDialog(parent)
    , ui(new Ui::KeretValaszto)
    , index(jelenlegi)
{
    ui->setupUi(this);

    inicializalas();
}

void KeretValaszto::inicializalas()
{
    QPushButton *tempbutton = new QPushButton();
    tempbutton->setAutoFillBackground(true);
    tempbutton->setStyleSheet("background-color: #ffffff; border: 3px outset #c2c2c2;");

    QPixmap pixmap(128, 128);
    QPainter imagePainter(&pixmap);
    image.render(&imagePainter);
    imagePainter.end();

    tempbutton->setIconSize(QSize(128, 128));
    tempbutton->setIcon(pixmap);

    ui->keretekGridLayout->addWidget(tempbutton, 0, 0);

    //funkcio hozzaadas a keret gombnak
    connect(tempbutton, &QPushButton::clicked, [=]{
        index = 0;
    });

    int counter = 1;
    for(unsigned short i = 1; i <= 2; ++i)
    {
        tempbutton = new QPushButton();
        tempbutton->setAutoFillBackground(true);
        tempbutton->setStyleSheet("background-color: #ffffff; border: 3px outset #c2c2c2;");

        QImage temp = pixmap.toImage().convertToFormat(QImage::Format_ARGB32);

        if(i < 2) //rahelyezes
        {
            QPainter painter(&temp);
            QSvgRenderer renderer(QString::fromStdString("./keretek/" + std::to_string(i) + ".svg"));
            renderer.render(&painter);

        }else{ //kivagas
            QPixmap maskMap(temp.size());
            maskMap.fill(Qt::transparent);
            QPainter painter(&maskMap);
            QSvgRenderer renderer(QString::fromStdString("./keretek/" + std::to_string(i) + ".svg"));
            renderer.render(&painter);

            QImage maskImg = maskMap.toImage();

            QColor color;
            for(unsigned i = 0; i < 128; ++i)
            {
                for(unsigned j = 0; j < 128; ++j)
                {
                    color = maskImg.pixelColor(i,j);

                    if(color.alpha() == 0)
                    {
                        temp.setPixelColor(i, j, Qt::transparent);
                    }
                }
            }
        }

        tempbutton->setIconSize(QSize(128, 128));
        tempbutton->setIcon(QPixmap::fromImage(temp));

        ui->keretekGridLayout->addWidget(tempbutton, counter/3, counter%3);

        ++counter;

        //funkcio hozzaadas a keret gombnak
        connect(tempbutton, &QPushButton::clicked, [=]{
            index = i;
        });
    }

    index = 1000;
}

unsigned short KeretValaszto::getIndex()
{
    return index;
}

KeretValaszto::~KeretValaszto()
{
    delete ui;
}

void KeretValaszto::on_valasztPushButton_clicked()
{
    accept();
}


void KeretValaszto::on_megsePushButton_clicked()
{
    reject();
}

