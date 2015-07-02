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

void PositionTest::shouldParseFromString()
{
    bool ok = false;
    QVERIFY(Chess::Position::A1() == Chess::Position::fromString("A1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::A2() == Chess::Position::fromString("A2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::A3() == Chess::Position::fromString("A3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::A4() == Chess::Position::fromString("A4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::A5() == Chess::Position::fromString("A5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::A6() == Chess::Position::fromString("A6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::A7() == Chess::Position::fromString("A7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::A8() == Chess::Position::fromString("A8", &ok)); QVERIFY(ok);

    QVERIFY(Chess::Position::B1() == Chess::Position::fromString("B1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::B2() == Chess::Position::fromString("B2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::B3() == Chess::Position::fromString("B3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::B4() == Chess::Position::fromString("B4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::B5() == Chess::Position::fromString("B5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::B6() == Chess::Position::fromString("B6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::B7() == Chess::Position::fromString("B7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::B8() == Chess::Position::fromString("B8", &ok)); QVERIFY(ok);

    QVERIFY(Chess::Position::C1() == Chess::Position::fromString("C1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::C2() == Chess::Position::fromString("C2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::C3() == Chess::Position::fromString("C3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::C4() == Chess::Position::fromString("C4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::C5() == Chess::Position::fromString("C5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::C6() == Chess::Position::fromString("C6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::C7() == Chess::Position::fromString("C7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::C8() == Chess::Position::fromString("C8", &ok)); QVERIFY(ok);

    QVERIFY(Chess::Position::D1() == Chess::Position::fromString("D1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::D2() == Chess::Position::fromString("D2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::D3() == Chess::Position::fromString("D3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::D4() == Chess::Position::fromString("D4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::D5() == Chess::Position::fromString("D5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::D6() == Chess::Position::fromString("D6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::D7() == Chess::Position::fromString("D7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::D8() == Chess::Position::fromString("D8", &ok)); QVERIFY(ok);

    QVERIFY(Chess::Position::E1() == Chess::Position::fromString("E1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::E2() == Chess::Position::fromString("E2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::E3() == Chess::Position::fromString("E3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::E4() == Chess::Position::fromString("E4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::E5() == Chess::Position::fromString("E5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::E6() == Chess::Position::fromString("E6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::E7() == Chess::Position::fromString("E7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::E8() == Chess::Position::fromString("E8", &ok)); QVERIFY(ok);

    QVERIFY(Chess::Position::F1() == Chess::Position::fromString("F1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::F2() == Chess::Position::fromString("F2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::F3() == Chess::Position::fromString("F3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::F4() == Chess::Position::fromString("F4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::F5() == Chess::Position::fromString("F5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::F6() == Chess::Position::fromString("F6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::F7() == Chess::Position::fromString("F7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::F8() == Chess::Position::fromString("F8", &ok)); QVERIFY(ok);

    QVERIFY(Chess::Position::G1() == Chess::Position::fromString("G1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::G2() == Chess::Position::fromString("G2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::G3() == Chess::Position::fromString("G3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::G4() == Chess::Position::fromString("G4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::G5() == Chess::Position::fromString("G5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::G6() == Chess::Position::fromString("G6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::G7() == Chess::Position::fromString("G7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::G8() == Chess::Position::fromString("G8", &ok)); QVERIFY(ok);

    QVERIFY(Chess::Position::H1() == Chess::Position::fromString("H1", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::H2() == Chess::Position::fromString("H2", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::H3() == Chess::Position::fromString("H3", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::H4() == Chess::Position::fromString("H4", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::H5() == Chess::Position::fromString("H5", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::H6() == Chess::Position::fromString("H6", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::H7() == Chess::Position::fromString("H7", &ok)); QVERIFY(ok);
    QVERIFY(Chess::Position::H8() == Chess::Position::fromString("H8", &ok)); QVERIFY(ok);
}

void PositionTest::shouldCreateFromIndex()
{
    Chess::Position a1(0);
    QCOMPARE(a1, Chess::Position::A1());

    Chess::Position h8(63);
    QCOMPARE(h8, Chess::Position::H8());
}
