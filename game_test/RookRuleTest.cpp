/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "game_test/RookRuleTest.h"
#include <game/RookRule.h>
#include <game/PawnRule.h>
#include <game/Chessboard.h>
#include <game/Position.h>
#include <game/Square.h>
#include <game/Piece.h>

#include <QtTest/QtTest>

RookRuleTest::RookRuleTest(QObject *parent)
    : QObject(parent)
{
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │ x │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │ x │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │   │ x │   │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │ x │ x │ x │ R │ x │ x │ x │ x │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │   │ x │   │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │ x │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │ x │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │ x │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void RookRuleTest::shouldFindAllPossibleMovesOnEmptyBoard()
{
    Chess::Chessboard board;
    Chess::RookRule* rule = new Chess::RookRule(board);
    Chess::Piece piece(Chess::PieceType::Rook, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    QList<Chess::Square*> moves = rule->findMoves(piece);
    QCOMPARE(moves.size(), 14);
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │ P │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │ x │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │   │ x │   │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │ P │ R │ x │ x │ P │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │   │ x │   │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │ x │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │ x │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │ P │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void RookRuleTest::shouldFindAllPossibleMovesOnFilledBoard()
{
    Chess::Chessboard board;

    Chess::Piece pawn1(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::D8(), &pawn1);

    Chess::Piece pawn2(Chess::PieceType::Pawn, Chess::Color::White, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::D1(), &pawn2);

    Chess::Piece pawn3(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::G5(), &pawn3);

    Chess::Piece pawn4(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::C5(), &pawn4);

    Chess::RookRule* rule = new Chess::RookRule(board);
    Chess::Piece piece(Chess::PieceType::Rook, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    QList<Chess::Square*> moves = rule->findMoves(piece);
    QCOMPARE(moves.size(), 7);
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │ P │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │ x │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │   │ x │   │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │ P │ R │ x │ x │ P │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │   │ x │   │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │ x │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │ x │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │ P │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void RookRuleTest::shouldFindAllPossibleAttacksOnBoard()
{
    Chess::Chessboard board;

    Chess::Piece pawn1(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::D8(), &pawn1);

    Chess::Piece pawn2(Chess::PieceType::Pawn, Chess::Color::White, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::D1(), &pawn2);

    Chess::Piece pawn3(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::G5(), &pawn3);

    Chess::Piece pawn4(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::C5(), &pawn4);

    Chess::RookRule* rule = new Chess::RookRule(board);
    Chess::Piece piece(Chess::PieceType::Rook, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    QList<Chess::Square*> attacks = rule->findAttacks(piece);
    QCOMPARE(attacks.size(), 3);
}
