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
    Chess::Color color() const;
    int index() const;
    Chess::Piece* piece();

    QString toStr() const; // toString() prints object address inside QML...

    // locations
    Square* left();
    const Square* left() const;

    Square* topLeft();
    const Square* topLeft() const;

    Square* top();
    const Square* top() const;

    Square* topRight();
    const Square* topRight() const;

    Square* right();
    const Square* right() const;

    Square* bottomRight();
    const Square* bottomRight() const;

    Square* bottom();
    const Square* bottom() const;

    Square* bottomLeft();
    const Square* bottomLeft() const;

signals:
    void colorChanged();

private:
    Chessboard& m_board;
    const Position m_position;
    Piece* m_piece;
};

} // namespace Chess

#endif // SQUARE_H
