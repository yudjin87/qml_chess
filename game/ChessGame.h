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

#include <QtCore/QObject>
#include <QtCore/QVector>

namespace Chess
{

class Chessboard;
class Piece;

class GAME_API ChessGame : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
public:
    explicit ChessGame(QObject *parent = nullptr);
    ~ChessGame();

    bool isRunning() const;

public slots:
    void start(Chess::Chessboard* onBoard);
    void stop();

signals:
    void isRunningChanged(bool isRunning);

private:
    void setIsRunning(bool isRunning);

private:
    Chessboard* m_board;
    QVector<Piece*> m_piecesOnBoard;
    QVector<Piece*> m_killedPieces;
    bool m_isRunning;
};

} // namespace Chess

#endif // CHESSGAME_H
