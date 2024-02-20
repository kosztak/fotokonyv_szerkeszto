#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>

#include <iostream>

class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomView(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~CustomView();

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // CUSTOMVIEW_H
