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

#ifndef GAMEMOVESREGISTRY_H
#define GAMEMOVESREGISTRY_H

#include "game/game_api.h"
#include "game/Commands/IMoveCommand.h"

#include <QtCore/QObject>
#include <QtCore/QUrl>

#include <vector>

namespace Chess
{

class Chessboard;

// QUndoStack with some changes ... and without dependency to QtGUI
class GAME_API GameMovesRegistry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool canRedo READ canRedo NOTIFY canRedoChanged)
    Q_PROPERTY(bool canUndo READ canUndo NOTIFY canUndoChanged)
public:
    explicit GameMovesRegistry(Chessboard& board, QObject *parent = nullptr);

    void push(IMoveCommand::UPtr newMove);
    void clear();

    bool canRedo() const;
    bool canUndo() const;

    int count() const;

public slots:
    void save(QString fileName);
    void load(QString fileName);
    void redo();
    void undo();

signals:
    void newMoveDone();
    void countChanged(int count);
    void movesLoaded();
    void canRedoChanged(bool canRedo);
    void canUndoChanged(bool canUndo);

private:
    Chessboard& m_board;
    std::vector<IMoveCommand::UPtr> m_performedCmnds;
    std::vector<IMoveCommand::UPtr> m_undoneCmnds;
};

} // namespace Chess

#endif // GAMEMOVESREGISTRY_H
