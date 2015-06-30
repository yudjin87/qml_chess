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

#ifndef MOVE_H
#define MOVE_H

#include "game/game_api.h"
#include "game/Color.h"
#include "game/Position.h"

#include <QtCore/QObject>

#include <memory>

namespace Chess
{

class Square;

class GAME_API Move : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
    Q_PROPERTY(Chess::Square* square READ square)
public:
    enum Type
    {
        Movement,
        Attack,
        Castling,
        Defend
    };

    typedef std::unique_ptr<Move> UPtr;

public:
    Move(const Type type, Square& square, QObject* parent = nullptr);

    template<class... TArgs>
    static Move::UPtr create(TArgs&&... args)
    {
        return Move::UPtr(new Move(std::forward<TArgs>(args)...));
    }

    Type type() const;
    Chess::Square* square();

    Position position() const;

signals:
    void typeChanged(Type type);

private:
    Square& m_square;
    const Type m_type;
};

struct GAME_API ByTypePredicate
{
    ByTypePredicate(const Move::Type type);
    bool operator()(const Move::UPtr& m) const;

private:
    const Move::Type m_type;
};

} // namespace Chess

#endif // MOVE_H
