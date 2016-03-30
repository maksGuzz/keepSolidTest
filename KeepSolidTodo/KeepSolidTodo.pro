#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T11:14:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeepSolidTodo

TEMPLATE = app

LIBS += -lprotobuf

SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    ../pbs_compiled/message.pb.cc \
    ../pbs_compiled/message_common.pb.cc \
    ../pbs_compiled/message_type.pb.cc \
    ../pbs_compiled/message_workgroup.pb.cc \
    networkmgr.cpp \
    solidauth.cpp \
    treemodel.cpp \
    treeitem.cpp \
    sendrcvjob.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    ../pbs_compiled/message.pb.h \
    ../pbs_compiled/message_common.pb.h \
    ../pbs_compiled/message_type.pb.h \
    ../pbs_compiled/message_workgroup.pb.h \
    networkmgr.h \
    solidauth.h \
    treemodel.h \
    treeitem.h \
    sendrcvjob.h

FORMS    += mainwindow.ui


