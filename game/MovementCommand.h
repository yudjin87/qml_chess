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

#ifndef MOVEMENTCOMMAND_H
#define MOVEMENTCOMMAND_H

#include "game/IMoveCommand.h"
#include "game/Position.h"

namespace Chess
{

class GAME_API MovementCommand : public IMoveCommand
{
public:
    typedef std::unique_ptr<MovementCommand> UPtr;
    static const char* NAME;

public:
    MovementCommand();
    MovementCommand(const Position& to, const Position& from);

    template<class... TArgs>
    static MovementCommand::UPtr create(TArgs&&... args)
    {
        return MovementCommand::UPtr(new MovementCommand(std::forward<TArgs>(args)...));
    }

    void redo(Chessboard& board) override;
    void undo(Chessboard& board) override;

    QString name() const override;

    QJsonObject write() const override;
    bool load(const QJsonObject move) override;

    void setDestinationSquare(const Position& to);
    void setFromSquare(const Position& from);

private:
    Position m_to;
    Position m_from;
};

} // namespace Chess

#endif // MOVEMENTCOMMAND_H
