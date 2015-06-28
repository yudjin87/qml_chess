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

#ifndef PIECE_H
#define PIECE_H

#include "game/game_api.h"
#include "game/Color.h"
#include "game/PieceType.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>

namespace Chess
{

class IMovementRule;
class Chessboard;
class Square;
class SquareList;

class GAME_API Piece : public QObject
{
    Q_OBJECT
public:
    Piece(const PieceType type, const Color color, Chessboard* board, IMovementRule* rule, QObject *parent = nullptr);
    ~Piece();

    QString toString() const;

    PieceType type() const;
    Color color() const;

    Chessboard *board();
    const Chessboard *board() const;

    const Chess::Square* atSquare() const;

public slots:
    Chess::Square* atSquare();

    // TODO: problems with QQmlListProperty
    Chess::SquareList* possibleMoves();

private:
    const PieceType m_type;
    const Color m_color;
    Chessboard* m_board;
    SquareList* m_possibleMoves;
    IMovementRule* m_movementRule;
};

} // namespace Chess

#endif // PIECE_H
