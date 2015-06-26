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

#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Position.h"

#include <algorithm>

namespace Chess
{

Chessboard::Chessboard(QObject *parent)
    : QObject(parent)
    , m_squares()
{
    for (Position p = Position(File::A, Rank::R1); p < Position(File::H, Rank::R8); ++p)
    {
        m_squares.push_back(new Square(*this, p));
    }
    m_squares.push_back(new Square(*this, Position(File::H, Rank::R8)));
}

Square *Chessboard::squareAt(const Position &pos)
{
    return const_cast<Square*>(const_cast<const Chessboard*>(this)->squareAt(pos));
}

const Square *Chessboard::squareAt(const Position &pos) const
{
    const auto byPos = [&pos](const Square* s) { return s->position() == pos;};
    const auto it = std::find_if(std::begin(m_squares), std::end(m_squares), byPos);
    if (it == std::end(m_squares))
    {
        return nullptr;
    }

    return *it;
}

Square *Chessboard::squareByIdex(const int index)
{
    return const_cast<Square*>(const_cast<const Chessboard*>(this)->squareByIdex(index));
}

const Square *Chessboard::squareByIdex(const int index) const
{
    if (index < 0 || m_squares.size() <= index)
    {
        return nullptr;
    }

    return m_squares[index];
}

int Chessboard::size() const
{
    return m_squares.size();
}

} // namespace Chess
