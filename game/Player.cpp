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

#include "game/Player.h"
#include "game/Piece.h"
#include "game/IGameMovesRegistry.h"
#include "game/Square.h"
#include "game/SquareList.h"
#include "game/MovementCommand.h"

#include <QtCore/QDebug>

namespace Chess
{

Player::Player(const Color color, IGameMovesRegistry &movesRegistry, QObject *parent)
    : QObject(parent)
    , m_color(color)
    , m_movesRegistry(movesRegistry)
    , m_name("Player " + Chess::toString(color))
    , m_selectedPiece(nullptr)
    , m_availableMovements(new SquareList(this))
{
}

Color Player::color() const
{
    return m_color;
}

QString Player::name() const
{
    return m_name;
}

Piece *Player::selectedPiece()
{
    return m_selectedPiece;
}

SquareList *Player::availableMovements()
{
    return m_availableMovements;
}

void Player::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

bool Player::selectPiece(Piece* piece)
{
    if (piece == nullptr)
    {
        setSelectedPiece(nullptr);
        m_availableMovements->clear();
        availableMovementsChanged(m_availableMovements);
        return false;
    }

    if (piece->color() != color())
    {
        setSelectedPiece(nullptr);
        m_availableMovements->clear();
        availableMovementsChanged(m_availableMovements);
        return false;
    }

    setSelectedPiece(piece);
    const QList<Square*> moves = piece->possibleMoves();
    m_availableMovements->reset(moves);
    availableMovementsChanged(m_availableMovements);
    return true;
}

void Player::moveTo(Square *square)
{
    Q_ASSERT(square != nullptr && "Logic error: Null pointer is not allowed");
    if (m_selectedPiece == nullptr)
    {
        qWarning() << "Piece wasn't selected - movement is aborted";
        return;
    }

    if (!m_availableMovements->contains(square))
    {
        qWarning() << "Trying to move to illegal position. Aborted";
        return;
    }

    MovementCommand::UPtr moveCmd = MovementCommand::create(*square, *m_selectedPiece);
    m_movesRegistry.commit(std::move(moveCmd));

    setSelectedPiece(nullptr);
    m_availableMovements->clear();
    availableMovementsChanged(m_availableMovements);
}

void Player::setSelectedPiece(Piece *selectedPiece)
{
    if (selectedPiece == m_selectedPiece)
    {
        return;
    }

    m_selectedPiece = selectedPiece;
    emit selectedPieceChanged(m_selectedPiece);
}


} // namespace Chess


