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

#include "game_test/SquareTest.h"

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
        Chess::Square sut(mock, Chess::Position::A1());
        QVERIFY(sut.color() == Chess::Color::Black);
    }

    {
        Chess::Square sut(mock, Chess::Position::A8());
        QVERIFY(sut.color() == Chess::Color::White);
    }

    {
        Chess::Square sut(mock, Chess::Position::H8());
        QVERIFY(sut.color() == Chess::Color::Black);
    }

    {
        Chess::Square sut(mock, Chess::Position::H1());
        QVERIFY(sut.color() == Chess::Color::White);
    }

    {
        Chess::Square sut(mock, Chess::Position::E4());
        QVERIFY(sut.color() == Chess::Color::White);
    }
}

void SquareTest::leftTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::A1());
        QVERIFY(sut.left() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B1());
        QVERIFY(sut.left()->file() == Chess::File::A);
    }
}

void SquareTest::topLeftTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::A1());
        QVERIFY(sut.topLeft() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B1());
        QVERIFY(sut.topLeft()->file() == Chess::File::A);
        QVERIFY(sut.topLeft()->rank() == Chess::Rank::R2);
    }
}

void SquareTest::topTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::A8());
        QVERIFY(sut.top() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B1());
        QVERIFY(sut.top()->rank() == Chess::Rank::R2);
    }
}

void SquareTest::topRightTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::H1());
        QVERIFY(sut.topRight() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B1());
        QVERIFY(sut.topRight()->file() == Chess::File::C);
        QVERIFY(sut.topRight()->rank() == Chess::Rank::R2);
    }
}

void SquareTest::rightTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::H1());
        QVERIFY(sut.right() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B1());
        QVERIFY(sut.right()->file() == Chess::File::C);
    }
}

void SquareTest::bottomTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::A1());
        QVERIFY(sut.bottom() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B7());
        QVERIFY(sut.bottom()->rank() == Chess::Rank::R6);
    }
}

void SquareTest::bottomLeftTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::A1());
        QVERIFY(sut.bottomLeft() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B2());
        QVERIFY(sut.bottomLeft()->file() == Chess::File::A);
        QVERIFY(sut.bottomLeft()->rank() == Chess::Rank::R1);
    }
}

void SquareTest::bottomRightTest()
{
    Chess::Chessboard mock;

    {
        Chess::Square sut(mock, Chess::Position::A1());
        QVERIFY(sut.bottomRight() == nullptr);
    }

    {
        Chess::Square sut(mock, Chess::Position::B2());
        QVERIFY(sut.bottomRight()->file() == Chess::File::C);
        QVERIFY(sut.bottomRight()->rank() == Chess::Rank::R1);
    }
}

