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
class Piece;

class GAME_API Square : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(Chess::Color color READ color NOTIFY colorChanged)
public:
    Square(Chessboard &parent, const Position& pos);
    Square(Chessboard &parent, const File file, const Rank rank);

    // Convinient functions (short cuts for position()):
    File file() const;
    Rank rank() const;

    Position position() const;

    const Piece* piece() const;

    void setPiece(Piece& piece);
    void removePiece();

    bool isEmpty() const;

public slots:
    int index() const;
    Chess::Piece* piece();

    Chess::Color color() const; // TODO: property
    QString toStr() const; // TODO: toString() prints address...

    // locations
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

signals:
    void colorChanged();

private:
    Chessboard& m_board;
    const Position m_position;
    Piece* m_piece;
};

} // namespace Chess
#endif // SQUARE_H
