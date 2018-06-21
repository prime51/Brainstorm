#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T20:56:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Brainstorm
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


SOURCES += \
        main.cpp \
        questionClass/question.cpp \
        questionClass/questionbank.cpp \
        pageClass/loginbufpage.cpp \
        pageClass/logindialog.cpp \
        pageClass/registerdialog.cpp \
        pageClass/gamepage.cpp \
    mainpage.cpp \
    hoversensitivelabel.cpp \
    hoverwindow.cpp

HEADERS += \
        questionClass/question.h \
        questionClass/questionbank.h \
        pageClass/loginbufpage.h \
        pageClass/logindialog.h \
        pageClass/registerdialog.h \
        pageClass/gamepage.h \
    mainpage.h \
    hoversensitivelabel.h \
    hoverwindow.h

FORMS += \
        pageClass/logindialog.ui \
        pageClass/registerdialog.ui \
        pageClass/gamepage.ui \
    mainpage.ui

RESOURCES += \
    widget.qrc
