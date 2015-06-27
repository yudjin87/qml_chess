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

#include "ui_qml/PieceItem.h"
#include "game/Piece.h"

#include <QtGui/QPainter>
#include <QtGui/QPainter>

namespace UiQml
{

PieceItem::PieceItem(QQuickItem * parent)
    : QQuickPaintedItem(parent)
    , m_chessPiece(nullptr)
    , m_pieceImg()
{
    setFlag(QQuickItem::ItemHasContents, true);
}

void PieceItem::paint(QPainter *painter)
{
    if (m_chessPiece == nullptr)
    {
        return;
    }

    painter->drawImage(boundingRect(), m_pieceImg);
}

Chess::Piece *PieceItem::piece()
{
    return m_chessPiece;
}

const Chess::Piece *PieceItem::piece() const
{
    return m_chessPiece;
}

void PieceItem::setPiece(Chess::Piece* piece)
{
    if (m_chessPiece == piece)
    {
        return;
    }

    m_chessPiece = piece;
    if (m_chessPiece == nullptr)
    {
        update();
        return;
    }

    const QString pieceType = Chess::toString(piece->type()).toLower();
    const QString pieceColor = Chess::toString(piece->color()).toLower();
    const QString path = QString(":/ui_imgs/images/%1_%2.svg").arg(pieceType).arg(pieceColor);
    if (!m_pieceImg.load(path))
    {
        qCritical() << "Error during loading image \"" << path << "\"";
        return;
    }

    emit pieceChanged(piece);
    update();
}

} // namespace UiQml
