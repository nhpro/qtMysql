#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T09:44:08
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtMysql
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connsql.cpp \
    loginwindow.cpp \
    qdelegate.cpp

HEADERS  += mainwindow.h \
    connsql.h \
    loginwindow.h \
    qdelegate.h

FORMS    += mainwindow.ui \
    loginwindow.ui

RESOURCES     = qtMysql.qrc
