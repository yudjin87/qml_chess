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

#include "SquareTest.h"

#include <game/Chessboard.h>
#include <game/Square.h>
#include <QtTest/QtTest>

SquareTest::SquareTest(QObject *parent)
    : QObject(parent)
{
}

void SquareTest::shouldCalculateColor()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R1);
        QVERIFY(sut.color() == Chess::Color::Dark);
    }

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R8);
        QVERIFY(sut.color() == Chess::Color::Light);
    }

    {
        Chess::Square sut(mock, Chess::File::H, Chess::Rank::R8);
        QVERIFY(sut.color() == Chess::Color::Dark);
    }

    {
        Chess::Square sut(mock, Chess::File::H, Chess::Rank::R1);
        QVERIFY(sut.color() == Chess::Color::Light);
    }

    {
        Chess::Square sut(mock, Chess::File::E, Chess::Rank::R4);
        QVERIFY(sut.color() == Chess::Color::Light);
    }
}

void SquareTest::leftTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R1);
        QVERIFY(sut.left() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R1);
        QVERIFY(sut.left()->file() == Chess::File::A);
    }

    {
        Chess::Square sut(mock, Chess::File::C, Chess::Rank::R1);
        QVERIFY(sut.left(2)->file() == Chess::File::A);
    }
}

void SquareTest::topLeftTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R1);
        QVERIFY(sut.topLeft() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R1);
        QVERIFY(sut.topLeft()->file() == Chess::File::A);
        QVERIFY(sut.topLeft()->rank() == Chess::Rank::R2);
    }

    {
        Chess::Square sut(mock, Chess::File::C, Chess::Rank::R1);
        QVERIFY(sut.topLeft(2)->file() == Chess::File::A);
        QVERIFY(sut.topLeft(2)->rank() == Chess::Rank::R3);
    }
}

void SquareTest::topTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R8);
        QVERIFY(sut.top() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R1);
        QVERIFY(sut.top()->rank() == Chess::Rank::R2);
    }

    {
        Chess::Square sut(mock, Chess::File::C, Chess::Rank::R1);
        QVERIFY(sut.top(2)->rank() == Chess::Rank::R3);
    }
}

void SquareTest::topRightTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::H, Chess::Rank::R1);
        QVERIFY(sut.topRight() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R1);
        QVERIFY(sut.topRight()->file() == Chess::File::C);
        QVERIFY(sut.topRight()->rank() == Chess::Rank::R2);
    }

    {
        Chess::Square sut(mock, Chess::File::C, Chess::Rank::R1);
        QVERIFY(sut.topRight(2)->file() == Chess::File::E);
        QVERIFY(sut.topRight(2)->rank() == Chess::Rank::R3);
    }
}

void SquareTest::rightTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::H, Chess::Rank::R1);
        QVERIFY(sut.right() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R1);
        QVERIFY(sut.right()->file() == Chess::File::C);
    }

    {
        Chess::Square sut(mock, Chess::File::F, Chess::Rank::R1);
        QVERIFY(sut.right(2)->file() == Chess::File::H);
    }

    {
        Chess::Square sut(mock, Chess::File::G, Chess::Rank::R1);
        QVERIFY(sut.right(2) == nullptr);
    }
}

void SquareTest::bottomTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R1);
        QVERIFY(sut.bottom() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R7);
        QVERIFY(sut.bottom()->rank() == Chess::Rank::R6);
    }

    {
        Chess::Square sut(mock, Chess::File::C, Chess::Rank::R7);
        QVERIFY(sut.bottom(2)->rank() == Chess::Rank::R5);
    }
}

void SquareTest::bottomLeftTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R1);
        QVERIFY(sut.bottomLeft() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R2);
        QVERIFY(sut.bottomLeft()->file() == Chess::File::A);
        QVERIFY(sut.bottomLeft()->rank() == Chess::Rank::R1);
    }

    {
        Chess::Square sut(mock, Chess::File::C, Chess::Rank::R3);
        QVERIFY(sut.bottomLeft(2)->file() == Chess::File::A);
        QVERIFY(sut.bottomLeft(2)->rank() == Chess::Rank::R1);
    }
}

void SquareTest::bottomRightTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::File::A, Chess::Rank::R1);
        QVERIFY(sut.bottomRight() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::File::B, Chess::Rank::R2);
        QVERIFY(sut.bottomRight()->file() == Chess::File::C);
        QVERIFY(sut.bottomRight()->rank() == Chess::Rank::R1);
    }

    {
        Chess::Square sut(mock, Chess::File::C, Chess::Rank::R3);
        QVERIFY(sut.bottomRight(2)->file() == Chess::File::E);
        QVERIFY(sut.bottomRight(2)->rank() == Chess::Rank::R1);
    }
}

