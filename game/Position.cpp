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

#include "game/Position.h"

namespace Chess
{

Position::Position(const File file, const Rank rank)
    : m_file(file)
    , m_rank(rank)
{
}

File Position::file() const
{
    return m_file;
}

Rank Position::rank() const
{
    return m_rank;
}

Color Position::color() const
{
    const int rank = static_cast<int>(m_rank);
    const int file = static_cast<int>(m_file);
    const bool odd = ((rank + file) % 2) == 1;
    return odd ? Color::Light : Color::Dark;
}

} // namespace Chess
