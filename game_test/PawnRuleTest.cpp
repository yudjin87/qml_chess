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

#include "game_test/PawnRuleTest.h"
#include <game/Rules/PawnRule.h>
#include <game/Chessboard.h>
#include <game/Position.h>
#include <game/Square.h>
#include <game/Piece.h>

#include <QtTest/QtTest>
#include <algorithm>

PawnRuleTest::PawnRuleTest(QObject *parent)
    : QObject(parent)
{
}

void PawnRuleTest::shouldReturnMovesForInitialPosition()
{
    Chess::Chessboard board;
    Chess::PawnRule* rule = new Chess::PawnRule(board);
    Chess::Piece piece(Chess::PieceType::Pawn, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::E2(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    QVERIFY(moves.size() == 2);

    QVERIFY(moves[0]->type() == Chess::Move::Movement);
    QVERIFY(moves[1]->type() == Chess::Move::Movement);
    QCOMPARE(moves[0]->position(), Chess::Position::E3());
    QCOMPARE(moves[1]->position(), Chess::Position::E4());
}

void PawnRuleTest::shouldReturnMovesForInitialPositionForBlack()
{
    Chess::Chessboard board;
    Chess::PawnRule* rule = new Chess::PawnRule(board);
    Chess::Piece piece(Chess::PieceType::Pawn, Chess::Color::Black, &board, rule);
    board.putPiece(Chess::Position::E7(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    QVERIFY(moves.size() == 2);

    QVERIFY(moves[0]->type() == Chess::Move::Movement);
    QVERIFY(moves[1]->type() == Chess::Move::Movement);
    QCOMPARE(moves[0]->position(), Chess::Position::E6());
    QCOMPARE(moves[1]->position(), Chess::Position::E5());
}

void PawnRuleTest::shouldReturnMoveForNonInitialPosition()
{
    Chess::Chessboard board;
    Chess::PawnRule* rule = new Chess::PawnRule(board);
    Chess::Piece movedPiece(Chess::PieceType::Pawn, Chess::Color::White, &board, rule);
    movedPiece.markAsMoved(true);
    board.putPiece(Chess::Position::E3(), &movedPiece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(movedPiece);
    QVERIFY(moves.size() == 1);

    QVERIFY(moves[0]->type() == Chess::Move::Movement);
    QCOMPARE(moves[0]->position(), Chess::Position::E4());
}

void PawnRuleTest::shouldReturnEmptyListIfMovementIsNotPossible()
{
    Chess::Chessboard board;
    Chess::Piece blockedPiece(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::E4(), &blockedPiece);

    Chess::PawnRule *rule = new Chess::PawnRule(board);
    Chess::Piece piece(Chess::PieceType::Pawn, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::E3(), &piece);
    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    QVERIFY(moves.size() == 0);
}

//     A   B   C   D   E   G   G   F   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │   │   │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │   │   │   │   │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │   │ P │   │   │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │   │   │ P │   │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │   │   │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │   │   │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   G   G   F   H
//

void PawnRuleTest::shouldReturnAttacks()
{
    Chess::Chessboard board;
    Chess::Piece enemyPiece(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::D5(), &enemyPiece);

    Chess::PawnRule *rule = new Chess::PawnRule(board);
    Chess::Piece piece(Chess::PieceType::Pawn, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::E4(), &piece);
    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);

    size_t attacks = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Attack));
    QVERIFY(attacks == 1);
}

