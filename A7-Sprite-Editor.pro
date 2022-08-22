QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editorwidget.cpp \
    main.cpp \
    model.cpp \
    previewwidget.cpp \
    realpreviewwindow.cpp \
    sprite.cpp \
    view.cpp

HEADERS += \
    editorwidget.h \
    model.h \
    previewwidget.h \
    realpreviewwindow.h \
    sprite.h \
    view.h

FORMS += \
    realpreviewwindow.ui \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
