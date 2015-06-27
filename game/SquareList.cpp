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

#include "game/SquareList.h"

namespace Chess
{

SquareList::SquareList(QObject *parent)
    : QObject(parent)
    , m_squares()
{
}

Square *SquareList::at(const int index)
{
    return const_cast<Square*>(const_cast<const SquareList*>(this)->at(index));
}

const Square *SquareList::at(const int index) const
{
    if (index < 0 || m_squares.size() <= index)
    {
        return nullptr;
    }

    return m_squares[index];
}

void SquareList::append(Square *square)
{
    m_squares.append(square);
}

int SquareList::length() const
{
    return m_squares.size();
}

void SquareList::clear()
{
    m_squares.clear();
}

int SquareList::size() const
{
    return m_squares.size();
}

} // namespace Chess
