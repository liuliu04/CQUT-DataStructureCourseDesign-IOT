QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = River
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    river_core.c

HEADERS += \
    mainwindow.h \
    river_core.h 