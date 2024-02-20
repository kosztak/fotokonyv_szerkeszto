#ifndef KIMENET_H
#define KIMENET_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QColor>
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
    void mouseMoveEvent(QMouseEvent* event);

private:
    QPoint offset;
};

#endif // KIMENET_H
