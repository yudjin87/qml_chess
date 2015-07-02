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

#include "ui_qml/UiStartup.h"
#include "ui_qml/PieceItem.h"
#include "ui_qml/ChessboardItem.h"

#include "game/AvailableMoves.h"
#include "game/Chessboard.h"
#include "game/ChessGame.h"
#include "game/Move.h"
#include "game/Piece.h"
#include "game/Player.h"
#include "game/Square.h"
#include "game/Commands/GameMovesRegistry.h"

#include <QtCore/QDebug>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/qqml.h>

namespace UiQml
{
namespace
{
bool registerTypes();
}

UiStartup::UiStartup(QObject *parent)
    : QObject(parent)
{
    static const bool oneTimeRegistering = registerTypes();
    (void) oneTimeRegistering;
}

bool UiStartup::showQmlWindow()
{
    QQmlApplicationEngine *engine = new QQmlApplicationEngine(this);
    QQmlContext *qmlcontext = engine->rootContext();
    if (qmlcontext == nullptr)
    {
        qCritical() << "Cannot get QML context";
        return false;
    }

    Chess::ChessGame* game = new Chess::ChessGame(this);
    qmlcontext->setContextProperty("game", game);

    engine->load(QUrl(QStringLiteral("qrc:/ui_qml/qml/main.qml")));

    return true;
}

namespace
{
bool registerTypes()
{
    qmlRegisterUncreatableType<Chess::ChessGame>("Chess", 1, 0, "ChessGame", "Use 'game' object");
    qmlRegisterUncreatableType<Chess::Chessboard>("Chess", 1, 0, "Chessboard", "Get it from 'game' object");
    qmlRegisterUncreatableType<Chess::Piece>("Chess", 1, 0, "Piece", "Get it from 'chessBoard' object");
    qmlRegisterUncreatableType<Chess::Player>("Chess", 1, 0, "Player", "Get it from 'game' object");
    qmlRegisterUncreatableType<Chess::GameMovesRegistry>("Chess", 1, 0, "GameMovesRegistry", "Get it from 'game' object");
    qmlRegisterUncreatableType<Chess::Square>("Chess", 1, 0, "Square", "Get it from 'chessBoard' object");
    qmlRegisterUncreatableType<Chess::Move>("Chess", 1, 0, "Move", "Get it from 'chessBoard' object");
    qmlRegisterUncreatableType<Chess::AvailableMoves>("Chess", 1, 0, "AvailableMoves", "Get it from 'Piece' object");

    qRegisterMetaType<Chess::GameMovesRegistry*>("Chess::GameMovesRegistry");
    qRegisterMetaType<Chess::Piece*>("Chess::Piece");
    qRegisterMetaType<Chess::Square*>("Chess::Square");
    qRegisterMetaType<Chess::Move*>("Chess::Move");
    qRegisterMetaType<Chess::AvailableMoves*>("Chess::AvailableMoves");
    qRegisterMetaType<Chess::Color>("Chess::Color");
    qRegisterMetaType<Chess::GameMode>("Chess::GameMode");

    qmlRegisterType<UiQml::PieceItem>("ChessUi", 1, 0, "PieceItem");
    qmlRegisterType<UiQml::ChessboardItem>("ChessUi", 1, 0, "ChessboardItem");

    return true;
}

}


} // namespace UiQml

