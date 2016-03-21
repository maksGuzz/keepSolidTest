#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T11:14:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeepSolidTodo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networkwrapper.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    networkwrapper.h \
    logindialog.h

FORMS    += mainwindow.ui
