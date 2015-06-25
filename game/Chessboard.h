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

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "game/game_api.h"
#include "game/File.h"
#include "game/Rank.h"

#include <QtCore/QObject>
#include <QtCore/QVector>

namespace Chess
{

class Position;
class Square;

class GAME_API Chessboard : public QObject
{
    Q_OBJECT
public:
    const int CHESS_SIZE = 8;

public:
    explicit Chessboard(QObject *parent = nullptr);

    Square* squareAt(const Position& pos);
    const Square* squareAt(const Position& pos) const;

private:
    QVector<Square*> m_squares;
};

} // namespace Chess

#endif // CHESSBOARD_H
