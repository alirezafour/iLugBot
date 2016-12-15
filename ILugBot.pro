QT += core network
QT -= gui

CONFIG += c++11

TARGET = ILugBot
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/command.cpp \
    src/ilugbot.cpp \
    controller.cpp \
    src/commands/nextsection.cpp

HEADERS += \
    src/command.h \
    src/ilugbot.h \
    controller.h \
    src/commands/nextsection.h
