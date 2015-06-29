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

#include "game/Commands/MovementCommand.h"
#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Piece.h"

#include <QtCore/QDebug>

namespace Chess
{

const char* MovementCommand::NAME = "MovementCommand";

MovementCommand::MovementCommand()
    : BaseCommand(MovementCommand::NAME)
{
}

MovementCommand::MovementCommand(const Position &to, const Position &from)
    : BaseCommand(MovementCommand::NAME, to, from)
{
}

bool MovementCommand::redo(Chessboard &board)
{
    Square *to = board.squareAt(toSquare());
    Square *from = board.squareAt(fromSquare());
    if (!to->isEmpty())
    {
        qCritical() << "Runtime error: square is not empty. AttackCommand should be used";
        return false;
    }

    if (from->isEmpty())
    {
        qCritical() << "Runtime error: square is empty";
        return false;
    }

    Piece* movedePiece = from->piece();
    markAsMoved(*movedePiece);
    board.removePiece(movedePiece);
    board.putPiece(to, movedePiece);
    qDebug() << "Move: " << Chess::toString(movedePiece->type()) << " " << from->toStr() << ":" << to->toStr();

    return true;
}

bool MovementCommand::undo(Chessboard &board)
{
    Square *to = board.squareAt(fromSquare());
    Square *from = board.squareAt(toSquare());
    if (!to->isEmpty())
    {
        qCritical() << "Runtime error: square is not empty. AttackCommand should be used";
        return false;
    }

    if (from->isEmpty())
    {
        qCritical() << "Runtime error: square is empty";
        return false;
    }

    Piece* movedePiece = from->piece();
    undoMarkingAsMoved(*movedePiece);
    board.removePiece(movedePiece);
    board.putPiece(to, movedePiece);
    qDebug() << "Move (Undo): " << Chess::toString(movedePiece->type()) << " " << from->toStr() << ":" << to->toStr();

        return true;
}

QString MovementCommand::toString() const
{
    return QString("Move: from %1 to %2").arg(fromSquare().toString()).arg(toSquare().toString());
}

} // namespace Chess
