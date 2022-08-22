#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QImage>
#include <QRgb>
#include <QPoint>

class Sprite : public QObject
{
    Q_OBJECT
public:
    explicit Sprite(QObject *parent = nullptr);

    QImage* getFrame(int frameIndex);
    void drawPixel(int frameIndex, QPointF pos, QRgb color);
    void drawLine(int frameIndex, QPointF pos1, QPointF pos2, QRgb color);

    int createFrame();
    void deleteFrame(int frameIndex);

    void setSize(int w, int h);
    int getFrameCount();
    int getWidth();
    int getHeight();

private:
    QImage::Format IMAGE_FORMAT = QImage::Format::Format_ARGB32;

    int width, height;
    std::vector<QImage*> frames;

    void plotPoint(QImage* frame, int x, int y, QRgb color);
    void plotLineLow(QImage* frame, int x1, int y1, int x2, int y2, QRgb color);
    void plotLineHigh(QImage* frame, int x1, int y1, int x2, int y2, QRgb color);

signals:

};

#endif // SPRITE_H
