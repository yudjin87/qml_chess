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

#include "PositionTest.h"
#include <game/Position.h>
#include <QtTest/QtTest>

PositionTest::PositionTest(QObject *parent)
    : QObject(parent)
{
}

void PositionTest::shouldCalculateColor()
{
    {
        Chess::Position sut(Chess::File::A, Chess::Rank::R1);
        QVERIFY(sut.color() == Chess::Color::Dark);
    }

    {
        Chess::Position sut(Chess::File::A, Chess::Rank::R8);
        QVERIFY(sut.color() == Chess::Color::Light);
    }

    {
        Chess::Position sut(Chess::File::H, Chess::Rank::R8);
        QVERIFY(sut.color() == Chess::Color::Dark);
    }

    {
        Chess::Position sut(Chess::File::H, Chess::Rank::R1);
        QVERIFY(sut.color() == Chess::Color::Light);
    }

    {
        Chess::Position sut(Chess::File::E, Chess::Rank::R4);
        QVERIFY(sut.color() == Chess::Color::Light);
    }
}

void PositionTest::indexTest()
{
    Chess::Position a1(Chess::File::A, Chess::Rank::R1);
    QCOMPARE(a1.index(), 0);

    Chess::Position h8(Chess::File::H, Chess::Rank::R8);
    QCOMPARE(h8.index(), 63);
}

void PositionTest::operatorLessTest()
{
    Chess::Position a1(Chess::File::A, Chess::Rank::R1);
    Chess::Position a2(Chess::File::A, Chess::Rank::R2);
    QVERIFY(a1 < a2);
    QVERIFY(a2 <= a2);

    Chess::Position b1(Chess::File::B, Chess::Rank::R1);
    QVERIFY(b1 < a2);
    QVERIFY((a2 < b1) == false);

    Chess::Position h8(Chess::File::H, Chess::Rank::R8);
    QVERIFY(a1 < h8);
}

void PositionTest::preIncrementTest()
{
    Chess::Position a1(Chess::File::A, Chess::Rank::R1);
    Chess::Position b1(Chess::File::B, Chess::Rank::R1);
    QVERIFY(++a1 == b1);

    Chess::Position h1(Chess::File::H, Chess::Rank::R1);
    Chess::Position a2(Chess::File::A, Chess::Rank::R2);
    QVERIFY(++h1 == a2);
}

void PositionTest::loopTest()
{
    int counter = 1;
    for (Chess::Position p = Chess::Position(Chess::File::A, Chess::Rank::R1); p < Chess::Position(Chess::File::H, Chess::Rank::R8); ++p)
    {
        ++counter;
    }

    QCOMPARE(counter, 64);
}
