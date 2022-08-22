#ifndef REALPREVIEWWINDOW_H
#define REALPREVIEWWINDOW_H

#include <QDialog>
#include "previewwidget.h"

namespace Ui {
class realPreviewWindow;
}

class realPreviewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit realPreviewWindow(QWidget *parent = nullptr);
    ~realPreviewWindow();

    previewwidget* getCanvas();


signals:
    void previewWindowClose();
    void sendFPStoModel(int fps);

public slots:
    void closeEvent(QCloseEvent *);
    void on_pushButton_clicked();



private slots:
    void on_frameCounter_valueChanged(int arg1);

private:
    Ui::realPreviewWindow *ui;
};

#endif // REALPREVIEWWINDOW_H
