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

#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "game/game_api.h"
#include "game/IGameMovesRegistry.h"
#include "game/GameMode.h"

#include <QtCore/QObject>
#include <QtCore/QVector>

#include <memory>
#include <vector>

namespace Chess
{

class Chessboard;
class Piece;
class Player;
class Square;

class GAME_API ChessGame : public QObject, private IGameMovesRegistry
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(Chess::Player* activePlayer READ activePlayer NOTIFY activePlayerChanged)
    Q_PROPERTY(Chess::Chessboard* board READ board NOTIFY boardChanged)
    Q_PROPERTY(Chess::GameMode mode READ mode NOTIFY modeChanged)
public:
    explicit ChessGame(QObject *parent = nullptr);
    ~ChessGame();

    bool isRunning() const;

    Player* activePlayer();

    Chessboard *board();
    const Chessboard *board() const;

    Chess::GameMode mode() const;

public slots:
    void start();
    void stop();
    void save(QString fileName);
    void load();

signals:
    void isRunningChanged(bool isRunning);
    void activePlayerChanged(Chess::Player* activePlayer);
    void boardChanged(Chess::Chessboard* board);

    void modeChanged(Chess::GameMode mode);

private:
    void commit(IMoveCommand::UPtr newMove) override;

    void setIsRunning(bool isRunning);
    void setActivePlayer(Player* activePlayer);
    void setMode(Chess::GameMode mode);
    Player* nextTurnPlayer();
    void nextTurn();

private:
    Chessboard* m_board;
    QVector<Piece*> m_piecesOnBoard;
    QVector<Piece*> m_killedPieces;
    bool m_isRunning;
    Chess::GameMode m_mode;
    std::unique_ptr<Player> m_playerWhite;
    std::unique_ptr<Player> m_playerBlack;
    Player* m_playerActive;
    std::vector<IMoveCommand::UPtr> m_performedCmnds;
};

} // namespace Chess

#endif // CHESSGAME_H
