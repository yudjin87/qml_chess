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

#include "game/QueenRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

QueenRule::QueenRule(Chessboard &board, QObject* parent)
    : IMovementRule(parent)
    , m_board(board)
{
}

QList<Square *> QueenRule::findMoves(Piece &forPiece) const
{
    Square *currentPosition = forPiece.atSquare();
    Q_ASSERT(currentPosition != nullptr && "Null poiner is not allowed");

    QList<Square *> result;
    if (!m_board.contains(currentPosition))
    {
        qWarning() << "currentPosition doesn't belong to specified board";
        return result;
    }

    Square* bottomLeft = nextMovement(currentPosition, &Square::bottomLeft);
    while ((bottomLeft != nullptr) && bottomLeft->isEmpty())
    {
        result.push_back(bottomLeft);
        bottomLeft = nextMovement(bottomLeft, &Square::bottomLeft);
    }

    Square* left = nextMovement(currentPosition, &Square::left);
    while ((left != nullptr) && left->isEmpty())
    {
        result.push_back(left);
        left = nextMovement(left, &Square::left);
    }

    Square* topLeft = nextMovement(currentPosition, &Square::topLeft);
    while ((topLeft != nullptr) && topLeft->isEmpty())
    {
        result.push_back(topLeft);
        topLeft = nextMovement(topLeft, &Square::topLeft);
    }

    Square* top = nextMovement(currentPosition, &Square::top);
    while ((top != nullptr) && top->isEmpty())
    {
        result.push_back(top);
        top = nextMovement(top, &Square::top);
    }

    Square* topRight = nextMovement(currentPosition, &Square::topRight);
    while ((topRight != nullptr) && topRight->isEmpty())
    {
        result.push_back(topRight);
        topRight = nextMovement(topRight, &Square::topRight);
    }

    Square* right = nextMovement(currentPosition, &Square::right);
    while ((right != nullptr) && right->isEmpty())
    {
        result.push_back(right);
        right = nextMovement(right, &Square::right);
    }

    Square* bottomRight = nextMovement(currentPosition, &Square::bottomRight);
    while ((bottomRight != nullptr) && bottomRight->isEmpty())
    {
        result.push_back(bottomRight);
        bottomRight = nextMovement(bottomRight, &Square::bottomRight);
    }

    Square* bottom = nextMovement(currentPosition, &Square::bottom);
    while ((bottom != nullptr) && bottom->isEmpty())
    {
        result.push_back(bottom);
        bottom = nextMovement(bottom, &Square::bottom);
    }

    return result;
}

QList<Square *> QueenRule::findAttacks(Piece &forPiece) const
{
    Square *currentPosition = forPiece.atSquare();
    Q_ASSERT(currentPosition != nullptr && "Null poiner is not allowed");

    QList<Square *> result; // TODO: base class
    if (!m_board.contains(currentPosition))
    {
        qWarning() << "currentPosition doesn't belong to specified board";
        return result;
    }

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

    Square* left = nextMovement(currentPosition, &Square::left);
    while ((left != nullptr))
    {
        if (left->isEmpty())
        {
            left = nextMovement(left, &Square::left);
            continue;
        }

        const Piece* piece = left->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(left);
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

    Square* top = nextMovement(currentPosition, &Square::top);
    while ((top != nullptr))
    {
        if (top->isEmpty())
        {
            top = nextMovement(top, &Square::top);
            continue;
        }

        const Piece* piece = top->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(top);
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

    Square* right = nextMovement(currentPosition, &Square::right);
    while ((right != nullptr))
    {
        if (right->isEmpty())
        {
            right = nextMovement(right, &Square::right);
            continue;
        }

        const Piece* piece = right->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(right);
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

    Square* bottom = nextMovement(currentPosition, &Square::bottom);
    while ((bottom != nullptr))
    {
        if (bottom->isEmpty())
        {
            bottom = nextMovement(bottom, &Square::bottom);
            continue;
        }

        const Piece* piece = bottom->piece();
        if (piece->color() != forPiece.color())
        {
            result.push_back(bottom);
        }
        break;
    }

    return result;
}

Square *QueenRule::nextMovement(Square *base, QueenRule::DirectionFunc dirFunc) const
{
    Square* next = (base->*dirFunc)();
    return next;
}

} // namespace Chess

