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

#include "game_test/KingRuleTest.h"
#include <game/Rules/KingRule.h>
#include <game/Rules/PawnRule.h>
#include <game/Chessboard.h>
#include <game/Position.h>
#include <game/Square.h>
#include <game/Piece.h>

#include <QtTest/QtTest>

KingRuleTest::KingRuleTest(QObject *parent)
    : QObject(parent)
{
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │   │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │ x │ x │ x │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │ x │ R │ x │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │ x │ x │ x │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │   │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │   │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void KingRuleTest::shouldFindAllPossibleMovesOnEmptyBoard()
{
    Chess::Chessboard board;
    Chess::KingRule* rule = new Chess::KingRule(board);
    Chess::Piece piece(Chess::PieceType::King, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    QVERIFY(moves.size() == 8);
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │   │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │ x │ x │ P │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │ P │ R │ x │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │ x │ P │ x │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │   │   │   │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │   │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void KingRuleTest::shouldFindAllPossibleMovesOnFilledBoard()
{
    Chess::Chessboard board;

    Chess::Piece pawn1(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::C5(), &pawn1);

    Chess::Piece pawn2(Chess::PieceType::Pawn, Chess::Color::White, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::E6(), &pawn2);

    Chess::Piece pawn3(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::D4(), &pawn3);

    Chess::KingRule* rule = new Chess::KingRule(board);
    Chess::Piece piece(Chess::PieceType::King, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    size_t attacks = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Attack));
    QVERIFY(attacks == 2);

    size_t movement = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Movement));
    QVERIFY(movement == 5);

    size_t defends = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Defend));
    QVERIFY(defends == 1);
}

//     A   B   C   D   E   F   G   H
//   ┌───┬───┬───┬───┬───┬───┬───┬───┐
// 8 │   │   │   │   │   │   │   │   │  8
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 7 │   │   │   │   │   │   │   │   │  7
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 6 │   │   │ x │ x │ P │   │   │   │  6
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 5 │   │   │ P │ R │ x │   │   │   │  5
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 4 │   │   │ x │ P │ x │   │   │   │  4
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 3 │   │   │   │   │   │ P │   │   │  3
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 2 │   │   │   │   │   │   │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │   │   │   │   │   │   │   │   │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void KingRuleTest::shouldFindAllPossibleAttacksOnBoard()
{
    Chess::Chessboard board;

    Chess::Piece pawn1(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::C5(), &pawn1);

    Chess::Piece pawn2(Chess::PieceType::Pawn, Chess::Color::White, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::E6(), &pawn2);

    Chess::Piece pawn3(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::D4(), &pawn3);

    Chess::Piece pawn4(Chess::PieceType::Pawn, Chess::Color::Black, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::F3(), &pawn4);

    Chess::KingRule* rule = new Chess::KingRule(board);
    Chess::Piece piece(Chess::PieceType::King, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::D5(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    size_t attacks = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Attack));
    QVERIFY(attacks == 2);

    size_t movement = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Movement));
    QVERIFY(movement == 5);

    size_t defends = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Defend));
    QVERIFY(defends == 1);
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
// 2 │   │   │   │ x │ x │ x │   │   │  2
//   ├───┼───┼───┼───┼───┼───┼───┼───┤
// 1 │ R │   │ x │ x │ K │ x │ x │ R │  1
//   └───┴───┴───┴───┴───┴───┴───┴───┘
//     A   B   C   D   E   F   G   H
//
void KingRuleTest::shouldCheckForCastling()
{
    Chess::Chessboard board;

    Chess::Piece rook1(Chess::PieceType::Rook, Chess::Color::White, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::H1(), &rook1);

    Chess::Piece rook2(Chess::PieceType::Rook, Chess::Color::White, &board, new Chess::PawnRule(board));
    board.putPiece(Chess::Position::A1(), &rook2);

    Chess::KingRule* rule = new Chess::KingRule(board);
    Chess::Piece piece(Chess::PieceType::King, Chess::Color::White, &board, rule);
    board.putPiece(Chess::Position::E1(), &piece);

    std::vector<Chess::Move::UPtr> moves = rule->findMoves(piece);
    size_t castling = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Castling));
    QVERIFY(castling == 2);

    size_t movement = std::count_if(std::begin(moves), std::end(moves), Chess::ByTypePredicate(Chess::Move::Movement));
    QVERIFY(movement == 5);
}
