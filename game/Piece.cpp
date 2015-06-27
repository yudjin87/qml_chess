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

#include "game/Piece.h"
#include "game/Chessboard.h"
#include "game/Square.h"

namespace Chess
{

Piece::Piece(const PieceType type, const Color color, Chessboard *parent)
    : QObject(parent)
    , m_type(type)
    , m_color(color)
    , m_board(parent)
{
    Q_ASSERT(parent != nullptr && "Null pointer is not allowed!");
}

PieceType Piece::type() const
{
    return m_type;
}

Color Piece::color() const
{
    return m_color;
}

Chessboard *Piece::board()
{
    return m_board;
}

const Chessboard *Piece::board() const
{
    return m_board;
}

Square *Piece::atSquare()
{
    return m_board->findSquare(this);
}

const Square *Piece::atSquare() const
{
    return m_board->findSquare(this);
}

} // namespace Chess
