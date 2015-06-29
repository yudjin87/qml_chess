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

#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "game/Commands/IMoveCommand.h"
#include "game/Position.h"

namespace Chess
{

class Piece;

class GAME_API BaseCommand : public IMoveCommand
{
public:
    QString name() const override;
    QString toString() const override;

    QJsonObject write() const override;
    bool load(const QJsonObject move) override;

    void setToSquare(const Position& toSquare);
    void setFromSquare(const Position& fromSquare);

    Position toSquare() const;
    Position fromSquare() const;

protected:
    BaseCommand(const QString &name);
    BaseCommand(const QString &name, const Position& toSquare, const Position& fromSquare);

    void markAsMoved(Piece& piece);
    void undoMarkingAsMoved(Piece& piece);

private:
    const QString m_name;
    Position m_to;
    Position m_from;
    bool m_wasMoved;
};

} // namespace Chess
#endif // BASECOMMAND_H
