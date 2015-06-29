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

#include "game/Piece.h"
#include "game/Chessboard.h"
#include "game/Rules/IMovementRule.h"
#include "game/Square.h"

namespace Chess
{

Piece::Piece(const PieceType type, const Color color, Chessboard *board, IMovementRule *rule, QObject *parent)
    : QObject(parent)
    , m_type(type)
    , m_color(color)
    , m_board(board)
    , m_movementRule(rule)
    , m_wasMoved(false)
{
    Q_ASSERT(board != nullptr && "Null pointer is not allowed!");
    Q_ASSERT(rule != nullptr && "Null pointer is not allowed!");

    m_movementRule->setParent(this);
}

Piece::~Piece()
{
}

QString Piece::toString() const
{
    return QString("%1 %2").arg(Chess::toString(m_type)).arg(atSquare()->toStr());
}

PieceType Piece::type() const
{
    return m_type;
}

Color Piece::color() const
{
    return m_color;
}

Chessboard *Piece::board()
{
    return m_board;
}

const Chessboard *Piece::board() const
{
    return m_board;
}

Square *Piece::atSquare()
{
    return m_board->findSquare(this);
}

QList<Square *> Piece::possibleMoves()
{
    const QList<Square *> moves = m_movementRule->findMoves(*this);
    return moves;
}

QList<Square *> Piece::possibleAttacks()
{
    return m_movementRule->findAttacks(*this);
}

const Square *Piece::atSquare() const
{
    return m_board->findSquare(this);
}

bool Piece::wasMoved() const
{
    return m_wasMoved;
}

void Piece::markAsMoved(bool moved)
{
    m_wasMoved = moved;
}

} // namespace Chess
