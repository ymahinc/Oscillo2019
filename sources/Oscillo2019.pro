#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22T14:11:18
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport opengl

TARGET = Oscillo2019
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

DEFINES += QCUSTOMPLOT_USE_OPENGL

LIBS += -LC:\Qt513b\5.13.0\mingw73_32\lib\libQt5OpenGL.a -lopengl32

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    portthread.cpp \
    qcustomplot.cpp \
    oscillowidget.cpp \
    mydial.cpp \
    yresdial.cpp \
    mydock.cpp \
    myslider.cpp \
    channelwidget.cpp \
    WidgetColorPicker.cpp \
    mytabwidget.cpp \
    channelsdock.cpp \
    yresticker.cpp \
    xresdial.cpp \
    maindock.cpp \
    maindockwidget.cpp \
    xresticker.cpp \
    cursor.cpp \
    measuresdockwidget.cpp \
    measuresdock.cpp \
    mathswidget.cpp \
    channel.cpp \
    led.cpp \
    settingsdialog.cpp

HEADERS += \
        mainwindow.h \
    global.h \
    portthread.h \
    qcustomplot.h \
    oscillowidget.h \
    mydial.h \
    yresdial.h \
    mydock.h \
    myslider.h \
    channelwidget.h \
    WidgetColorPicker.h \
    mytabwidget.h \
    channelsdock.h \
    yresticker.h \
    xresdial.h \
    maindock.h \
    maindockwidget.h \
    xresticker.h \
    cursor.h \
    measuresdockwidget.h \
    measuresdock.h \
    mathswidget.h \
    channel.h \
    led.h \
    settingsdialog.h

FORMS += \
        mainwindow.ui \
    yresdial.ui \
    channelwidget.ui \
    WidgetColorPicker.ui \
    xresdial.ui \
    maindockwidget.ui \
    measuresdockwidget.ui \
    mathswidget.ui \
    led.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    oscilloscope.qrc

RC_ICONS = sine.ico
