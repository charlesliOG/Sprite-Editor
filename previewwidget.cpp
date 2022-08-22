#include "previewwidget.h"
#include <QPainter>
#include <iostream>

previewwidget::previewwidget(QWidget *parent)
    : QWidget{parent}
    ,image()
{

}

void previewwidget::showFrame(QImage* image)
{
    this->image = image;
    setMinimumSize(image->width(), image->height());
    update();
}

QSize previewwidget::getScaledImageSize() {
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

void previewwidget::paintEvent(QPaintEvent *event) {
    if (image) {
        QPainter painter(this);

        QImage scaledImg = image->scaled(getScaledImageSize()); // this scales the pixels to the widget window
        painter.drawImage(width() / 2 - scaledImg.width() / 2, height()/2 - scaledImg.height() / 2, scaledImg);
    }
}
