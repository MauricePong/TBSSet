#-------------------------------------------------
#
# Project created by QtCreator 2017-11-21T18:38:15
#
#-------------------------------------------------

QT       += core gui
QT      += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = TBSSET
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/../bin

SOURCES     += main.cpp tbsbase.cpp tbshardware.cpp 
SOURCES     += iconhelper.cpp
SOURCES     += appinit.cpp
SOURCES     += tbsui.cpp

HEADERS     += iconhelper.h tbsbase.h  tbshardware.h
HEADERS     += appinit.h
HEADERS     += tbsui.h
FORMS       += tbsui.ui

RESOURCES   += main.qrc
RESOURCES   += qss.qrc
CONFIG      += qt warn_off
INCLUDEPATH += $$PWD
RC_FILE = tbsui.rc
#DEFINES += QT_NO_WARNING_OUTPUT\
#             QT_NO_DEBUG_OUTPUT


