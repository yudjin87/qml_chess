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

const char* AttackCommand::NAME = "AttackCommand";

AttackCommand::AttackCommand()
    : IMoveCommand()
    , m_to(Position::A1())
    , m_from(Position::A1())
{
}

AttackCommand::AttackCommand(const Position &to, const Position &from)
    : IMoveCommand()
    , m_to(to)
    , m_from(from)
{
}

void AttackCommand::redo(Chessboard &board)
{
    Square *to = board.squareAt(m_to);
    Square *from = board.squareAt(m_from);

    Q_ASSERT(!to->isEmpty() && "Runtime error: square is empty. MoveCommand should be used");
    Q_ASSERT(!from->isEmpty() && "Runtime error: square is empty");

    Piece* movedePiece = from->piece();
    movedePiece->markAsMoved(); // TODO: save prev. state
    board.removePiece(movedePiece);

    Piece* attackedPiece = to->piece();
    board.removePiece(attackedPiece);
    board.putPiece(to, movedePiece);
    qDebug() << "Attack: " << Chess::toString(movedePiece->type()) << " " << from->toStr() << ":" << to->toStr();
}

void AttackCommand::undo(Chessboard &board)
{
    (void)board;
}

QString AttackCommand::name() const
{
    return AttackCommand::NAME;
}

bool AttackCommand::load(const QJsonObject move)
{
    (void) move;
    return false;
}

QJsonObject AttackCommand::write() const
{
    QJsonObject me;
    return me;
}

void AttackCommand::setDestinationSquare(const Position &to)
{
    m_to = to;
}

void AttackCommand::setFromSquare(const Position &from)
{
    m_from = from;
}

} // namespace Chess

