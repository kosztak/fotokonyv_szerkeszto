#include "kimenet.h"

Kimenet::Kimenet(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

Kimenet::~Kimenet() {}

void Kimenet::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();

    }else if(event->button() == Qt::RightButton && this->geometry().contains(event->pos()))
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        // mimeData->setData("ptr", );
        QPixmap pixmap = QPixmap(this->size());
        QPainter painter = QPainter(&pixmap);
        pixmap.fill(Qt::transparent);
        this->render(&painter);

        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);

        Qt::DropAction dropAction = drag->exec();
    }
}
