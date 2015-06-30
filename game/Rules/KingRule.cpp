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

QList<Square *> KingRule::findMovesSafe(Piece &forPiece) const
{
    QList<Square *> result;
    Square *currentPosition = forPiece.atSquare();
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

    result.append(findCastling(forPiece));
    return result;
}

QList<Square *> KingRule::findAttacksSafe(Piece &forPiece) const
{
    QList<Square *> result;
    Square *currentPosition = forPiece.atSquare();
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

QList<Square *> KingRule::findCastling(Piece &forPiece) const
{
    if (forPiece.wasMoved())
    {
        return {};
    }

    Square *currentPosition = forPiece.atSquare();
    QList<Square *> result;
    const Square *aRock = squareAtMyLine(forPiece.color(), File::A);
    if (!aRock->isEmpty() && !aRock->piece()->wasMoved()
            && currentPosition->left()->isEmpty()
            && currentPosition->left()->left()->isEmpty()
            && currentPosition->left()->left()->left()->isEmpty())
    {
        result.push_back(currentPosition->left()->left());
    }

    const Square *hRock = squareAtMyLine(forPiece.color(), File::H);
    if (!hRock->isEmpty() && !hRock->piece()->wasMoved()
            && currentPosition->right()->isEmpty()
            && currentPosition->right()->right()->isEmpty())
    {
        result.push_back(currentPosition->right()->right());
    }

    return result;
}

const Square *KingRule::squareAtMyLine(const Color forColor, const File file) const
{
    return board().squareAt(Position(file, (forColor == Color::White) ? Rank::R1 : Rank::R8));
}

} // namespace Chess
