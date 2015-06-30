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

#include "game/Rules/PawnRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

PawnRule::PawnRule(Chessboard &board, QObject* parent)
    : BaseRule(board, parent)
{
}

std::vector<Move::UPtr> PawnRule::findMovesSafe(Piece &forPiece) const
{
    std::vector<Move::UPtr> result;
    Square *currentPosition = forPiece.atSquare();
    Square* rightAttack = nextRightAttack(forPiece.color(), currentPosition);
    if (rightAttack != nullptr && !rightAttack->isEmpty())
    {
        const Piece* piece = rightAttack->piece();
        result.push_back(Move::create((piece->color() == forPiece.color()) ? Move::Defend : Move::Attack, *rightAttack));
    }

    Square* leftAttack = nextLeftAttack(forPiece.color(), currentPosition);
    if (leftAttack != nullptr && !leftAttack->isEmpty())
    {
        const Piece* piece = leftAttack->piece();
        result.push_back(Move::create((piece->color() == forPiece.color()) ? Move::Defend : Move::Attack, *leftAttack));
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

    result.push_back(Move::create(Move::Movement, *shortMovement)); // TODO: check for possible check

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
        result.push_back(Move::create(Move::Movement, *longMovement)); // TODO: check for possible check
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
