#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T16:47:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = warsztat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    partdialog.cpp \
    exploitationdialog.cpp \
    clientdialog.cpp \
    branddialog.cpp \
    modeldialog.cpp \
    repairdialog.cpp \
    cardialog.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    tabele.h \
    partdialog.h \
    exploitationdialog.h \
    clientdialog.h \
    branddialog.h \
    modeldialog.h \
    repairdialog.h \
    cardialog.h \
    logindialog.h \
    tabele_kopia.h

FORMS    += mainwindow.ui \
    partdialog.ui \
    exploitationdialog.ui \
    clientdialog.ui \
    branddialog.ui \
    modeldialog.ui \
    repairdialog.ui \
    cardialog.ui \
    logindialog.ui

#LIBS += -lmysqlclient

QMAKE_CXXFLAGS += -std=c++11


