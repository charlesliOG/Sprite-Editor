#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

class previewwidget : public QWidget
{
    Q_OBJECT
public:
    explicit previewwidget(QWidget *parent = nullptr);

public slots:
    void showFrame(QImage* image);


private:
    void paintEvent(QPaintEvent *event);
    QSize getScaledImageSize();

    QImage* image;

signals:

};

#endif // PREVIEWWIDGET_H
