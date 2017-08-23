#    Author: Roland Ihasz   https://chtbsoft.com
#    Created on 07 February 2015, 15:09 final

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#QMAKE_MAC_SDK = macosx10.10

TARGET = ThicknessMeasuringTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
