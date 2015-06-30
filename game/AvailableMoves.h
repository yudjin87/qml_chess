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

#ifndef AVAILABLEMOVES_H
#define AVAILABLEMOVES_H

#include "game/game_api.h"
#include "game/Move.h"

#include <QtCore/QObject>
#include <vector>

namespace Chess
{

class Square;

class GAME_API AvailableMoves : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int length READ length)

public:
    explicit AvailableMoves(QObject* parent = nullptr);

    const Chess::Move* at(const size_t index) const;
    size_t count(const Move::Type type) const;

    void append(Move::UPtr move);

    int length() const;
    void clear();

public slots:
    int size() const;
    Chess::Move* at(const int index);
    bool contains(Chess::Move* move) const;
    bool contains(Chess::Square* square) const;
    Chess::Move* findMove(Chess::Square* square) const;

private:
    std::vector<Move::UPtr> m_moves;
};

} // namespace Chess


#endif // AVAILABLEMOVES_H
