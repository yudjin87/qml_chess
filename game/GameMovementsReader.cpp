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
 * Public License along with this library; if not, read to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "game/GameMovementsReader.h"
#include "game/AttackCommand.h"
#include "game/MovementCommand.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QDebug>

namespace Chess
{

GameMovementsReader::GameMovementsReader()
{
}

std::vector<IMoveCommand::UPtr> GameMovementsReader::read(const QByteArray &loadStream)
{
    std::vector<IMoveCommand::UPtr> cmds;

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(loadStream, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qCritical() << error.errorString();
        return cmds;
    }

    const QJsonObject root = document.object();
    const QJsonArray turnsJson = root.value("Movements").toArray();

    for (int i = 0; i < turnsJson.count(); ++i)
    {
        const QJsonObject turn = turnsJson.at(i).toObject();
        const QString cmdName = turn.value("CmdType").toString();

        // TODO: do something with it (Visitor?)
        if (cmdName == MovementCommand::NAME)
        {
            const int index = turn.value("Index").toInt();
            if (index != i)
            {
                qCritical() << "Saved data corrupted";
                return {};
            }

            const QJsonObject move = turn.value("Move").toObject();
            MovementCommand::UPtr cmd(new MovementCommand());
            if (!cmd->load(move))
            {
                qCritical() << "Can't load command's data";
                return {};
            }

            cmds.push_back(std::move(cmd));
        }
        else if (cmdName == AttackCommand::NAME)
        {
            const int index = turn.value("Index").toInt();
            if (index != i)
            {
                qCritical() << "Saved data corrupted";
                return {};
            }

            const QJsonObject move = turn.value("Move").toObject();
            AttackCommand::UPtr cmd(new AttackCommand());
            if (!cmd->load(move))
            {
                qCritical() << "Can't load command's data";
                return {};
            }

            cmds.push_back(std::move(cmd));
        }
        else
        {
            qCritical() << "Unknown command type" << cmdName;
        }

    }

    qDebug() << "Reading completed";

    return cmds;
}

} // namespace Chess
