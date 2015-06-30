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

#include "game/Rules/KingRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"
#include "game/Position.h"

#include <QtCore/QDebug>

namespace Chess
{

KingRule::KingRule(Chessboard &board, QObject* parent)
    : BaseRule(board, parent)
{
}

std::vector<Move::UPtr> KingRule::findMovesSafe(Piece &forPiece) const
{
    std::vector<Move::UPtr> result;
    Square *currentPosition = forPiece.atSquare();
    Square* bottomLeft = nextMovement(currentPosition, &Square::bottomLeft);
    if (bottomLeft != nullptr)
    {
        if (bottomLeft->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *bottomLeft));
        }
        else
        {
            result.push_back(Move::create((bottomLeft->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *bottomLeft));
        }
    }

    Square* left = nextMovement(currentPosition, &Square::left);
    if (left != nullptr)
    {
        if (left->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *left));
        }
        else
        {
            result.push_back(Move::create((left->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *left));
        }
    }

    Square* topLeft = nextMovement(currentPosition, &Square::topLeft);
    if (topLeft != nullptr)
    {
        if (topLeft->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *topLeft));
        }
        else
        {
            result.push_back(Move::create((topLeft->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *topLeft));
        }
    }

    Square* top = nextMovement(currentPosition, &Square::top);
    if (top != nullptr)
    {
        if (top->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *top));
        }
        else
        {
            result.push_back(Move::create((top->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *top));
        }
    }

    Square* topRight = nextMovement(currentPosition, &Square::topRight);
    if (topRight != nullptr)
    {
        if (topRight->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *topRight));
        }
        else
        {
            result.push_back(Move::create((topRight->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *topRight));
        }
    }

    Square* right = nextMovement(currentPosition, &Square::right);
    if (right != nullptr)
    {
        if (right->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *right));
        }
        else
        {
            result.push_back(Move::create((right->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *right));
        }
    }

    Square* bottomRight = nextMovement(currentPosition, &Square::bottomRight);
    if (bottomRight != nullptr)
    {
        if (bottomRight->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *bottomRight));
        }
        else
        {
            result.push_back(Move::create((bottomRight->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *bottomRight));
        }
    }

    Square* bottom = nextMovement(currentPosition, &Square::bottom);
    if (bottom != nullptr)
    {
        if (bottom->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *bottom));
        }
        else
        {
            result.push_back(Move::create((bottom->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *bottom));
        }
    }

    // castling
    if (forPiece.wasMoved())
    {
        return result;
    }

    const Square *aRock = squareAtMyLine(forPiece.color(), File::A);
    if (!aRock->isEmpty() && !aRock->piece()->wasMoved()
            && currentPosition->left()->isEmpty()
            && currentPosition->left()->left()->isEmpty()
            && currentPosition->left()->left()->left()->isEmpty())
    {
        result.push_back(Move::create(Move::Castling, *currentPosition->left()->left()));
    }

    const Square *hRock = squareAtMyLine(forPiece.color(), File::H);
    if (!hRock->isEmpty() && !hRock->piece()->wasMoved()
            && currentPosition->right()->isEmpty()
            && currentPosition->right()->right()->isEmpty())
    {
        result.push_back(Move::create(Move::Castling, *currentPosition->right()->right()));
    }

    return result;
}

const Square *KingRule::squareAtMyLine(const Color forColor, const File file) const
{
    return board().squareAt(Position(file, (forColor == Color::White) ? Rank::R1 : Rank::R8));
}

} // namespace Chess
