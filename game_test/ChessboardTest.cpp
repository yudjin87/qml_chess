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

#include "game_test/ChessboardTest.h"

#include <game/Position.h>
#include <game/Chessboard.h>
#include <game/Square.h>
#include <QtTest/QtTest>

ChessboardTest::ChessboardTest(QObject *parent)
    : QObject(parent)
{

}

void ChessboardTest::shouldCreate8x8Board()
{
    Chess::Chessboard sut;
    QCOMPARE(sut.size(), Chess::CHESS_SIZE * Chess::CHESS_SIZE);

    const Chess::Square* a1 = sut.squareAt(Chess::Position::A1());
    QVERIFY(a1 != nullptr);
    QVERIFY(a1->position() == Chess::Position::A1());
    QVERIFY(a1 == sut.squareByIdex(0));

    const Chess::Square* a8 = sut.squareAt(Chess::Position::A8());
    QVERIFY(a8 != nullptr);
    QVERIFY(a8->position() == Chess::Position::A8());

    const Chess::Square* e4 = sut.squareAt(Chess::Position::E4());
    QVERIFY(e4 != nullptr);
    QVERIFY(e4->position() == Chess::Position::E4());

    const Chess::Square* h8 = sut.squareAt(Chess::Position::H8());
    QVERIFY(h8 != nullptr);
    QVERIFY(h8->position() == Chess::Position::H8());
    QVERIFY(h8 == sut.squareByIdex(63));
}

