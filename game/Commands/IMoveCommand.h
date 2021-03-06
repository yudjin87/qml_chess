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

#ifndef IMOVECOMMAND
#define IMOVECOMMAND

#include "game/game_api.h"
#include "game/Move.h"
#include <QtCore/QJsonObject>

#include <memory>

namespace Chess
{

class Chessboard;
class Piece;

class GAME_API IMoveCommand
{
public:
    typedef std::unique_ptr<IMoveCommand> UPtr;

public:
    IMoveCommand() = default;
    virtual ~IMoveCommand() = default;

    virtual bool redo(Chessboard& board) = 0;
    virtual bool undo(Chessboard& board) = 0;

    virtual Move::Type type() const = 0;
    virtual QString toString() const = 0;

    virtual QJsonObject write() const = 0;
    virtual bool load(const QJsonObject move) = 0;
};

} // namespace Chess

#endif // IMOVECOMMAND

