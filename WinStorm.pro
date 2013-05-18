#-------------------------------------------------
#
# Project created by QtCreator 2013-03-23T23:21:11
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WinStorm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    appdata.cpp \
    filelist.cpp \
    chrome.cpp \
    firefox.cpp \
    titlebar.cpp

HEADERS  += mainwindow.h \
    appdata.h \
    filelist.h \
    chrome.h \
    firefox.h \
    titlebar.h

RESOURCES += \
    resource.qrc
RC_FILE = myapp.rc
