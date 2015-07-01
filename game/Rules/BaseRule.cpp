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

#include "game/Rules/BaseRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

BaseRule::BaseRule(Chessboard &board, QObject* parent)
    : IMovementRule(parent)
    , m_board(board)
{
}

std::vector<Move::UPtr> BaseRule::findMoves(Piece &forPiece) const
{
    // TODO: check for possible "check" in all rules

    Square *currentPosition = forPiece.atSquare();
    Q_ASSERT(currentPosition != nullptr && "Null poiner is not allowed");

    if (!m_board.contains(currentPosition))
    {
        qWarning() << "currentPosition doesn't belong to specified board";
        return {};
    }

    return findMovesSafe(forPiece);
}

Square *BaseRule::nextMovement(Square *base, BaseRule::DirectionFunc dirFunc) const
{
    Square* next = (base->*dirFunc)();
    return next;
}

Move::UPtr BaseRule::createMove(Square *square, Piece &forPiece) const
{
    if (square->isEmpty())
    {
        return Move::create(Move::Movement, *square);
    }

    if (square->piece()->color() != forPiece.color())
    {
        return Move::create(Move::Attack, *square);
    }

    return nullptr;
}

Chessboard &BaseRule::board()
{
    return m_board;
}

const Chessboard &BaseRule::board() const
{
    return m_board;
}


} // namespace Chess
