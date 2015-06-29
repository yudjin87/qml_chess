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
    Player.cpp \
    GameMode.cpp \
    Commands/GameMovementsWriter.cpp \
    Commands/GameMovementsReader.cpp \
    Commands/AttackCommand.cpp \
    Commands/MovementCommand.cpp \
    Rules/PawnRule.cpp \
    Rules/KnightRule.cpp \
    Rules/BishopRule.cpp \
    Rules/RookRule.cpp \
    Rules/QueenRule.cpp \
    Rules/KingRule.cpp \
    Commands/GameMovesRegistry.cpp \
    Commands/CastlingCommand.cpp \
    Commands/BaseCommand.cpp

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
    Player.h \
    GameMode.h \
    Commands/GameMovementsWriter.h \
    Commands/GameMovementsReader.h \
    Commands/IMoveCommand.h \
    Commands/AttackCommand.h \
    Commands/MovementCommand.h \
    Rules/IMovementRule.h \
    Rules/PawnRule.h \
    Rules/KnightRule.h \
    Rules/BishopRule.h \
    Rules/RookRule.h \
    Rules/QueenRule.h \
    Rules/KingRule.h \
    Commands/GameMovesRegistry.h \
    Commands/CastlingCommand.h \
    Commands/BaseCommand.h
