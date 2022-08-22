#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <sprite.h>
#include <QPoint>
#include <QImage>
#include <QTimer>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    QImage* getFrame();
    QImage* getFrame(int frameIndex);

signals:
    void updateImage(int frameIndex, QImage* image);
    void changePrimColorBg(const QString& styleSheet);
    void changeSecColorBg(const QString& styleSheet);
    void onFrameCreated(QImage* image);
    void onFrameDeleted(int frameIndex);
    void sendFramesToPreview(QImage* image);



public slots:
    void drawPixel(QPointF pos);
    void drawLine(QPointF pos1, QPointF pos2);
    void choosePrimaryColor();
    void chooseSecondaryColor();
    void switchColors();
    void pencilButtonClick();
    void eraserButtonClick();
    void setEditedFrame(int frameIndex);
    void createFrame();
    void deleteFrame();
    void cycleFrames();
    void setPreviewWindow();
    void stopCycleFrames();
    void setFPS(int fps);

private:
    Sprite* sprite;
    QTimer timer;
    int editedFrame;
    int previewFrameIndex;
    int framesPerSecond;
    bool previewWindowIsOpen;


    enum BrushType {Pencil, Eraser};
    BrushType brush = Pencil;

    QRgb primaryColor, secondaryColor;

    QRgb chooseColor();
    void emitPrimBgChange();
    void emitSecBgChange();
    QRgb getDrawColor();
};

#endif // MODEL_H
