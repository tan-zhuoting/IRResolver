QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    IRResolver.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    IRResolver.hpp \
    mainwindow.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    data.txt
