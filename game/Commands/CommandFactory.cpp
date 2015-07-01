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

#include "game/Commands/CommandFactory.h"
#include "game/Commands/AttackCommand.h"
#include "game/Commands/CastlingCommand.h"
#include "game/Commands/MovementCommand.h"


#include <QtCore/QDebug>

namespace Chess
{

IMoveCommand::UPtr CommandFactory::create(const Move::Type movementType)
{
    switch (movementType)
    {
    case Move::Movement:
        return MovementCommand::create();
    case Move::Attack:
        return AttackCommand::create();
    case Move::Defend:
        qCritical() << "No command supported for the \"Move::Defend\"";
        break;
    case Move::Castling:
        return CastlingCommand::create();
    }

    qCritical() << "Unknown movementType" << movementType;
    return nullptr;
}

IMoveCommand::UPtr CommandFactory::create(const Move::Type movementType, const Position &to, const Position &from)
{
    switch (movementType)
    {
    case Move::Movement:
        return MovementCommand::create(to, from);
    case Move::Attack:
        return AttackCommand::create(to, from);
    case Move::Defend:
        qCritical() << "No command supported for the \"Move::Defend\"";
        break;
    case Move::Castling:
        return CastlingCommand::create(to, from);
    }

    qCritical() << "Unknown movementType" << movementType;
    return nullptr;
}


} // namespace Chess
