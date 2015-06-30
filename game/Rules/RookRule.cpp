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

#include "game/Rules/RookRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

RookRule::RookRule(Chessboard &board, QObject* parent)
    : BaseRule(board, parent)
{
}

std::vector<Move::UPtr> RookRule::findMovesSafe(Piece &forPiece) const
{
    std::vector<Move::UPtr> result;
    Square *currentPosition = forPiece.atSquare();
    Square* left = nextMovement(currentPosition, &Square::left);
    while (left != nullptr)
    {
        if (left->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *left));
        }
        else
        {
            result.push_back(Move::create((left->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *left));
            break;
        }
        left = nextMovement(left, &Square::left);
    }

    Square* top = nextMovement(currentPosition, &Square::top);
    while (top != nullptr)
    {
        if (top->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *top));
        }
        else
        {
            result.push_back(Move::create((top->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *top));
            break;
        }
        top = nextMovement(top, &Square::top);
    }

    Square* right = nextMovement(currentPosition, &Square::right);
    while (right != nullptr)
    {
        if (right->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *right));
        }
        else
        {
            result.push_back(Move::create((right->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *right));
            break;
        }
        right = nextMovement(right, &Square::right);
    }

    Square* bottom = nextMovement(currentPosition, &Square::bottom);
    while (bottom != nullptr)
    {
        if (bottom->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *bottom));
        }
        else
        {
            result.push_back(Move::create((bottom->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *bottom));
            break;
        }
        bottom = nextMovement(bottom, &Square::bottom);
    }

    return result;
}

} // namespace Chess
