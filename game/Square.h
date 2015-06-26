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

#ifndef SQUARE_H
#define SQUARE_H

#include "game/game_api.h"
#include "game/Color.h"
#include "game/File.h"
#include "game/Rank.h"
#include "game/Position.h"

#include <QtCore/QObject>

namespace Chess
{

class Chessboard;

class GAME_API Square : public QObject
{
    Q_OBJECT
public:
    Square(Chessboard &parent, const Position& pos);
    Square(Chessboard &parent, const File file, const Rank rank);

    Position position() const;

    Square* left(const int numberOfSquares = 1);
    const Square* left(const int numberOfSquares = 1) const;

    Square* topLeft(const int numberOfSquares = 1);
    const Square* topLeft(const int numberOfSquares = 1) const;

    Square* top(const int numberOfSquares = 1);
    const Square* top(const int numberOfSquares = 1) const;

    Square* topRight(const int numberOfSquares = 1);
    const Square* topRight(const int numberOfSquares = 1) const;

    Square* right(const int numberOfSquares = 1);
    const Square* right(const int numberOfSquares = 1) const;

    Square* bottomRight(const int numberOfSquares = 1);
    const Square* bottomRight(const int numberOfSquares = 1) const;

    Square* bottom(const int numberOfSquares = 1);
    const Square* bottom(const int numberOfSquares = 1) const;

    Square* bottomLeft(const int numberOfSquares = 1);
    const Square* bottomLeft(const int numberOfSquares = 1) const;

    // Convinient functions (short cuts for position()):
    File file() const;
    Rank rank() const;
    int index() const;
    Color color() const;

private:
    Chessboard& m_board;
    const Position m_position;
};

} // namespace Chess
#endif // SQUARE_H
