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

#ifndef PLAYER_H
#define PLAYER_H

#include "game/game_api.h"
#include "game/Color.h"

#include <QtCore/QObject>

namespace Chess
{

class Square;
class SquareList;
class ChessGame;

class GAME_API Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit Player(const Color color, ChessGame& game, QObject *parent = nullptr);

    Color color() const;
    QString name() const;

public slots:
    void setName(QString name);

    // TODO: problems with QQmlListProperty
    Chess::SquareList* selectPiece(Chess::Square* atSquare);

signals:
    void nameChanged(QString name);
    void availableMovementsChanged(Chess::SquareList* availableMovements);

private:
    const Color m_color;
    ChessGame& m_game;
    QString m_name;
    SquareList* m_possibleMoves;
};

} // namespace Chess

#endif // PLAYER_H
