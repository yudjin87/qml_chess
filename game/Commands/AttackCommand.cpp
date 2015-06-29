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

const char* AttackCommand::NAME = "AttackCommand";

AttackCommand::AttackCommand()
    : BaseCommand(AttackCommand::NAME)
    , m_killedPiece(nullptr)
{
}

AttackCommand::AttackCommand(const Position &to, const Position &from)
    : BaseCommand(AttackCommand::NAME, to, from)
    , m_killedPiece(nullptr)
{
}

void AttackCommand::redo(Chessboard &board)
{
    Square *to = board.squareAt(toSquare());
    Square *from = board.squareAt(fromSquare());

    Q_ASSERT(!to->isEmpty() && "Runtime error: square is empty. MoveCommand should be used");
    Q_ASSERT(!from->isEmpty() && "Runtime error: square is empty");

    Piece* movedePiece = from->piece();
    markAsMoved(*movedePiece);
    board.removePiece(movedePiece);

    m_killedPiece = to->piece();
    board.removePiece(m_killedPiece);
    board.putPiece(to, movedePiece);
    qDebug() << "Attack: " << Chess::toString(movedePiece->type()) << " " << from->toStr() << ":" << to->toStr();
}

void AttackCommand::undo(Chessboard &board)
{
    Square *to = board.squareAt(fromSquare());
    Square *from = board.squareAt(toSquare());
    Q_ASSERT(to->isEmpty() && "Runtime error: square is not empty");
    Q_ASSERT(!from->isEmpty() && "Runtime error: square is empty");

    Piece* movedePiece = from->piece();
    undoMarkingAsMoved(*movedePiece);
    board.removePiece(movedePiece);
    board.putPiece(to, movedePiece);

    board.putPiece(from, m_killedPiece);
    m_killedPiece = nullptr;

    qDebug() << "Attack (Undo): " << Chess::toString(movedePiece->type()) << " " << from->toStr() << ":" << to->toStr();
}

QString AttackCommand::toString() const
{
    return QString("Attack: from %1 to %2").arg(fromSquare().toString()).arg(toSquare().toString());
}

} // namespace Chess

