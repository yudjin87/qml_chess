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

#include "ui_qml/ChessboardItem.h"
#include "ui_qml/PieceItem.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Square.h"
#include "game/Position.h"

#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <QtGui/QMouseEvent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QDebug>
#include <QtCore/QThread>

#include <algorithm>

namespace UiQml
{

const QColor ChessboardItem::LIGHT_DARK[2]{QColor("#FFCE9E"), QColor("#D18B47")};

ChessboardItem::ChessboardItem(QQuickItem * parent)
    : QQuickPaintedItem(parent)
    , m_chessChessboard(nullptr)
    , m_pieces()
    , m_buffer(new QPixmap(this->width(), this->height()))
{
    qDebug() << "ChessboardItem:" << QThread::currentThread()->objectName() << QThread::currentThread();
    setFlag(QQuickItem::ItemHasContents, true);
    connect(this, &QQuickItem::windowChanged, this, &ChessboardItem::onWindowChanged);

    std::generate_n(std::back_inserter(m_pieces), 64, [this](){ return createPiece(); });
    updatePiecesSize();
    setAcceptedMouseButtons(Qt::LeftButton);
}

void ChessboardItem::paint(QPainter *painter)
{
    qDebug() << "paint:" << QThread::currentThread()->objectName() << QThread::currentThread();

    const int size = squareSize();

    //painter->save();

    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 8; ++y)
        {
            const int colorIndex = (x + y) % 2;
            painter->setBrush(QBrush(LIGHT_DARK[colorIndex]));
            painter->drawRect(size * x, size * y, size, size);
        }
    }

    for (PieceItem* item : m_pieces)
    {
        item->paint(painter);
    }

   // painter->restore();
}

Chess::Chessboard *ChessboardItem::chessboard()
{
    return m_chessChessboard;
}

const Chess::Chessboard *ChessboardItem::chessboard() const
{
    return m_chessChessboard;
}

void ChessboardItem::setChessboard(Chess::Chessboard* chessboard)
{
    if (m_chessChessboard == chessboard)
    {
        return;
    }

    if (m_chessChessboard != nullptr)
    {
        disconnect(m_chessChessboard);
    }

    m_chessChessboard = chessboard;
    if (m_chessChessboard != nullptr)
    {
        connect(m_chessChessboard, &Chess::Chessboard::pieceAdded, this, &ChessboardItem::onPieceAdded);
        connect(m_chessChessboard, &Chess::Chessboard::pieceRemoved, this, &ChessboardItem::onPieceRemoved);
    }

    // fill PieceItems
    //update();
}

void ChessboardItem::mousePressEvent(QMouseEvent *event)
{
    //QQuickPaintedItem::mouseReleaseEvent(event);
    //if (event->button() != Qt::LeftButton)
    {
      //  return;
    }

    qDebug() << "Clicked " << event->pos();
}

void ChessboardItem::onWindowChanged(QQuickWindow *window)
{
    if (window != nullptr)
    {
        connect(window, &QQuickWindow::widthChanged, this, &ChessboardItem::onWindowSizeDimentionChanged);
        connect(window, &QQuickWindow::heightChanged, this, &ChessboardItem::onWindowSizeDimentionChanged);
    }
}

void ChessboardItem::onPieceAdded(Chess::Piece *piece)
{
    if (piece == nullptr)
    {
        return;
    }

    const int index = piece->atSquare()->index();
    if (index < 0 || m_pieces.size() < index)
    {
        qCritical() << "ChessboardItem::onPieceAdded: Invalid index" << index;
        return;
    }
    updatePiece(index);
    m_pieces[index]->setPiece(piece);
}

void ChessboardItem::onPieceRemoved(Chess::Piece *piece)
{
    if (piece == nullptr)
    {
        return;
    }

    const int index = piece->atSquare()->index();
    if (index < 0 || m_pieces.size() < index)
    {
        qCritical() << "ChessboardItem::onPieceRemoved: Invalid index" << index;
        return;
    }
    m_pieces[index]->setPiece(nullptr);
}

void ChessboardItem::onWindowSizeDimentionChanged(int)
{
    m_buffer.reset(new QPixmap(width(), height()));
    updatePiecesSize();
    //update();
}

int ChessboardItem::mapIndex(const int index)
{
    const int mod8 = index % 8;
    const int base = index / 8;
    return 64 - ((base + 1)* 8) + mod8;
}

void ChessboardItem::updatePiecesSize()
{
    for (int index = 0; index < m_pieces.size(); ++index)
    {
        updatePiece(index);
    }
}

void ChessboardItem::updatePiece(const int index)
{
    PieceItem* item  = m_pieces[index];
    item->setSize(QSize(squareSize(), squareSize()));

    const Chess::Position pos(index);
    const int top = (7 - static_cast<int>(pos.rank()));
    const int left = static_cast<int>(pos.file());
    item->setPosition(QPoint(left * squareSize(), top * squareSize()));
}

int ChessboardItem::squareSize() const
{
    const qreal dimension = std::min(contentsBoundingRect().width(), contentsBoundingRect().height());
    const int size = dimension / 8;
    return size;
}

PieceItem *ChessboardItem::createPiece()
{
    PieceItem* piece = new PieceItem(this);
    return piece;
}

} // namespace UiQml
