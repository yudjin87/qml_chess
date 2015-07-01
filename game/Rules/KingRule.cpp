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
    BaseRule::DirectionFunc dirFuncs[] = {&Square::left, &Square::top, &Square::right, &Square::bottom,
                                         &Square::bottomLeft, &Square::topLeft, &Square::topRight, &Square::bottomRight};
    for (BaseRule::DirectionFunc dirFunc : dirFuncs)
    {
        Square* nextSquare = nextMovement(currentPosition, dirFunc);
        if (nextSquare != nullptr)
        {
            if (nextSquare->isEmpty())
            {
                result.push_back(Move::create(Move::Movement, *nextSquare));
            }
            else
            {
                result.push_back(Move::create((nextSquare->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *nextSquare));
            }
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
