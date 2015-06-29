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

#ifndef CASTLINGCOMMAND_H
#define CASTLINGCOMMAND_H

#include "game/Commands/BaseCommand.h"
#include "game/Position.h"

namespace Chess
{

class Square;

class GAME_API CastlingCommand : public BaseCommand
{
public:
    typedef std::unique_ptr<CastlingCommand> UPtr;
    static const char* NAME;

public:
    CastlingCommand();
    CastlingCommand(const Position& to, const Position& from);

    template<class... TArgs>
    static CastlingCommand::UPtr create(TArgs&&... args)
    {
        return CastlingCommand::UPtr(new CastlingCommand(std::forward<TArgs>(args)...));
    }

    bool redo(Chessboard& board) override;
    bool undo(Chessboard& board) override;

    QString toString() const override;
};

} // namespace Chess
#endif // CASTLINGCOMMAND_H
