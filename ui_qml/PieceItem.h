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

#ifndef PIECEITEM_H
#define PIECEITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QtGui/QImage>

namespace Chess
{
class Piece;
}

namespace UiQml
{

class PieceItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Chess::Piece* piece READ piece WRITE setPiece NOTIFY pieceChanged)

public:
    PieceItem(QQuickItem * parent = nullptr);

    void paint(QPainter * painter);

    Chess::Piece* piece();
    const Chess::Piece* piece() const;

public slots:
    void setPiece(Chess::Piece *piece);

signals:
    void pieceChanged(Chess::Piece* piece);

private:
    Chess::Piece* m_chessPiece;
    QImage m_pieceImg;
};

} // namespace UiQml

#endif // PIECEITEM_H
