#ifndef KERETVALASZTO_H
#define KERETVALASZTO_H

#include <QDialog>
#include <QtSvg/QSvgRenderer>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <string>

namespace Ui {
class KeretValaszto;
}

class KeretValaszto : public QDialog
{
    Q_OBJECT

    //rendszer
    void inicializalas();

public:
    explicit KeretValaszto(QWidget *parent = nullptr, unsigned short jelenlegi = 0);
    ~KeretValaszto();
    unsigned short getIndex();

private slots:
    void on_valasztPushButton_clicked();

    void on_megsePushButton_clicked();

private:
    Ui::KeretValaszto *ui;

    //rendszer
    QPushButton* jelenlegiButton = nullptr;
    unsigned short index;
    QSvgRenderer image = QSvgRenderer(QString::fromStdString("./image.svg"));
};

#endif // KERETVALASZTO_H
