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

#include "game/MovementCommand.h"
#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Piece.h"

#include <QtCore/QDebug>

namespace Chess
{

MovementCommand::MovementCommand()
    : IMoveCommand()
    , m_to(nullptr)
    , m_from(nullptr)
{
}

MovementCommand::MovementCommand(Square &to, Square &from)
    : IMoveCommand()
    , m_to(&to)
    , m_from(&from)
{
}

void MovementCommand::redo(Chessboard &board)
{
    Q_ASSERT(m_to->isEmpty() && "Runtime error: square is not empty. AttackCommand should be used");
    Q_ASSERT(!m_from->isEmpty() && "Runtime error: square is empty");

    Piece* movedePiece = m_from->piece();
    movedePiece->markAsMoved(); // TODO: save prev. state
    board.removePiece(movedePiece);
    board.putPiece(m_to, movedePiece);
    qDebug() << "Move: " << Chess::toString(movedePiece->type()) << " " << m_from->toStr() << ":" << m_to->toStr();
}

void MovementCommand::undo(Chessboard &board)
{
    (void)board;
}

QJsonObject MovementCommand::write() const
{
    QJsonObject me;
    me.insert("to", QJsonValue(m_to->position().toString()));
    return me;
}

void MovementCommand::setDestinationSquare(Square &to)
{
    m_to = &to;
}

void MovementCommand::setFromSquare(Square &from)
{
    m_from = &from;
}

Square &MovementCommand::destinationSquare()
{
    return *m_to;
}

const Square &MovementCommand::destinationSquare() const
{
    return *m_to;
}

Square *MovementCommand::from()
{
    return m_from;
}

const Square *MovementCommand::from() const
{
    return m_from;
}

} // namespace Chess
