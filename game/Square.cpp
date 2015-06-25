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

#include "game/Square.h"
#include "game/Chessboard.h"

namespace Chess
{

Square::Square(Chessboard &parent, const Position &pos)
    : QObject(&parent)
    , m_board(parent)
    , m_position(pos)
{
}

Square::Square(Chessboard &parent, const File file, const Rank rank)
    : Square(parent, Position(file, rank))
{
}

Position Square::position() const
{
    return m_position;
}

File Square::file() const
{
    return m_position.file();
}

Rank Square::rank() const
{
    return m_position.rank();
}

Color Square::color() const
{
    return m_position.color();
}

} // namespace Chess