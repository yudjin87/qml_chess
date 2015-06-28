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

#include "game_test/PositionTest.h"
#include <game/Position.h>
#include <QtTest/QtTest>

PositionTest::PositionTest(QObject *parent)
    : QObject(parent)
{
}

void PositionTest::shouldCalculateColor()
{
    {
        Chess::Position sut(Chess::Position::A1());
        QVERIFY(sut.color() == Chess::Color::Black);
    }

    {
        Chess::Position sut(Chess::Position::A8());
        QVERIFY(sut.color() == Chess::Color::White);
    }

    {
        Chess::Position sut(Chess::Position::H8());
        QVERIFY(sut.color() == Chess::Color::Black);
    }

    {
        Chess::Position sut(Chess::Position::H1());
        QVERIFY(sut.color() == Chess::Color::White);
    }

    {
        Chess::Position sut(Chess::Position::E4());
        QVERIFY(sut.color() == Chess::Color::White);
    }
}

void PositionTest::indexTest()
{
    Chess::Position a1(Chess::Position::A1());
    QCOMPARE(a1.index(), 0);

    Chess::Position h8(Chess::Position::H8());
    QCOMPARE(h8.index(), 63);
}

void PositionTest::operatorLessTest()
{
    Chess::Position a1(Chess::Position::A1());
    Chess::Position a2(Chess::Position::A2());
    QVERIFY(a1 < a2);
    QVERIFY(a2 <= a2);

    Chess::Position b1(Chess::Position::B1());
    QVERIFY(b1 < a2);
    QVERIFY((a2 < b1) == false);

    Chess::Position h8(Chess::Position::H8());
    QVERIFY(a1 < h8);
}

void PositionTest::preIncrementTest()
{
    Chess::Position a1(Chess::Position::A1());
    Chess::Position b1(Chess::Position::B1());
    QVERIFY(++a1 == b1);

    Chess::Position h1(Chess::Position::H1());
    Chess::Position a2(Chess::Position::A2());
    QVERIFY(++h1 == a2);

    Chess::Position h8(Chess::Position::H8());
    QVERIFY(++h8 == Chess::Position(Chess::Position::A1()));
}

int transform(int index)
{
    const int mod8 = index % 8;
    const int base = index / 8;
    return 64 - ((base + 1)* 8) + mod8;
}

void PositionTest::loopTest()
{
    int counter = 1;
    for (Chess::Position p = Chess::Position(Chess::Position::A1()); p < Chess::Position(Chess::Position::H8()); ++p)
    {
        ++counter;
    }

    QCOMPARE(counter, 64);

    QVERIFY(transform(0) == 56);
    QVERIFY(transform(1) == 57);
    QVERIFY(transform(8) == 48);
    QVERIFY(transform(62) == 6);

    QVERIFY(transform(56) == 0);
    QVERIFY(transform(57) == 1);
    QVERIFY(transform(48) == 8);
    QVERIFY(transform(6) == 62);
}
