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

#include "game/Commands/GameMovesRegistry.h"
#include "game/Commands/GameMovementsWriter.h"
#include "game/Commands/GameMovementsReader.h"

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QByteArray>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCore/QFile>

namespace Chess
{

GameMovesRegistry::GameMovesRegistry(Chessboard &board, QObject *parent)
    : QObject(parent)
    , m_board(board)
    , m_performedCmnds()
    , m_undoneCmnds()
{
}

void GameMovesRegistry::push(IMoveCommand::UPtr newMove)
{
    Q_ASSERT(newMove != nullptr && "Null pointer is not allowed");
    m_undoneCmnds.push_back(std::move(newMove));
    redo();
    emit countChanged(count());
}

void GameMovesRegistry::clear()
{
    m_performedCmnds.clear();
    m_undoneCmnds.clear();

    emit countChanged(count());
    emit canRedoChanged(canRedo());
    emit canUndoChanged(canUndo());
}

bool GameMovesRegistry::canRedo() const
{
    return !m_undoneCmnds.empty();
}

bool GameMovesRegistry::canUndo() const
{
    return !m_performedCmnds.empty();
}

int GameMovesRegistry::count() const
{
    return m_performedCmnds.size() + m_undoneCmnds.size();
}

void GameMovesRegistry::save(QString fileName)
{
    QFileInfo info(fileName);
    if (info.suffix().isEmpty() || info.suffix() != "chess")
    {
        info = fileName + ".chess";
    }

    qDebug() << "Saving to" << info.absoluteFilePath();

    QFile file(info.absoluteFilePath());

    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Can't open file" << info.absoluteFilePath() << "for writting";
        return;
    }

    QTextStream out(&file);
    GameMovementsWriter writer;
    QByteArray savedDoc = writer.write(m_performedCmnds);

    out << savedDoc;
}

void GameMovesRegistry::load(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Can't open file" << fileName << "for reading";
        return;
    }

    QByteArray savedDov = file.readAll();
    GameMovementsReader reader;
    bool ok = false;
    m_undoneCmnds = reader.read(savedDov, &ok);
    if (!ok)
    {
        return;
    }

    qDebug() << m_undoneCmnds.size() << "commands were read:";
    for (const IMoveCommand::UPtr& cmd : m_undoneCmnds)
    {
        qDebug() << cmd->toString();
    }

    emit canRedoChanged(canRedo());
    emit movesLoaded();
}

void GameMovesRegistry::redo()
{
    if (!canRedo())
    {
        return;
    }

    qDebug() << "Redo";

    IMoveCommand::UPtr cmd = std::move(m_undoneCmnds.back());
    m_undoneCmnds.pop_back();
    m_performedCmnds.push_back(std::move(cmd));

    if (!m_performedCmnds.back()->redo(m_board))
    {
        failExecution();
        return;
    }

    emit newMoveDone();
    emit canRedoChanged(canRedo());
    emit canUndoChanged(canUndo());
}

void GameMovesRegistry::undo()
{
    if (!canUndo())
    {
        return;
    }

    qDebug() << "Undo";

    IMoveCommand::UPtr cmd = std::move(m_performedCmnds.back());
    m_performedCmnds.pop_back();
    m_undoneCmnds.push_back(std::move(cmd));
    if (!m_undoneCmnds.back()->undo(m_board))
    {
        failExecution();
        return;
    }

    emit newMoveDone();

    emit canRedoChanged(canRedo());
    emit canUndoChanged(canUndo());
}

void GameMovesRegistry::failExecution()
{
    m_performedCmnds.clear();
    m_undoneCmnds.clear();

    emit canRedoChanged(canRedo());
    emit canUndoChanged(canUndo());
    emit executionFailed();
}

} // namespace Chess
