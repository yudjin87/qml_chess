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

#include "game/Rules/KnightRule.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"

#include <QtCore/QDebug>

namespace Chess
{

KnightRule::KnightRule(Chessboard &board, QObject* parent)
    : BaseRule(board, parent)
{
}

std::vector<Move::UPtr> KnightRule::findMovesSafe(Piece &forPiece) const
{
    std::vector<Move::UPtr> result;
    Square *currentPosition = forPiece.atSquare();
    if (Square* pos = leftLeftTop(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    if (Square* pos = leftTopTop(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    if (Square* pos = rightTopTop(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    if (Square* pos = rightRightTop(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    if (Square* pos = rightRightBot(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    if (Square* pos = rightBotBot(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    if (Square* pos = leftBotBot(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    if (Square* pos = leftLeftBot(currentPosition))
    {
        if (pos->isEmpty())
        {
            result.push_back(Move::create(Move::Movement, *pos));
        }
        else
        {
            result.push_back(Move::create((pos->piece()->color() == forPiece.color()) ? Move::Defend : Move::Attack, *pos));
        }
    }

    return result;
}

Square *KnightRule::leftLeftTop(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->left() == nullptr) return nullptr;
    return current->left()->topLeft();
}

Square *KnightRule::leftTopTop(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->top() == nullptr) return nullptr;
    return current->top()->topLeft();
}

Square *KnightRule::rightTopTop(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->top() == nullptr) return nullptr;
    return current->top()->topRight();
}

Square *KnightRule::rightRightTop(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->right() == nullptr) return nullptr;
    return current->right()->topRight();
}

Square *KnightRule::rightRightBot(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->right() == nullptr) return nullptr;
    return current->right()->bottomRight();
}

Square *KnightRule::rightBotBot(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->bottom() == nullptr) return nullptr;
    return current->bottom()->bottomRight();
}

Square *KnightRule::leftBotBot(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->bottom() == nullptr) return nullptr;
    return current->bottom()->bottomLeft();
}

Square *KnightRule::leftLeftBot(Square* current) const
{
    if (current == nullptr) return nullptr;
    if (current->left() == nullptr) return nullptr;
    return current->left()->bottomLeft();
}

} // namespace Chess
