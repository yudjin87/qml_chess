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

#include "game/Commands/CastlingCommand.h"
#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Piece.h"

#include <QtCore/QDebug>

namespace Chess
{

const char* CastlingCommand::NAME = "CastlingCommand";

CastlingCommand::CastlingCommand()
    : IMoveCommand()
    , m_to(Position::A1())
    , m_from(Position::A1())
{
}

CastlingCommand::CastlingCommand(const Position &to, const Position &from)
    : IMoveCommand()
    , m_to(to)
    , m_from(from)
{
}

void CastlingCommand::redo(Chessboard &board)
{
    Square *to = board.squareAt(m_to);
    Square *from = board.squareAt(m_from);

    Q_ASSERT(to->isEmpty() && "Runtime error: square is not empty. AttackCommand should be used");
    Q_ASSERT(!from->isEmpty() && "Runtime error: square is empty");
}

void CastlingCommand::undo(Chessboard &board)
{
    (void)board;
}

QString CastlingCommand::name() const
{
    return CastlingCommand::NAME;
}

QString CastlingCommand::toString() const
{
    return QString("Castling: from %1 to %2").arg(m_from.toString()).arg(m_to.toString());
}

bool CastlingCommand::load(const QJsonObject move)
{
    const QString fromStr = move.value("from").toString();
    const QString toStr = move.value("to").toString();
    bool ok = false;
    m_from = Position::fromString(fromStr, &ok);
    if (!ok)
    {
        return false;
    }

    m_to = Position::fromString(toStr, &ok);
    if (!ok)
    {
        return false;
    }

    return true;
}

QJsonObject CastlingCommand::write() const
{
    // TODO: move to base
    QJsonObject me;
    me.insert("from", QJsonValue(m_from.toString()));
    me.insert("to", QJsonValue(m_to.toString()));
    return me;
}

void CastlingCommand::setDestinationSquare(const Position &to)
{
    m_to = to;
}

void CastlingCommand::setFromSquare(const Position &from)
{
    m_from = from;
}

} // namespace Chess



