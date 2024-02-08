#include "keret.h"
#include <iostream>

void Keret::kepKeszites()
{
    QPixmap ujKep = forras.copy(kepXKoordinata, kepYKoordinata, meret.width()*(szelesseg/100.0), meret.height()*(magassag/100.0));

    //meretezes
    if(meretArany != 100)
    {
        ujKep = ujKep.scaled(ujKep.width()*(meretArany/100.0), ujKep.height()*(meretArany/100.0));
    }

    //szuro felhelyezes
    if(szuro == 1) //fekete-feher
    {
        QImage temp = ujKep.toImage().convertToFormat(QImage::Format_ARGB32);
        unsigned width = temp.width();
        unsigned height = temp.height();

        QRgb color;

        for(unsigned i = 0; i < width; ++i)
        {
            for(unsigned j = 0; j < height; ++j)
            {
                color = temp.pixel(i,j);
                int gray = qGray(color);
                temp.setPixel(i, j, qRgb(gray, gray, gray));
            }
        }

        ujKep = QPixmap::fromImage(temp);

    }else if(szuro == 2){ //szepia
        QImage temp = ujKep.toImage().convertToFormat(QImage::Format_ARGB32);
        unsigned width = temp.width();
        unsigned height = temp.height();

        QColor color;

        for(unsigned i = 0; i < width; ++i)
        {
            for(unsigned j = 0; j< height; ++j)
            {
                color = temp.pixel(i,j);

                int tr = color.red()*0.393 + color.green()*0.769 + color.blue()*0.189;
                int tg = color.red()*0.343 + color.green()*0.686 + color.blue()*0.168;
                int tb = color.red()*0.272 + color.green()*0.534 + color.blue()*0.131;

                temp.setPixel(i, j, qRgb(tr>255?255:tr, tg>255?255:tg, tb>255?255:tb));
            }
        }

        ujKep = QPixmap::fromImage(temp);
    }

    //keret felhelyezes
    if(kepKeret != 0)
    {
        QImage temp = ujKep.toImage().convertToFormat(QImage::Format_ARGB32);

        if(kepKeret < 2) //rahelyezes
        {
            QPainter painter(&temp);
            QSvgRenderer renderer(QString::fromStdString("./keretek/" + to_string(kepKeret) + ".svg"));
            renderer.render(&painter);

        }else{ //kivagas
            QPixmap maskMap(temp.size());
            maskMap.fill(Qt::transparent);
            QPainter painter(&maskMap);
            QSvgRenderer renderer(QString::fromStdString("./keretek/" + to_string(kepKeret) + ".svg"));
            renderer.render(&painter);

            unsigned width = temp.width();
            unsigned height = temp.height();

            QImage maskImg = maskMap.toImage();

            QColor color;
            for(unsigned i = 0; i < width; ++i)
            {
                for(unsigned j = 0; j < height; ++j)
                {
                    color = maskImg.pixelColor(i,j);

                    if(color.alpha() == 0)
                    {
                        temp.setPixelColor(i, j, Qt::transparent);
                    }
                }
            }
        }

        ujKep = QPixmap::fromImage(temp);
    }

    kimenet->resize(ujKep.size());
    kimenet->setIcon(ujKep);
}

const QPixmap &Keret::getKep() const
{
    return kep;
}

void Keret::setKeret(unsigned short index)
{
    kepKeret = index;
}

unsigned short Keret::getKeret() const
{
    return kepKeret;
}

unsigned short Keret::getSzelesseg() const
{
    return szelesseg;
}

void Keret::setSzelesseg(unsigned short newSzelesseg)
{
    szelesseg = newSzelesseg;
}

unsigned short Keret::getMagassag() const
{
    return magassag;
}

void Keret::setMagassag(unsigned short newMagassag)
{
    magassag = newMagassag;
}

unsigned int Keret::getKepXKoordinata() const
{
    return kepXKoordinata;
}

void Keret::setKepXKoordinata(unsigned int newKepXKoordinata)
{
    kepXKoordinata = newKepXKoordinata;
}

unsigned int Keret::getKepYKoordinata() const
{
    return kepYKoordinata;
}

void Keret::setKepYKoordinata(unsigned int newKepYKoordinata)
{
    kepYKoordinata = newKepYKoordinata;
}

unsigned short Keret::getSzuro() const
{
    return szuro;
}

void Keret::setSzuro(unsigned short newSzuro)
{
    szuro = newSzuro;
}

Keret::Keret(const QSize &meret, const QPixmap &forras, const unsigned &xKoordinata, const unsigned &yKoordinata, int dolesszog, unsigned short meretArany, unsigned short szelesseg, unsigned short magassag, unsigned kepXKoordinata, unsigned kepYKoordinata, unsigned short szuro, unsigned short kepKeret) : Abra(meret, forras, xKoordinata, yKoordinata, dolesszog, meretArany),
    szelesseg(szelesseg), magassag(magassag), kepXKoordinata(kepXKoordinata), kepYKoordinata(kepYKoordinata), szuro(szuro), kepKeret(kepKeret)
{
    tipus = keret;
}
