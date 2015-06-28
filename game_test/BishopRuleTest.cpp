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

#include "game_test/BishopRuleTest.h"
#include <game/BishopRule.h>
#include <game/PawnRule.h>
#include <game/Chessboard.h>
#include <game/Position.h>
#include <game/Square.h>
#include <game/Piece.h>

#include <QtTest/QtTest>

BishopRuleTest::BishopRuleTest(QObject *parent)
    : QObject(parent)
{
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │ x │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │ x │   │   │   │ x │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │ x │   │ x │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │   │ B │   │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │ x │   │ x │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │ x │   │   │   │ x │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │ x │   │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │   │   │   │ x │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void BishopRuleTest::shouldFindAllPossibleMovesOnEmptyBoard()
{
    Chess::Chessboard board;
    Chess::BishopRule* rule = new Chess::BishopRule(board);
    Chess::Piece piece(Chess::PieceType::Bishop, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    QList<Chess::Square*> moves = rule->findMoves(piece);
    QCOMPARE(moves.size(), 13);

//    QCOMPARE(moves[0]->position(), Chess::Position::E3());
    //    QCOMPARE(moves[1]->position(), Chess::Position::E4());
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │ P │   │   │   │ P │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │   │ x │   │ x │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │   │   │ B │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │   │ x │   │ P │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │ x │   │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │ x │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │ P │   │   │   │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void BishopRuleTest::shouldFindAllPossibleMovesOnFilledBoard()
{
    Chess::Chessboard board;

    Chess::Piece pawn1(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board, Chess::Color::Black));
    board.putPiece(Chess::Position::C7(), &pawn1);

    Chess::Piece pawn2(Chess::PieceType::Pawn, Chess::Color::White, &board, new Chess::PawnRule(board, Chess::Color::White));
    board.putPiece(Chess::Position::F4(), &pawn2);

    Chess::Piece pawn3(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board, Chess::Color::Black));
    board.putPiece(Chess::Position::G7(), &pawn3);

    Chess::Piece pawn4(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board, Chess::Color::Black));
    board.putPiece(Chess::Position::A1(), &pawn4);

    Chess::BishopRule* rule = new Chess::BishopRule(board);
    Chess::Piece piece(Chess::PieceType::Bishop, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::E5(), &piece);

    QList<Chess::Square*> moves = rule->findMoves(piece);
    QCOMPARE(moves.size(), 5);
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │ A │   │   │   │ A │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │   │ x │   │ x │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │   │   │ B │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │   │ x │   │ o │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │ x │   │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │ x │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │ A │   │   │   │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void BishopRuleTest::shouldFindAllPossibleAttacksOnBoard()
{
    Chess::Chessboard board;

    Chess::Piece pawn1(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board, Chess::Color::Black));
    board.putPiece(Chess::Position::C7(), &pawn1);

    Chess::Piece pawn2(Chess::PieceType::Pawn, Chess::Color::White, &board, new Chess::PawnRule(board, Chess::Color::White));
    board.putPiece(Chess::Position::F4(), &pawn2);

    Chess::Piece pawn3(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board, Chess::Color::Black));
    board.putPiece(Chess::Position::G7(), &pawn3);

    Chess::Piece pawn4(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board, Chess::Color::Black));
    board.putPiece(Chess::Position::A1(), &pawn4);

    Chess::BishopRule* rule = new Chess::BishopRule(board);
    Chess::Piece piece(Chess::PieceType::Bishop, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::E5(), &piece);

    QList<Chess::Square*> attacks = rule->findAttacks(piece);
    QCOMPARE(attacks.size(), 3);
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │   │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │   │   │   │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │   │   │   │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │   │   │   │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │   │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │   │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
