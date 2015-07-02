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

#ifndef CHESSBOARDITEM_H
#define CHESSBOARDITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPixmap>
#include <QtCore/QList>

#include <memory>

namespace Chess
{
class Chessboard;
class Piece;
}

namespace UiQml
{

class PieceItem;

class ChessboardItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Chess::Chessboard* chessboard READ chessboard WRITE setChessboard NOTIFY chessboardChanged)

public:
    ChessboardItem(QQuickItem * parent = nullptr);

    void paint(QPainter * painter) override;

    Chess::Chessboard* chessboard();
    const Chess::Chessboard* chessboard() const;

public slots:
    void setChessboard(Chess::Chessboard *chessboard);

signals:
    void chessboardChanged(Chess::Chessboard* chessboard);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onWindowChanged(QQuickWindow * window);
    void onPieceAdded(Chess::Piece* piece);
    void onPieceRemoved(Chess::Piece* piece);
    void onWindowSizeDimentionChanged(int newDim);

private:
    static int mapIndex(const int index);
    PieceItem* createPiece();

    void updatePiecesSize();
    void updatePiece(const int index);
    int squareSize() const;

private:
    static const QColor LIGHT_DARK[2];
    Chess::Chessboard* m_chessChessboard;
    QList<PieceItem*> m_pieces;
    std::unique_ptr<QPixmap> m_buffer;


};

} // namespace UiQml

#endif // CHESSBOARDITEM_H
