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

#include "game/ChessGame.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Position.h"
#include "game/Player.h"

#include "game/Commands/GameMovesRegistry.h"
#include "game/BoardCreator.h"

#include <QtCore/QtAlgorithms>
#include <QtCore/QDebug>

namespace Chess
{

ChessGame::ChessGame(QObject *parent)
    : QObject(parent)
    , m_board(new Chessboard(this))
    , m_movesRegistry(new GameMovesRegistry(*m_board, this))
    , m_piecesOnBoard()
    , m_isRunning(false)
    , m_mode(GameMode::HumanVsHuman)
    , m_playerWhite(nullptr)
    , m_playerBlack(nullptr)
    , m_playerActive(nullptr)
{
    connect(m_movesRegistry, &GameMovesRegistry::newMoveDone, this, &ChessGame::nextTurn);
    connect(m_movesRegistry, &GameMovesRegistry::movesLoaded, this, &ChessGame::onMovesLoaded);
}

ChessGame::~ChessGame()
{
    Q_ASSERT(!isRunning() && "Logic error: game wasn't stopped");
    // TODO: stop() inside d.tor is RAII but looks unsafe - client should stop it explicitly
}

bool ChessGame::isRunning() const
{
    return m_isRunning;
}

Player *ChessGame::activePlayer()
{
    return m_playerActive;
}

Chessboard *ChessGame::board()
{
    return m_board;
}

const Chessboard *ChessGame::board() const
{
    return m_board;
}

GameMode ChessGame::mode() const
{
    return m_mode;
}

GameMovesRegistry *ChessGame::movesRegistry()
{
    return m_movesRegistry;
}

void ChessGame::start()
{
    stop();
    setMode(GameMode::HumanVsHuman);

    qDebug() << "Game: Starting, mode" << Chess::toString(m_mode);

    prepareGame();

    setIsRunning(true);
}

void ChessGame::stop()
{
    qDebug() << "Game: Stopping";
    clear();

    setIsRunning(false);
}

void ChessGame::save(QString fileName)
{
    m_movesRegistry->save(fileName);
}

void ChessGame::load(QString fileName)
{
    clear();
    m_movesRegistry->load(fileName);
}

void ChessGame::load(const QUrl &fileName)
{
    return load(fileName.toLocalFile());
}

void ChessGame::onMovesLoaded()
{
    setMode(GameMode::Replay);
    qDebug() << "Game: Starting, mode" << Chess::toString(m_mode);
    prepareGame();
}

void ChessGame::setMode(GameMode mode)
{
    if (m_mode == mode)
        return;

    m_mode = mode;
    emit modeChanged(mode);
}

void ChessGame::setIsRunning(bool isRunning)
{
    if (m_isRunning == isRunning)
    {
        return;
    }

    m_isRunning = isRunning;
    emit isRunningChanged(m_isRunning);
}

void ChessGame::setActivePlayer(Player *activePlayer)
{
    if (m_playerActive == activePlayer)
    {
        return;
    }

    m_playerActive = activePlayer;
    emit activePlayerChanged(activePlayer);
}

Player *ChessGame::nextTurnPlayer()
{
    return (m_playerActive->color() == Color::White) ? m_playerBlack.get() : m_playerWhite.get();
}

void ChessGame::nextTurn()
{
    Player *nextPlayer = nextTurnPlayer();
    qDebug() << "Game: Next turn: " << toString(nextPlayer->color());
    setActivePlayer(nextPlayer);
}

void ChessGame::prepareGame()
{
    m_playerWhite.reset(new Player(Color::White, *m_movesRegistry));
    m_playerBlack.reset(new Player(Color::Black, *m_movesRegistry));
    setActivePlayer(m_playerWhite.get());

    BoardCreator creator(*m_board);
    Q_ASSERT(m_piecesOnBoard.empty() && "Logic error: clean before re-creating");
    m_piecesOnBoard = creator.createDefault();
}

void ChessGame::clear()
{
    qDebug() << "Game: Clearing";
    m_movesRegistry->clear();

    for (const Piece::UPtr& p : m_piecesOnBoard)
    {
        m_board->removePiece(p.get());
    }

    m_piecesOnBoard.clear();

    m_playerWhite.reset();
    m_playerBlack.reset();
    setActivePlayer(nullptr);
}

} // namespace Chess

