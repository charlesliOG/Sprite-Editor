#include "sprite.h"
#include <iostream>
#include <QImage>
#include <QPoint>

Sprite::Sprite(QObject *parent)
    : QObject{parent}
    , frames()
{

}

QImage* Sprite::getFrame(int frameIndex) {
    return frames[frameIndex];
}

void Sprite::plotPoint(QImage *frame, int x, int y, QRgb color) {
    if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight())
        frame->setPixel(x, y, color);
}

void Sprite::drawPixel(int frameIndex, QPointF pos, QRgb color) {
    QImage* frame = getFrame(frameIndex);
    plotPoint(frame, pos.x(), pos.y(), color);
}

void Sprite::drawLine(int frameIndex, QPointF pos1, QPointF pos2, QRgb color) {
    QImage* frame = getFrame(frameIndex);

    // Line algorithm courtesy of https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    if (std::abs(pos2.y() - pos1.y()) < std::abs(pos2.x() - pos1.x())) {
        if (pos1.x() > pos2.x()) {
            plotLineLow(frame, pos2.x(), pos2.y(), pos1.x(), pos1.y(), color);
        } else {
            plotLineLow(frame, pos1.x(), pos1.y(), pos2.x(), pos2.y(), color);
        }
    } else {
        if (pos1.y() > pos2.y()) {
            plotLineHigh(frame, pos2.x(), pos2.y(), pos1.x(), pos1.y(), color);
        } else {
            plotLineHigh(frame, pos1.x(), pos1.y(), pos2.x(), pos2.y(), color);
        }
    }
}

void Sprite::plotLineLow(QImage* frame, int x1, int y1, int x2, int y2, QRgb color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = 2 * dy - dx;
    int y = y1;

    for (int x = x1; x <= x2; ++x) {
        plotPoint(frame, x, y, color);
        if (D > 0) {
            y += yi;
            D += 2 * (dy - dx);
        } else {
            D += 2 * dy;
        }
    }
}

void Sprite::plotLineHigh(QImage* frame, int x1, int y1, int x2, int y2, QRgb color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x1;

    for (int y = y1; y <= y2; ++y) {
        plotPoint(frame, x, y, color);
        if (D > 0) {
            x += xi;
            D += 2 * (dx - dy);
        } else {
            D += 2 * dx;
        }
    }
}

int Sprite::createFrame() {
    QImage* image = new QImage(width, height, IMAGE_FORMAT);
    image->fill(qRgba(0, 0, 0, 0));
    frames.push_back(image);
    return getFrameCount() - 1;
}

void Sprite::deleteFrame(int frameIndex) {
    QImage* frame = getFrame(frameIndex);
    frames.erase(frames.begin() + frameIndex);
    delete frame;
}

void Sprite::setSize(int w, int h) {
    width = w;
    height = h;
}

int Sprite::getFrameCount() {
    return frames.size();
}

int Sprite::getWidth() {
    return width;
}

int Sprite::getHeight() {
    return height;
}
