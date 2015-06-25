#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T17:43:40
#
#-------------------------------------------------

include(../chess_shared.pro)

QT       += core
QT       -= gui

TARGET = game
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = lib


SOURCES += Square.cpp \
    Chessboard.cpp \
    File.cpp \
    Rank.cpp \
    Color.cpp \
    Position.cpp

HEADERS += \
    Square.h \
    Chessboard.h \
    File.h \
    Rank.h \
    Color.h \
    Position.h
