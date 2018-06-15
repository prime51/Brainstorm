#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T15:34:18
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyServer
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp\
        question.cpp\
        questionbank.cpp\
        user.cpp\
        userbank.cpp
#        gameresult.cpp

HEADERS  += server.h\
        question.h\
        questionbank.h\
        user.h\
        userbank.h
#        gameresult.h

FORMS    += server.ui

RESOURCES += \
    data.qrc
