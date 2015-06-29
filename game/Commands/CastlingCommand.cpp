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
    : BaseCommand(CastlingCommand::NAME)
{
}

CastlingCommand::CastlingCommand(const Position &to, const Position &from)
    : BaseCommand(CastlingCommand::NAME, to, from)
{
}

void CastlingCommand::redo(Chessboard &board)
{
    Square *to = board.squareAt(toSquare());
    Square *from = board.squareAt(fromSquare());

    Q_ASSERT(to->isEmpty() && "Runtime error: square is not empty. AttackCommand should be used");
    Q_ASSERT(!from->isEmpty() && "Runtime error: square is empty");
}

void CastlingCommand::undo(Chessboard &board)
{
    (void)board;
}

QString CastlingCommand::toString() const
{
    return QString("Castling: from %1 to %2").arg(fromSquare().toString()).arg(toSquare().toString());
}

} // namespace Chess



