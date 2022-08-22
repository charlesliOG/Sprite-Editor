#include "model.h"
#include <QColorDialog>
#include <iostream>
#include <QTimer>

Model::Model(QObject *parent)
    : QObject{parent}
    , sprite(new Sprite())
    , editedFrame(0)
    , primaryColor(qRgba(0, 0, 0, 255))
    , secondaryColor(qRgba(255, 255, 255, 255))
{
    previewFrameIndex = 0;
    previewWindowIsOpen = false;
    framesPerSecond = 5;

    sprite->setSize(64, 64);
    sprite->createFrame();

    emit updateImage(editedFrame, getFrame());
}

QImage* Model::getFrame() {
    return getFrame(editedFrame);
}

QImage* Model::getFrame(int frameIndex) {
    return sprite->getFrame(frameIndex);
}

void Model::drawPixel(QPointF pos) {
    sprite->drawPixel(editedFrame, pos, getDrawColor());
    emit updateImage(editedFrame, getFrame());
}

void Model::drawLine(QPointF pos1, QPointF pos2) {
    sprite->drawLine(editedFrame, pos1, pos2, getDrawColor());
    emit updateImage(editedFrame, getFrame());
}

QRgb Model::chooseColor() {
    return QColorDialog::getColor().rgb();
}

// helper method to emit the primary button bg change
void Model::emitPrimBgChange(){
    QString r = QString::number(qRed(primaryColor));
    QString g = QString::number(qGreen(primaryColor));
    QString b = QString::number(qBlue(primaryColor));
    emit changePrimColorBg("background-color: rgb(" + r +  "," + g + "," + b + ");");
}

// helper method to emit the sceondary button bg change
void Model::emitSecBgChange(){
    QString r = QString::number(qRed(secondaryColor));
    QString g = QString::number(qGreen(secondaryColor));
    QString b = QString::number(qBlue(secondaryColor));
    emit changeSecColorBg("background-color: rgb(" + r +  "," + g + "," + b + ");");
}

void Model::choosePrimaryColor() {
    primaryColor = chooseColor();
    emitPrimBgChange();
}

void Model::chooseSecondaryColor() {
    secondaryColor = chooseColor();
    emitSecBgChange();
}

void Model::switchColors() {
    std::swap(primaryColor, secondaryColor);
    emitPrimBgChange();
    emitSecBgChange();
}

// changes brush to a pencil when the button is clicked
void Model::pencilButtonClick(){
    brush = Pencil;
}

// changes brush to an eraser when the button is clicked
void Model::eraserButtonClick(){
    brush = Eraser;
}

void Model::setEditedFrame(int frameIndex) {
    editedFrame = frameIndex;
    emit updateImage(frameIndex, getFrame());
}

void Model::createFrame() {
    int index = sprite->createFrame();
    emit onFrameCreated(getFrame(index));
    setEditedFrame(index);
}

void Model::deleteFrame() {
    if (sprite->getFrameCount() > 1) {
        sprite->deleteFrame(editedFrame);
        emit onFrameDeleted(editedFrame);

        if (editedFrame >= sprite->getFrameCount()) editedFrame--;
        emit updateImage(editedFrame, getFrame());
    }
}

void Model::setPreviewWindow()
{
    previewWindowIsOpen = true;
    cycleFrames();
}

void Model::setFPS(int fps)
{
    framesPerSecond = fps;
}


void Model::cycleFrames()
{
    std::cout<<"still cycling"<<std::endl;

    if(previewWindowIsOpen)
    {
        emit sendFramesToPreview(sprite->getFrame(previewFrameIndex));
        previewFrameIndex = (previewFrameIndex + 1) % sprite->getFrameCount();

        timer.singleShot(1000 / framesPerSecond, this, &Model::cycleFrames);
    }

}

void Model::stopCycleFrames()
{
    std::cout<< "stop cycle frames" << std::endl;
    previewWindowIsOpen = false;
}

QRgb Model::getDrawColor() {
    switch (brush) {
    case Pencil:
        return primaryColor;
    case Eraser:
        return qRgba(0, 0, 0, 0);
    }
}
