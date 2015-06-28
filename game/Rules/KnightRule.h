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

#ifndef KNIGHTRULE_H
#define KNIGHTRULE_H

#include "game/Rules/IMovementRule.h"

namespace Chess
{

class Chessboard;

class GAME_API KnightRule : public IMovementRule
{
public:
    KnightRule(Chessboard& board, QObject* parent = nullptr);

    QList<Square*> findMoves(Piece& forPiece) const override;
    QList<Square*> findAttacks(Piece& forPiece) const override;

private:
    Square* leftLeftTop(Square* current) const;
    Square* leftTopTop(Square* current) const;
    Square* rightTopTop(Square* current) const;
    Square* rightRightTop(Square* current) const;
    Square* rightRightBot(Square* current) const;
    Square* rightBotBot(Square* current) const;
    Square* leftBotBot(Square* current) const;
    Square* leftLeftBot(Square* current) const;

private:
    Chessboard& m_board;
};

} // namespace Chess

#endif // KNIGHTRULE_H
