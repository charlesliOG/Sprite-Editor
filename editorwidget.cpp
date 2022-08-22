#include "editorwidget.h"
#include <iostream>
#include <QPainter>
#include <QMouseEvent>

EditorWidget::EditorWidget(QWidget *parent)
    : QWidget{parent}
    , image()
{

}

void EditorWidget::onImageUpdate(int frameIndex, QImage* image) {
    this->image = image;
    setMinimumSize(image->width(), image->height());
    update();
}

void EditorWidget::mousePressEvent(QMouseEvent *event) {
    mousePressed = true;
    emit drawPixel(toImagePos(event->position()));
    mousePosPrev = event->position();
}

void EditorWidget::mouseReleaseEvent(QMouseEvent *event){
    mousePressed = false;
}

void EditorWidget::mouseMoveEvent(QMouseEvent *event){
    if (mousePressed) {
        QPointF mousePos = event->position();
        if (mousePosPrev == mousePos) {
            emit drawPixel(toImagePos(event->position()));
        } else {
            emit drawLine(toImagePos(mousePosPrev), toImagePos(mousePos));
        }
        mousePosPrev = event->position();
    }
}

void EditorWidget::paintEvent(QPaintEvent *event) {
    if (image) {
        QPainter painter(this);

        QImage scaledImg = image->scaled(getScaledImageSize()); // this scales the pixels to the widget window
        painter.drawImage(width() / 2 - scaledImg.width() / 2, height()/2 - scaledImg.height() / 2, scaledImg);
    }
}

QSize EditorWidget::getScaledImageSize() {
    double editorAspect = (double) width() / height();
    double imageAspect = (double) image->width() / image->height();

    double scale;
    if (editorAspect >= imageAspect) {
        scale = (double) height() / image->height();
    } else {
        scale = (double) width() / image->width();
    }

    return QSize(image->width() * scale, image->height() * scale);
}

QPointF EditorWidget::toImagePos(QPointF mousePos) {
    QSize scaledSize = getScaledImageSize();
    QPoint imageTopLeft(width() / 2 - scaledSize.width() / 2, height()/2 - scaledSize.height() / 2);
    mousePos -= imageTopLeft;

    mousePos.setX(mousePos.x() / scaledSize.width() * image->width());
    mousePos.setY(mousePos.y() / scaledSize.height() * image->height());
    return mousePos;
}
