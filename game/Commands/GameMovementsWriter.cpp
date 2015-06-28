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

#include "game/Commands/GameMovementsWriter.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

namespace Chess
{

GameMovementsWriter::GameMovementsWriter()
{
}

QByteArray GameMovementsWriter::write(const std::vector<IMoveCommand::UPtr> &performedCmnds)
{
    QJsonObject root;

    QJsonArray turnsJson;

    for (size_t i = 0; i < performedCmnds.size(); ++i)
    {
        const IMoveCommand::UPtr& cmd = performedCmnds[i];
        QJsonObject jsonCmd;
        jsonCmd.insert("CmdType", cmd->name());
        jsonCmd.insert("Index", static_cast<int>(i));

        QJsonObject move = cmd->write();
        jsonCmd.insert("Move", move);
        turnsJson.append(jsonCmd);
    }

    root.insert("Movements", turnsJson);

    QJsonDocument document;
    document.setObject(root);

    return document.toJson(QJsonDocument::Indented);
}

} // namespace Chess
