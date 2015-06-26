#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T17:43:40
#
#-------------------------------------------------
include(../chess_shared.pro)

QT       += gui

TARGET = app
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \

SOURCES += main.cpp \

LIBS += -L$${DESTDIR}/../bin -lgame \
                             -lui_qml \
