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

namespace Chess
{

MovementCommand::MovementCommand()
    : IMoveCommand()
    , m_to(nullptr)
    , m_from(nullptr)
    , m_movedPiece(nullptr)
{
}

MovementCommand::MovementCommand(Square &to, Piece &movedPiece)
    : IMoveCommand()
    , m_to(&to)
    , m_from(nullptr)
    , m_movedPiece(&movedPiece)
{
}

void MovementCommand::redo(Chessboard &board)
{
    Q_ASSERT(m_to->isEmpty() && "Runtime error: square is not empty. AttackCommand should be used");
    m_from = m_movedPiece->atSquare();

    m_movedPiece->markAsMoved(); // TODO: save prev. state
    board.removePiece(m_movedPiece);
    board.putPiece(m_to, m_movedPiece);
}

void MovementCommand::undo(Chessboard &board)
{
    (void)board;
}

void MovementCommand::setDestinationSquare(Square &to)
{
    m_to = &to;
}

void MovementCommand::setMovedPiece(Piece &movedPiece)
{
    m_movedPiece = &movedPiece;
}

Square &MovementCommand::destinationSquare()
{
    return *m_to;
}

const Square &MovementCommand::destinationSquare() const
{
    return *m_to;
}

Piece &MovementCommand::movedPiece()
{
    return *m_movedPiece;
}

const Piece &MovementCommand::movedPiece() const
{
    return *m_movedPiece;
}

} // namespace Chess
