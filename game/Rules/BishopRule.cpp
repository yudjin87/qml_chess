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

QList<Square *> BishopRule::findMovesSafe(Piece &forPiece) const
{
    QList<Square *> result;

    Square *currentPosition = forPiece.atSquare();
    Square* bottomLeft = nextMovement(currentPosition, &Square::bottomLeft);
    while ((bottomLeft != nullptr) && bottomLeft->isEmpty())
    {
        result.push_back(bottomLeft);
        bottomLeft = nextMovement(bottomLeft, &Square::bottomLeft);
    }

    Square* topLeft = nextMovement(currentPosition, &Square::topLeft);
    while ((topLeft != nullptr) && topLeft->isEmpty())
    {
        result.push_back(topLeft);
        topLeft = nextMovement(topLeft, &Square::topLeft);
    }

    Square* bottomRight = nextMovement(currentPosition, &Square::bottomRight);
    while ((bottomRight != nullptr) && bottomRight->isEmpty())
    {
        result.push_back(bottomRight);
        bottomRight = nextMovement(bottomRight, &Square::bottomRight);
    }

    Square* topRight = nextMovement(currentPosition, &Square::topRight);
    while ((topRight != nullptr) && topRight->isEmpty())
    {
        result.push_back(topRight);
        topRight = nextMovement(topRight, &Square::topRight);
    }

    return result;
}

QList<Square *> BishopRule::findAttacksSafe(Piece &forPiece) const
{
    QList<Square *> result;

    Square *currentPosition = forPiece.atSquare();
    Square* bottomLeft = nextMovement(currentPosition, &Square::bottomLeft);
    while ((bottomLeft != nullptr))
    {
        if (bottomLeft->isEmpty())
        {
            bottomLeft = nextMovement(bottomLeft, &Square::bottomLeft);
            continue;
        }

        const Piece* piece = bottomLeft->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(bottomLeft);
        }
        break;
    }

    Square* topLeft = nextMovement(currentPosition, &Square::topLeft);
    while ((topLeft != nullptr))
    {
        if (topLeft->isEmpty())
        {
            topLeft = nextMovement(topLeft, &Square::topLeft);
            continue;
        }

        const Piece* piece = topLeft->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(topLeft);
        }
        break;
    }

    Square* bottomRight = nextMovement(currentPosition, &Square::bottomRight);
    while ((bottomRight != nullptr))
    {
        if (bottomRight->isEmpty())
        {
            bottomRight = nextMovement(bottomRight, &Square::bottomRight);
            continue;
        }

        const Piece* piece = bottomRight->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(bottomRight);
        }
        break;
    }

    Square* topRight = nextMovement(currentPosition, &Square::topRight);
    while ((topRight != nullptr))
    {
        if (topRight->isEmpty())
        {
            topRight = nextMovement(topRight, &Square::topRight);
            continue;
        }

        const Piece* piece = topRight->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(topRight);
        }
        break;
    }

    return result;
}

} // namespace Chess
