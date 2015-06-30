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

#ifndef PAWNRULE_H
#define PAWNRULE_H

#include "game/Rules/BaseRule.h"
#include "game/Color.h"

namespace Chess
{

class Chessboard;

class GAME_API PawnRule : public BaseRule
{
public:
    PawnRule(Chessboard& board, QObject* parent = nullptr);

protected:
    std::vector<Move::UPtr> findMovesSafe(Piece& forPiece) const override;

    Square* nextMovement(const Color ownColor, Square* basePosition) const;
    Square* nextRightAttack(const Color ownColor, Square* basePosition) const;
    Square *nextLeftAttack(const Color ownColor, Square* basePosition) const;
};

} // namespace Chess

#endif // PAWNRULE_H
