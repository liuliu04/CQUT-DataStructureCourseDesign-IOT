QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StickSorter
TEMPLATE = app

# 添加C语言编译选项
CONFIG += c11
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -std=c11

# 添加标准库
LIBS += -lmsvcrt

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    stick_sorter.c

HEADERS += \
    mainwindow.h \
    stick_sorter.h 