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

#include "game_test/QueenRuleTest.h"
#include <game/Rules/QueenRule.h>
#include <game/Rules/PawnRule.h>
#include <game/Chessboard.h>
#include <game/Position.h>
#include <game/Square.h>
#include <game/Piece.h>

#include <QtTest/QtTest>

QueenRuleTest::QueenRuleTest(QObject *parent)
    : QObject(parent)
{
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │ x │   │   │ x │   │   │ x │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │ x │   │ x │   │ x │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │ x │ x │ x │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │ x │ x │ x │ Q │ x │ x │ x │ x │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │ x │ x │ x │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │ x │   │ x │   │ x │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │ x │   │   │ x │   │   │ x │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │ x │   │   │   │ x │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void QueenRuleTest::shouldFindAllPossibleMovesOnEmptyBoard()
{
    Chess::Chessboard board;
    Chess::QueenRule* rule = new Chess::QueenRule(board);
    Chess::Piece piece(Chess::PieceType::Queen, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    QVERIFY(moves.size() == 14 + 13);
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │ P │   │   │ x │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │ P │   │ x │   │ x │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │ x │ x │ x │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │ P │ Q │ x │ x │ P │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │ x │ x │ x │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │ x │   │ x │   │ x │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │ x │   │   │ x │   │   │ x │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │ P │   │   │   │ x │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void QueenRuleTest::shouldFindAllPossibleMovesOnFilledBoard()
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

    Chess::Piece pawn5(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::B7(), &pawn5);

    Chess::QueenRule* rule = new Chess::QueenRule(board);
    Chess::Piece piece(Chess::PieceType::Queen, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    size_t attacks = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Attack));
    QVERIFY(attacks == 4);

    size_t defends = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Defend));
    QVERIFY(defends == 1);

    size_t movement = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Movement));
    QVERIFY(movement == 18);
}
