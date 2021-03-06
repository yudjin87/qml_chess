#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T17:43:40
#
#-------------------------------------------------
include(../chess_shared.pro)

QT       += core
QT       += testlib
QT       -= gui

TARGET = game_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L$${DESTDIR}/ -lgame

SOURCES += main.cpp \
    SquareTest.cpp \
    PositionTest.cpp \
    ChessboardTest.cpp \
    PawnRuleTest.cpp \
    BishopRuleTest.cpp \
    KnightRuleTest.cpp \
    RookRuleTest.cpp \
    QueenRuleTest.cpp \
    KingRuleTest.cpp

HEADERS += \
    SquareTest.h \
    PositionTest.h \
    ChessboardTest.h \
    PawnRuleTest.h \
    BishopRuleTest.h \
    KnightRuleTest.h \
    RookRuleTest.h \
    QueenRuleTest.h \
    KingRuleTest.h


win32-msvc* {
    QMAKE_CXXFLAGS -= /Wall # too much warnings in Qt test lib
    QMAKE_CXXFLAGS += /W3
}
