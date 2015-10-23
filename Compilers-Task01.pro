#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T21:31:47
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Compilers-Task01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    onlineprocessor.hpp

INCLUDEPATH += $$PWD/CTools/inc/

Release:LIBS += $$PWD/CTools/Release/CTools.lib

Debug:LIBS += $$PWD/CTools/Debug/CTools.lib

FORMS    += mainwindow.ui
