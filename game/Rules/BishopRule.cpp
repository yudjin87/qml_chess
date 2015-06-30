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

#include "game/Rules/BishopRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

BishopRule::BishopRule(Chessboard &board, QObject* parent)
    : BaseRule(board, parent)
{
}

std::vector<Move::UPtr> BishopRule::findMovesSafe(Piece &forPiece) const
{
    std::vector<Move::UPtr> result;

    Square *currentPosition = forPiece.atSquare();
    Square* bottomLeft = nextMovement(currentPosition, &Square::bottomLeft);
    while (bottomLeft != nullptr)
    {
        if (bottomLeft->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *bottomLeft));
        }
        else
        {
            result.push_back(Move::create((bottomLeft->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *bottomLeft));
            break;
        }
        bottomLeft = nextMovement(bottomLeft, &Square::bottomLeft);
    }

    Square* topLeft = nextMovement(currentPosition, &Square::topLeft);
    while (topLeft != nullptr)
    {
        if (topLeft->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *topLeft));
        }
        else
        {
            result.push_back(Move::create((topLeft->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *topLeft));
            break;
        }
        topLeft = nextMovement(topLeft, &Square::topLeft);
    }

    Square* topRight = nextMovement(currentPosition, &Square::topRight);
    while (topRight != nullptr)
    {
        if (topRight->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *topRight));
        }
        else
        {
            result.push_back(Move::create((topRight->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *topRight));
            break;
        }
        topRight = nextMovement(topRight, &Square::topRight);
    }

    Square* bottomRight = nextMovement(currentPosition, &Square::bottomRight);
    while (bottomRight != nullptr)
    {
        if (bottomRight->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *bottomRight));
        }
        else
        {
            result.push_back(Move::create((bottomRight->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *bottomRight));
            break;
        }
        bottomRight = nextMovement(bottomRight, &Square::bottomRight);
    }

    return result;
}

} // namespace Chess
