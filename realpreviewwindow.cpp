#include "realpreviewwindow.h"
#include "ui_realpreviewwindow.h"
#include <iostream>

realPreviewWindow::realPreviewWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::realPreviewWindow)
{
    ui->setupUi(this);


}

previewwidget* realPreviewWindow::getCanvas()
{
    return ui->canvas;
}

realPreviewWindow::~realPreviewWindow()
{
    delete ui;
}

void realPreviewWindow::on_pushButton_clicked()
{
    emit previewWindowClose();
    this->hide();

}

void realPreviewWindow::closeEvent(QCloseEvent *)
{
    emit previewWindowClose();
    this->hide();
}


void realPreviewWindow::on_frameCounter_valueChanged(int fps)
{
    std::cout<<fps<<std::endl;
    emit sendFPStoModel(fps);
}

