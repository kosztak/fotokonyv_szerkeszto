#include "kimenet.h"

Kimenet::Kimenet(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

Kimenet::~Kimenet() {}

void Kimenet::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
