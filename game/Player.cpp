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
#include "game/Square.h"
#include "game/SquareList.h"
#include "game/Commands/IGameMovesRegistry.h"
#include "game/Commands/AttackCommand.h"
#include "game/Commands/MovementCommand.h"

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
    , m_availableAttacks(new SquareList(this))
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

SquareList *Player::availableAttacks()
{
    return m_availableAttacks;
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
        qDebug() << "Player: nothing to select";
        setSelectedPiece(nullptr);
        m_availableMovements->clear();
        availableMovementsChanged(m_availableMovements);

        // TODO: simplify
        m_availableAttacks->clear();
        availableAttacksChanged(m_availableAttacks);

        return false;
    }

    if (piece->color() != color())
    {
        qDebug() << "Player: wrong color";
        setSelectedPiece(nullptr);
        m_availableMovements->clear();
        availableMovementsChanged(m_availableMovements);

        m_availableAttacks->clear();
        availableAttacksChanged(m_availableAttacks);
        return false;
    }

    qDebug() << "Player: piece " << piece->toString() << " was selected";

    setSelectedPiece(piece);
    const QList<Square*> moves = piece->possibleMoves();
    m_availableMovements->reset(moves);
    availableMovementsChanged(m_availableMovements);

    const QList<Square*> attacks = piece->possibleAttacks();
    m_availableAttacks->reset(attacks);
    availableAttacksChanged(m_availableAttacks);
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

    MovementCommand::UPtr moveCmd = MovementCommand::create(square->position(), m_selectedPiece->atSquare()->position());
    m_movesRegistry.commit(std::move(moveCmd));

    setSelectedPiece(nullptr);
    m_availableMovements->clear();
    availableMovementsChanged(m_availableMovements);

    m_availableAttacks->clear();
    availableAttacksChanged(m_availableAttacks);
}

void Player::attack(Square *square)
{
    Q_ASSERT(square != nullptr && "Logic error: Null pointer is not allowed");
    if (m_selectedPiece == nullptr)
    {
        qWarning() << "Piece wasn't selected - attack is aborted";
        return;
    }

    if (!m_availableAttacks->contains(square))
    {
        qWarning() << "Trying to attack illegal position. Aborted";
        return;
    }

    AttackCommand::UPtr moveCmd = AttackCommand::create(square->position(), m_selectedPiece->atSquare()->position());
    m_movesRegistry.commit(std::move(moveCmd));

    // TODO: simplfy....
    setSelectedPiece(nullptr);
    m_availableMovements->clear();
    availableMovementsChanged(m_availableMovements);

    m_availableAttacks->clear();
    availableAttacksChanged(m_availableAttacks);
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


