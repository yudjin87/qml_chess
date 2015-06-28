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

#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Position.h"
#include "game/Piece.h"

#include <algorithm>

namespace Chess
{

Chessboard::Chessboard(QObject *parent)
    : QObject(parent)
    , m_squares()
    , m_piecesOnBoard()
{
    for (Position p = Position::A1(); p < Position::H8(); ++p)
    {
        m_squares.push_back(new Square(*this, p));
    }
    m_squares.push_back(new Square(*this, Position::H8()));
}

Square *Chessboard::squareAt(const Position &pos)
{
    return const_cast<Square*>(const_cast<const Chessboard*>(this)->squareAt(pos));
}

const Square *Chessboard::squareAt(const Position &pos) const
{
    const auto byPos = [&pos](const Square* s) { return s->position() == pos;};
    const auto it = std::find_if(std::begin(m_squares), std::end(m_squares), byPos);
    if (it == std::end(m_squares))
    {
        return nullptr;
    }

    return *it;
}

Square *Chessboard::squareByIdex(const int index)
{
    return const_cast<Square*>(const_cast<const Chessboard*>(this)->squareByIdex(index));
}

const Square *Chessboard::squareByIdex(const int index) const
{
    if (index < 0 || m_squares.size() <= index)
    {
        return nullptr;
    }

    return m_squares[index];
}

int Chessboard::size() const
{
    return m_squares.size();
}

void Chessboard::putPiece(const Position &pos, Piece *piece)
{
    Square* square = squareAt(pos);
    putPiece(square, piece);
}

Square *Chessboard::findSquare(const Piece *piece)
{
    return const_cast<Square*>(const_cast<const Chessboard*>(this)->findSquare(piece));
}

const Square *Chessboard::findSquare(const Piece *piece) const
{
    const auto byPiece = [&piece](const Square* s) { return s->piece() == piece;};
    const auto it = std::find_if(std::begin(m_squares), std::end(m_squares), byPiece);
    if (it == std::end(m_squares))
    {
        return nullptr;
    }

    return *it;
}

bool Chessboard::contains(const Square *square) const
{
    if (square == nullptr)
    {
        return false;
    }

    // m_squares.contains(square) doesn't work, since "'const' Square *"
    const auto it = std::find(std::begin(m_squares), std::end(m_squares), square);
    return it != std::end(m_squares);
}

void Chessboard::putPiece(Square *square, Piece *piece)
{
    Q_ASSERT(square != nullptr && "Null pointer is not allowed!");
    Q_ASSERT(piece != nullptr && "Null pointer is not allowed!");

    // TODO: something smarter, that asserts?
    Q_ASSERT(m_squares.contains(square) && "Runtime error - square doesn't belong to this board");
    Q_ASSERT(!m_piecesOnBoard.contains(piece) && "Runtime error - this piece has already been added");

    m_piecesOnBoard.push_back(piece);
    square->setPiece(*piece);
    emit pieceAdded(piece);
}

void Chessboard::removePiece(Piece *piece)
{
    Q_ASSERT(piece != nullptr && "Null pointer is not allowed!");

    // TODO: something smarter, that asserts?
    Q_ASSERT(m_piecesOnBoard.contains(piece) && "Runtime error - this piece wasn't added");

    m_piecesOnBoard.removeOne(piece);
    emit pieceRemoved(piece);
    piece->atSquare()->removePiece();
}

Piece *Chessboard::takePiece(Square *square)
{
    (void)square;
    return nullptr;
}

} // namespace Chess
