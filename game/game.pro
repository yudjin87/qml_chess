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

DEFINES += GAME_LIB_IMPORT

SOURCES += Square.cpp \
    Chessboard.cpp \
    File.cpp \
    Rank.cpp \
    Color.cpp \
    Position.cpp \
    Piece.cpp \
    ChessGame.cpp \
    PieceType.cpp \
    SquareList.cpp \
    PawnRule.cpp \
    Player.cpp \
    MovementCommand.cpp \
    BishopRule.cpp \
    AttackCommand.cpp \
    KnightRule.cpp \
    GameMode.cpp \
    GameMovementsWriter.cpp \
    GameMovementsReader.cpp

HEADERS += \
    Square.h \
    Chessboard.h \
    File.h \
    Rank.h \
    Color.h \
    Position.h \
    game_api.h \
    Constants.h \
    Piece.h \
    ChessGame.h \
    PieceType.h \
    SquareList.h \
    IMovementRule.h \
    PawnRule.h \
    Player.h \
    IMoveCommand.h \
    MovementCommand.h \
    IGameMovesRegistry.h \
    BishopRule.h \
    AttackCommand.h \
    KnightRule.h \
    GameMode.h \
    GameMovementsWriter.h \
    GameMovementsReader.h
