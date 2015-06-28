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

#include <QtCore/QDebug>

namespace Chess
{

KingRule::KingRule(Chessboard &board, QObject* parent)
    : IMovementRule(parent)
    , m_board(board)
{
}

QList<Square *> KingRule::findMoves(Piece &forPiece) const
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
    if ((bottomLeft != nullptr) && bottomLeft->isEmpty())
    {
        result.push_back(bottomLeft);
        bottomLeft = nextMovement(bottomLeft, &Square::bottomLeft);
    }

    Square* left = nextMovement(currentPosition, &Square::left);
    if ((left != nullptr) && left->isEmpty())
    {
        result.push_back(left);
        left = nextMovement(left, &Square::left);
    }

    Square* topLeft = nextMovement(currentPosition, &Square::topLeft);
    if ((topLeft != nullptr) && topLeft->isEmpty())
    {
        result.push_back(topLeft);
        topLeft = nextMovement(topLeft, &Square::topLeft);
    }

    Square* top = nextMovement(currentPosition, &Square::top);
    if ((top != nullptr) && top->isEmpty())
    {
        result.push_back(top);
        top = nextMovement(top, &Square::top);
    }

    Square* topRight = nextMovement(currentPosition, &Square::topRight);
    if ((topRight != nullptr) && topRight->isEmpty())
    {
        result.push_back(topRight);
        topRight = nextMovement(topRight, &Square::topRight);
    }

    Square* right = nextMovement(currentPosition, &Square::right);
    if ((right != nullptr) && right->isEmpty())
    {
        result.push_back(right);
        right = nextMovement(right, &Square::right);
    }

    Square* bottomRight = nextMovement(currentPosition, &Square::bottomRight);
    if ((bottomRight != nullptr) && bottomRight->isEmpty())
    {
        result.push_back(bottomRight);
        bottomRight = nextMovement(bottomRight, &Square::bottomRight);
    }

    Square* bottom = nextMovement(currentPosition, &Square::bottom);
    if ((bottom != nullptr) && bottom->isEmpty())
    {
        result.push_back(bottom);
        bottom = nextMovement(bottom, &Square::bottom);
    }

    return result;
}

QList<Square *> KingRule::findAttacks(Piece &forPiece) const
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
    if (bottomLeft != nullptr && !bottomLeft->isEmpty() && bottomLeft->piece()->color() != forPiece.color())
    {
        result.push_back(bottomLeft);
    }

    Square* left = nextMovement(currentPosition, &Square::left);
    if (left != nullptr && !left->isEmpty() && left->piece()->color() != forPiece.color())
    {
        result.push_back(left);
    }

    Square* topLeft = nextMovement(currentPosition, &Square::topLeft);
    if (topLeft != nullptr && !topLeft->isEmpty() && topLeft->piece()->color() != forPiece.color())
    {
        result.push_back(topLeft);
    }

    Square* top = nextMovement(currentPosition, &Square::top);
    if (top != nullptr && !top->isEmpty() && top->piece()->color() != forPiece.color())
    {
        result.push_back(top);
    }

    Square* topRight = nextMovement(currentPosition, &Square::topRight);
    if (topRight != nullptr && !topRight->isEmpty() && topRight->piece()->color() != forPiece.color())
    {
        result.push_back(topRight);
    }

    Square* right = nextMovement(currentPosition, &Square::right);
    if (right != nullptr && !right->isEmpty() && right->piece()->color() != forPiece.color())
    {
        result.push_back(right);
    }

    Square* bottomRight = nextMovement(currentPosition, &Square::bottomRight);
    if (bottomRight != nullptr && !bottomRight->isEmpty() && bottomRight->piece()->color() != forPiece.color())
    {
        result.push_back(bottomRight);
    }

    Square* bottom = nextMovement(currentPosition, &Square::bottom);
    if (bottom != nullptr && !bottom->isEmpty() && bottom->piece()->color() != forPiece.color())
    {
        result.push_back(bottom);
    }

    return result;
}

Square *KingRule::nextMovement(Square *base, KingRule::DirectionFunc dirFunc) const
{
    Square* next = (base->*dirFunc)();
    return next;
}

} // namespace Chess
