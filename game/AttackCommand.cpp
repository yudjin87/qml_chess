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

#include "game/AttackCommand.h"
#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Piece.h"

#include <QtCore/QDebug>

namespace Chess
{

AttackCommand::AttackCommand()
    : IMoveCommand()
    , m_to(nullptr)
    , m_from(nullptr)
{
}

AttackCommand::AttackCommand(Square &to, Square &from)
    : IMoveCommand()
    , m_to(&to)
    , m_from(&from)
{
}

void AttackCommand::redo(Chessboard &board)
{
    Q_ASSERT(!m_to->isEmpty() && "Runtime error: square is empty. MoveCommand should be used");
    Q_ASSERT(!m_from->isEmpty() && "Runtime error: square is empty");

    Piece* movedePiece = m_from->piece();
    movedePiece->markAsMoved(); // TODO: save prev. state
    board.removePiece(movedePiece);

    Piece* attackedPiece = m_to->piece();
    board.removePiece(attackedPiece);
    board.putPiece(m_to, movedePiece);
    qDebug() << "Attack: " << Chess::toString(movedePiece->type()) << " " << m_from->toStr() << ":" << m_to->toStr();
}

void AttackCommand::undo(Chessboard &board)
{
    (void)board;
}

QJsonObject AttackCommand::write() const
{
    QJsonObject me;
    return me;
}

void AttackCommand::setDestinationSquare(Square &to)
{
    m_to = &to;
}

Square &AttackCommand::destinationSquare()
{
    return *m_to;
}

const Square &AttackCommand::destinationSquare() const
{
    return *m_to;
}

Square *AttackCommand::from()
{
    return m_from;
}

const Square *AttackCommand::from() const
{
    return m_from;
}

} // namespace Chess

