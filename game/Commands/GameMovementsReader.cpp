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

#include "game/Commands/GameMovementsReader.h"
#include "game/Commands/CommandFactory.h"

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

std::vector<IMoveCommand::UPtr> GameMovementsReader::read(const QByteArray &loadStream, bool* ok)
{
    if (ok) *ok = false;
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
        const Move::Type cmdType = static_cast<Move::Type>(turn.value("CmdType").toInt(-1));

        IMoveCommand::UPtr cmd = CommandFactory::create(cmdType);
        if (cmd == nullptr)
        {
            qCritical() << "Unknown command type" << cmdType;
            return {};
        }

        if (!loadCommand(turn, *cmd, i))
        {
            qCritical() << "Saved data corrupted";
            return {};
        }
        cmds.insert(cmds.begin(), std::move(cmd));
    }

    if (ok) *ok = true;
    qDebug() << "Reading completed";

    return cmds;
}

bool GameMovementsReader::loadCommand(const QJsonObject &turn, IMoveCommand &cmd, const int index)
{
    const int savedIndex = turn.value("Index").toInt();
    if (savedIndex != index)
    {
        qCritical() << "Saved data corrupted";
        return false;
    }

    const QJsonObject move = turn.value("Move").toObject();
    if (!cmd.load(move))
    {
        qCritical() << "Can't load command's data";
        return false;
    }

    return true;
}

} // namespace Chess
