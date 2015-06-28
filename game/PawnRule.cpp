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

#include "game/PawnRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

PawnRule::PawnRule(Chessboard &board, QObject* parent)
    : IMovementRule(parent)
    , m_board(board)
{
}

QList<Square *> PawnRule::findMoves(Piece &forPiece) const
{
    Square *currentPosition = forPiece.atSquare();
    Q_ASSERT(currentPosition != nullptr && "Null poiner is not allowed");

    QList<Square *> result;
    if (!m_board.contains(currentPosition))
    {
        qWarning() << "currentPosition doesn't belong to specified board";
        return result;
    }

    Square* shortMovement = nextMovement(forPiece.color(), currentPosition);
    if (shortMovement == nullptr)
    {
        return result;
    }

    if (!shortMovement->isEmpty())
    {
        return result;
    }

    result.push_back(shortMovement); // TODO: check for possible check

    if (forPiece.wasMoved())
    {
        // This pawn was already moved, so long movement is not possible
        return result;
    }

    Square* longMovement = nextMovement(forPiece.color(), shortMovement);
    if (longMovement == nullptr)
    {
        return result;
    }

    if (longMovement->isEmpty())
    {
        result.push_back(longMovement); // TODO: check for possible check
    }

    return result;
}

QList<Square *> PawnRule::findAttacks(Piece &forPiece) const
{
    Square *currentPosition = forPiece.atSquare();
    Q_ASSERT(currentPosition != nullptr && "Null poiner is not allowed");

    QList<Square *> result;
    Square* rightAttack = nextRightAttack(forPiece.color(), currentPosition);
    if (rightAttack != nullptr && !rightAttack->isEmpty())
    {
        const Piece* piece = rightAttack->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(rightAttack);
        }
    }

    Square* leftAttack = nextLeftAttack(forPiece.color(), currentPosition);
    if (leftAttack != nullptr && !leftAttack->isEmpty())
    {
        const Piece* piece = leftAttack->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(leftAttack);
        }
    }

    return result;
}

Square *PawnRule::nextMovement(const Color ownColor, Square *basePosition) const
{
    if (ownColor == Color::White)
    {
        return basePosition->top();
    }

    return basePosition->bottom();
}

Square *PawnRule::nextRightAttack(const Color ownColor, Square *basePosition) const
{
    if (ownColor == Color::White)
    {
        return basePosition->topRight();
    }

    return basePosition->bottomLeft();
}

Square *PawnRule::nextLeftAttack(const Color ownColor, Square *basePosition) const
{
    if (ownColor == Color::White)
    {
        return basePosition->topLeft();
    }

    return basePosition->bottomRight();
}

} // namespace Chess
