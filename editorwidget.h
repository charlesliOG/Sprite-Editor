#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>

class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = nullptr);

signals:
    void drawPixel(QPointF pos);
    void drawLine(QPointF pos1, QPointF pos2);

public slots:
    void onImageUpdate(int frameIndex, QImage* image);

private:
    QImage* image;
    bool mousePressed = false; // to keep track if the mouse is being held down or not
    QPointF mousePosPrev; // mouse position of the previous frame

    void paintEvent(QPaintEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    QSize getScaledImageSize();
    QPointF toImagePos(QPointF mousePos);
};

#endif // EDITORWIDGET_H
