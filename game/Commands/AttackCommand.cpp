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

#include "game/Commands/AttackCommand.h"
#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Piece.h"

#include <QtCore/QDebug>

namespace Chess
{

AttackCommand::AttackCommand()
    : BaseCommand(Move::Attack)
    , m_killedPiece(nullptr)
{
}

AttackCommand::AttackCommand(const Position &to, const Position &from)
    : BaseCommand(Move::Attack, to, from)
    , m_killedPiece(nullptr)
{
}

bool AttackCommand::redo(Chessboard &board)
{
    Square *to = board.squareAt(toSquare());
    Square *from = board.squareAt(fromSquare());

    if (to->isEmpty())
    {
        qCritical() << "Runtime error: square is empty. MoveCommand should be used";
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

    m_killedPiece = to->piece();
    board.removePiece(m_killedPiece);
    board.putPiece(to, movedePiece);
    qDebug() << "Attack: " << Chess::toString(movedePiece->type()) << " " << from->toStr() << ":" << to->toStr();

    return true;
}

bool AttackCommand::undo(Chessboard &board)
{
    Square *to = board.squareAt(fromSquare());
    Square *from = board.squareAt(toSquare());

    if (!to->isEmpty())
    {
        qCritical() << "Runtime error: square is not empty";
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

    board.putPiece(from, m_killedPiece);
    m_killedPiece = nullptr;

    qDebug() << "Attack (Undo): " << Chess::toString(movedePiece->type()) << " " << from->toStr() << ":" << to->toStr();

    return true;
}

QString AttackCommand::toString() const
{
    return QString("Attack: from %1 to %2").arg(fromSquare().toString()).arg(toSquare().toString());
}

} // namespace Chess

