#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "model.h"
#include "editorwidget.h"
#include <QPainter>
#include <iostream>
#include <QImage>
#include <QPushButton>
#include <realpreviewwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(Model& model, QWidget *parent = nullptr);
    ~View();

signals:
    void setEditedFrame(int frameIndex);

public slots:
    void onImageUpdate(int frameIndex, QImage* image);
    void onFrameCreated(QImage* image);
    void onFrameDeleted(int frameIndex);
    void onFrameButtonPressed(QPushButton* btn);

private slots:
    void on_previewButton_clicked();

private:
    Ui::View *ui;
    realPreviewWindow previewWindow;

};
#endif // VIEW_H
