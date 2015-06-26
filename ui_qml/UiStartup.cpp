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
#include "ui_qml/ChessboardPresenter.h"

#include "game/Chessboard.h"
#include "game/Square.h"
#include "game/Piece.h"

#include <QtCore/QDebug>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/qqml.h>

namespace UiQml
{

UiStartup::UiStartup(QObject *parent)
    : QObject(parent)
{
    // TODO: move to static function
    // TODO: qmlRegisterUncreatableType'
    qmlRegisterUncreatableType<ChessboardPresenter>("ChessUi", 1, 0, "ChessboardPresenter", "Use 'chessBoard' object");
    qmlRegisterType<UiQml::PieceItem>("ChessUi", 1, 0, "PieceItem");

    qRegisterMetaType<Chess::Square*>("Chess::Square");
    qRegisterMetaType<Chess::Color>("Chess::Color");
    //qmlRegisterType<Chess::Piece>("Chess", 1, 0, "Piece");

}

bool UiStartup::showQmlWindow()
{
    // TODO: clean me up
    QQmlApplicationEngine *engine = new QQmlApplicationEngine(this);
    QQmlContext *qmlcontext = engine->rootContext();
    if (qmlcontext == nullptr)
    {
        qWarning() << "Cannot get QML context";
        return false;
    }

    Chess::Chessboard* board = new Chess::Chessboard(this);
    ChessboardPresenter* boardPresenter = new ChessboardPresenter(board, this);
    qmlcontext->setContextProperty("chessBoard", boardPresenter);

    engine->load(QUrl(QStringLiteral("qrc:/ui_qml/qml/main.qml")));

    return true;
}

} // namespace UiQml

