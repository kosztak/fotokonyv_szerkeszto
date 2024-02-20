#include "customview.h"

CustomView::CustomView(QWidget* parent, Qt::WindowFlags f)
    : QGraphicsView(parent) {

}

CustomView::~CustomView() {}

void CustomView::resizeEvent(QResizeEvent *event)
{
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
