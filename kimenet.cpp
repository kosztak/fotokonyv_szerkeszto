#include "kimenet.h"

Kimenet::Kimenet(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

Kimenet::~Kimenet() {

}

void Kimenet::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
        offset = event->pos();

    }
}

void Kimenet::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QWidget* parent = dynamic_cast<QWidget*>(this->parent());
        QPoint uj = mapToParent(event->pos() - offset);
        if(uj.x() < 0)
            uj.setX(0);

        if(uj.y() < 0)
            uj.setY(0);

        if((uj.x() > (parent->width() - this->width())))
            uj.setX(parent->width() - this->width());

        if((uj.y() > (parent->height() - this->height())))
            uj.setY(parent->height() - this->height());

        this->move(uj);
    }
}
