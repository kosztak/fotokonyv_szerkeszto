#ifndef KIMENET_H
#define KIMENET_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class Kimenet : public QLabel {
    Q_OBJECT

public:
    explicit Kimenet(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~Kimenet();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // KIMENET_H