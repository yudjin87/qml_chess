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

#include "game/Rules/QueenRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

QueenRule::QueenRule(Chessboard &board, QObject* parent)
    : BaseRule(board, parent)
{
}

std::vector<Move::UPtr> QueenRule::findMovesSafe(Piece &forPiece) const
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

