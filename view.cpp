#include "view.h"
#include "ui_view.h"

View::View(Model& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{


    ui->setupUi(this);

    //preview window connections
    connect(ui->previewButton, &QPushButton::clicked, &model, &Model::setPreviewWindow);
    connect(&model, &Model::sendFramesToPreview, previewWindow.getCanvas(), &previewwidget::showFrame);
    connect(&previewWindow, &realPreviewWindow::previewWindowClose, &model, &Model::stopCycleFrames);
    connect(&previewWindow, &realPreviewWindow::sendFPStoModel, &model, &Model::setFPS);


    connect(ui->primaryColorButton, &QPushButton::clicked, &model, &Model::choosePrimaryColor);
    connect(ui->secondaryColorButton, &QPushButton::clicked, &model, &Model::chooseSecondaryColor);
    connect(ui->switchColorButton, &QPushButton::clicked, &model, &Model::switchColors);
    connect(ui->createFrameButton, &QPushButton::clicked, &model, &Model::createFrame);
    connect(ui->deleteFrameButton, &QPushButton::clicked, &model, &Model::deleteFrame);
    connect(this, &View::setEditedFrame, &model, &Model::setEditedFrame);

    connect(ui->canvas, &EditorWidget::drawPixel, &model, &Model::drawPixel);
    connect(ui->canvas, &EditorWidget::drawLine, &model, &Model::drawLine);

    connect(&model, &Model::updateImage, ui->canvas, &EditorWidget::onImageUpdate);
    connect(&model, &Model::updateImage, this, &View::onImageUpdate);
    connect(&model, &Model::onFrameCreated, this, &View::onFrameCreated);
    connect(&model, &Model::onFrameDeleted, this, &View::onFrameDeleted);

    // connect prim/secon color bg changes
    connect(&model, &Model::changePrimColorBg, ui->primaryColorButton, &QPushButton::setStyleSheet);
    connect(&model, &Model::changeSecColorBg, ui->secondaryColorButton, &QPushButton::setStyleSheet);

    // connect brush type buttons
    connect(ui->pencilButton, &QPushButton::clicked, &model, &Model::pencilButtonClick);
    connect(ui->eraserButton, &QPushButton::clicked, &model, &Model::eraserButtonClick);

    // update initial frame in the editor widget
    ui->canvas->onImageUpdate(0, model.getFrame());
    // update initial frame in frame buttons
    onFrameCreated(model.getFrame());
}

void View::onImageUpdate(int frameIndex, QImage* image) {
    QLayout* layout = ui->framesScrollAreaWidgetContent->layout();
    QPushButton* btn = (QPushButton*) layout->itemAt(frameIndex)->widget();
    QPixmap pixmap = QPixmap::fromImage(*image).scaled(60, 60);
    QIcon icon(pixmap);
    btn->setIcon(icon);
}

void View::onFrameCreated(QImage* image) {
    QLayout* layout = ui->framesScrollAreaWidgetContent->layout();

    QSpacerItem* spacer = ui->horizontalSpacer;
    layout->removeItem(ui->horizontalSpacer);

    QPushButton* btn = new QPushButton(ui->framesScrollAreaWidgetContent);
    btn->setFixedSize(70, 70);
    btn->setContentsMargins(0, 0, 0, 0);

    QPixmap pixmap = QPixmap::fromImage(*image).scaled(60, 60);
    QIcon icon(pixmap);
    btn->setIconSize(pixmap.size());
    btn->setIcon(icon);

    layout->addWidget(btn);
    layout->addItem(spacer);

    connect(btn, &QPushButton::clicked, this, [this, btn] { onFrameButtonPressed(btn); });
}

void View::onFrameDeleted(int frameIndex) {
    QLayout* layout = ui->framesScrollAreaWidgetContent->layout();
    QPushButton* btn = (QPushButton*) layout->itemAt(frameIndex)->widget();

    layout->removeWidget(btn);
    delete btn;
}

void View::onFrameButtonPressed(QPushButton* btn) {
    QLayout* layout = ui->framesScrollAreaWidgetContent->layout();
    int frameIndex = layout->indexOf(btn);

    emit setEditedFrame(frameIndex);
}

View::~View()
{
    delete ui;
}


void View::on_previewButton_clicked()
{
    previewWindow.show();
}

