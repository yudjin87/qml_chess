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
#include "game/Move.h"
#include "game/AvailableMoves.h"
#include "game/Commands/GameMovesRegistry.h"
#include "game/Commands/AttackCommand.h"
#include "game/Commands/CastlingCommand.h"
#include "game/Commands/MovementCommand.h"

#include <QtCore/QDebug>

namespace Chess
{

Player::Player(const Color color, GameMovesRegistry &movesRegistry, QObject *parent)
    : QObject(parent)
    , m_color(color)
    , m_movesRegistry(movesRegistry)
    , m_name("Player " + Chess::toString(color))
    , m_selectedPiece(nullptr)
    , m_availableMovements(new AvailableMoves(this))
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

AvailableMoves *Player::availableMovements()
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
        qDebug() << "Player: nothing to select";
        setSelectedPiece(nullptr);

        // TODO: simplify
        m_availableMovements->clear();
        availableMovementsChanged(m_availableMovements);
        return false;
    }

    if (piece->color() != color())
    {
        qDebug() << "Player: wrong color";
        setSelectedPiece(nullptr);
        m_availableMovements->clear();
        availableMovementsChanged(m_availableMovements);
        return false;
    }

    qDebug() << "Player: piece " << piece->toString() << " was selected";

    setSelectedPiece(piece);
    m_availableMovements->clear();

    std::vector<Move::UPtr> moves = piece->possibleMoves();
    for (auto it = std::begin(moves); it != std::end(moves); ++it)
    {
        Move::UPtr move = std::move(*it);
        if (move->type() != Move::Defend)
            m_availableMovements->append(std::move(move));
    }

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

    Move* move = m_availableMovements->findMove(square);
    if (move == nullptr)
    {
        qWarning() << "Trying to move to illegal position. Aborted";
        return;
    }

    IMoveCommand::UPtr moveCmd;
    // TODO: factory?
    switch (move->type())
    {
    case Move::Movement:
        moveCmd = MovementCommand::create(square->position(), m_selectedPiece->atSquare()->position());
        break;
    case Move::Attack:
        moveCmd = AttackCommand::create(square->position(), m_selectedPiece->atSquare()->position());
        break;
    case Move::Defend:
        break;
    case Move::Castling:
        moveCmd = CastlingCommand::create(square->position(), m_selectedPiece->atSquare()->position());
        break;
    }

    if (moveCmd != nullptr)
    {
        m_movesRegistry.push(std::move(moveCmd));
    }

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


