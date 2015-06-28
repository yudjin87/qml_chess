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
#include "game_test/SquareTest.h"
#include "game_test/PositionTest.h"
#include "game_test/PawnRuleTest.h"
#include "game_test/KnightRuleTest.h"
#include "game_test/BishopRuleTest.h"
#include "game_test/RookRuleTest.h"
#include "game_test/QueenRuleTest.h"
#include "game_test/KingRuleTest.h"

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ChessboardTest chessboardTest;
    QTest::qExec(&chessboardTest, argc, argv);

    SquareTest squareTest;
    QTest::qExec(&squareTest, argc, argv);

    PositionTest positionTest;
    QTest::qExec(&positionTest, argc, argv);

    PawnRuleTest pawnRuleTest;
    QTest::qExec(&pawnRuleTest, argc, argv);

    KnightRuleTest knightRuleTest;
    QTest::qExec(&knightRuleTest, argc, argv);

    BishopRuleTest bishopRuleTest;
    QTest::qExec(&bishopRuleTest, argc, argv);

    RookRuleTest rookRuleTest;
    QTest::qExec(&rookRuleTest, argc, argv);

    QueenRuleTest queenRuleTest;
    QTest::qExec(&queenRuleTest, argc, argv);

    KingRuleTest kingRuleTest;
    QTest::qExec(&kingRuleTest, argc, argv);

    return 0;
}
