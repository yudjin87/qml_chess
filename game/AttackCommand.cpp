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
    , m_movedPiece(nullptr)
    , m_attackedPiece(nullptr)
{
}

AttackCommand::AttackCommand(Square &to, Piece &movedPiece)
    : IMoveCommand()
    , m_to(&to)
    , m_from(nullptr)
    , m_movedPiece(&movedPiece)
    , m_attackedPiece(nullptr)
{
}

void AttackCommand::redo(Chessboard &board)
{
    Q_ASSERT(!m_to->isEmpty() && "Runtime error: square is empty. MoveCommand should be used");
    m_from = m_movedPiece->atSquare();

    m_movedPiece->markAsMoved(); // TODO: save prev. state
    board.removePiece(m_movedPiece);

    m_attackedPiece = m_to->piece();

    board.removePiece(m_attackedPiece);
    board.putPiece(m_to, m_movedPiece);
    qDebug() << "Attack: " << Chess::toString(m_movedPiece->type()) << " " << m_from->toStr() << ":" << m_to->toStr();
}

void AttackCommand::undo(Chessboard &board)
{
    (void)board;
}

void AttackCommand::setDestinationSquare(Square &to)
{
    m_to = &to;
}

void AttackCommand::setMovedPiece(Piece &movedPiece)
{
    m_movedPiece = &movedPiece;
}

Square &AttackCommand::destinationSquare()
{
    return *m_to;
}

const Square &AttackCommand::destinationSquare() const
{
    return *m_to;
}

Piece &AttackCommand::movedPiece()
{
    return *m_movedPiece;
}

const Piece &AttackCommand::movedPiece() const
{
    return *m_movedPiece;
}

} // namespace Chess

