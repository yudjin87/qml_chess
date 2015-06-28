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

#include "game/Square.h"
#include "game/Chessboard.h"
#include "game/Piece.h"

namespace Chess
{

Square::Square(Chessboard &parent, const Position &pos)
    : QObject(&parent)
    , m_board(parent)
    , m_position(pos)
    , m_piece(nullptr)
{
}

Square::Square(Chessboard &parent, const File file, const Rank rank)
    : Square(parent, Position(file, rank))
{
}

Piece *Square::piece()
{
    return m_piece;
}

const Piece *Square::piece() const
{
    return m_piece;
}

void Square::setPiece(Piece &piece)
{
    m_piece = &piece;
}

void Square::removePiece()
{
    m_piece = nullptr;
}

bool Square::isEmpty() const
{
    return (m_piece == nullptr);
}

QString Square::toStr() const
{
    return m_position.toString();
}

Position Square::position() const
{
    return m_position;
}

Square *Square::left(const int numberOfSquares)
{
    return const_cast<Square*>(const_cast<const Square*>(this)->left(numberOfSquares));
}

const Square *Square::left(const int numberOfSquares) const
{
    if (file() == File::A)
    {
        return nullptr;
    }

    const Position leftPos(prev(file()), rank());
    const Square *left = m_board.squareAt(leftPos);
    if (numberOfSquares == 1)
    {
        return left;
    }

    return left->left(numberOfSquares - 1);
}

Square *Square::topLeft()
{
    return const_cast<Square*>(const_cast<const Square*>(this)->topLeft());
}

const Square *Square::topLeft() const
{
    const Square *topSquare = top();
    if (topSquare == nullptr)
    {
        return nullptr;
    }

    const Square *topLeft = topSquare->left();
    return topLeft;
}

Square *Square::top(const int numberOfSquares)
{
    return const_cast<Square*>(const_cast<const Square*>(this)->top(numberOfSquares));
}

const Square *Square::top(const int numberOfSquares) const
{
    if (rank() == Rank::R8)
    {
        return nullptr;
    }

    const Position topPos(file(), next(rank()));
    const Square *top = m_board.squareAt(topPos);
    if (numberOfSquares == 1)
    {
        return top;
    }

    return top->top(numberOfSquares - 1);
}

Square *Square::topRight()
{
    return const_cast<Square*>(const_cast<const Square*>(this)->topRight());
}

const Square *Square::topRight() const
{
    const Square *topSquare = top();
    if (topSquare == nullptr)
    {
        return nullptr;
    }

    const Square *topRight = topSquare->right();
    return topRight;
}

Square *Square::right(const int numberOfSquares)
{
    return const_cast<Square*>(const_cast<const Square*>(this)->right(numberOfSquares));
}

const Square *Square::right(const int numberOfSquares) const
{
    if (file() == File::H)
    {
        return nullptr;
    }

    const Position rightPos(next(file()), rank());
    const Square *right = m_board.squareAt(rightPos);
    if (numberOfSquares == 1)
    {
        return right;
    }

    return right->right(numberOfSquares - 1);
}

Square *Square::bottomRight()
{
    return const_cast<Square*>(const_cast<const Square*>(this)->bottomRight());
}

const Square *Square::bottomRight() const
{
    const Square *bottomSquare = bottom();
    if (bottomSquare == nullptr)
    {
        return nullptr;
    }

    const Square *bottomRight = bottomSquare->right();
    return bottomRight;
}

Square *Square::bottom(const int numberOfSquares)
{
    return const_cast<Square*>(const_cast<const Square*>(this)->bottom(numberOfSquares));
}

const Square *Square::bottom(const int numberOfSquares) const
{
    if (rank() == Rank::R1)
    {
        return nullptr;
    }

    const Position bottomPos(file(), prev(rank()));
    const Square *bottom = m_board.squareAt(bottomPos);
    if (numberOfSquares == 1)
    {
        return bottom;
    }

    return bottom->bottom(numberOfSquares - 1);
}

Square *Square::bottomLeft()
{
    return const_cast<Square*>(const_cast<const Square*>(this)->bottomLeft());
}

const Square *Square::bottomLeft() const
{
    const Square *bottomSquare = bottom();
    if (bottomSquare == nullptr)
    {
        return nullptr;
    }

    const Square *bottomLeft = bottomSquare->left();
    return bottomLeft;
}

File Square::file() const
{
    return m_position.file();
}

Rank Square::rank() const
{
    return m_position.rank();
}

int Square::index() const
{
    return m_position.index();
}

Color Square::color() const
{
    return m_position.color();
}

} // namespace Chess
