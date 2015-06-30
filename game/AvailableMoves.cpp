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

#include "game/AvailableMoves.h"
#include <algorithm>

namespace Chess
{

AvailableMoves::AvailableMoves(QObject* parent)
    : QObject(parent)
    , m_moves()
{
}

Move *AvailableMoves::at(const int index)
{
    return const_cast<Move*>(const_cast<const AvailableMoves*>(this)->at(index));
}

const Move *AvailableMoves::at(const size_t index) const
{
    if (index < 0 || m_moves.size() <= index)
    {
        return nullptr;
    }

    return m_moves[index].get();
}

size_t AvailableMoves::count(const Move::Type type) const
{
    const auto byType = [type](const Move::UPtr& m) { return m->type() == type;};
    return std::count_if(std::begin(m_moves), std::end(m_moves), byType);
}

void AvailableMoves::append(Move::UPtr move)
{
    move->setParent(nullptr);
    m_moves.push_back(std::move(move));
}

int AvailableMoves::length() const
{
    return m_moves.size();
}

void AvailableMoves::clear()
{
    m_moves.clear();
}

bool AvailableMoves::contains(Move *move) const
{
    const auto byUPtr = [move](const Move::UPtr& m) { return m.get() == move;};
    const auto it = std::find_if(std::begin(m_moves), std::end(m_moves), byUPtr);
    return it != std::end(m_moves);
}

bool AvailableMoves::contains(Square *square) const
{
    return findMove(square) != nullptr;
}

Move *AvailableMoves::findMove(Square *square) const
{
    const auto bySquare = [square](const Move::UPtr& m) { return m->square() == square;};
    const auto it = std::find_if(std::begin(m_moves), std::end(m_moves), bySquare);
    return (it == std::end(m_moves)) ? nullptr : (*it).get();
}

int AvailableMoves::size() const
{
    return m_moves.size();
}

} // namespace Chess
