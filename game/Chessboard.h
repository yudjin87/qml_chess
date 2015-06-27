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

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "game/game_api.h"
#include "game/File.h"
#include "game/Constants.h"
#include "game/Rank.h"

#include <QtCore/QObject>
#include <QtCore/QVector>

namespace Chess
{

class Piece;
class Position;
class Square;

class GAME_API Chessboard : public QObject
{
    Q_OBJECT

public:
    explicit Chessboard(QObject *parent = nullptr);

    const Square* squareAt(const Position& pos) const;
    const Square* squareByIdex(const int index) const;
    void putPiece(const Position& pos, Piece* piece);

    Square* findSquare(const Piece* piece);
    const Square* findSquare(const Piece* piece) const;

public slots:
    Chess::Square* squareAt(const Position& pos);
    Chess::Square* squareByIdex(const int index);

    int size() const;

    void putPiece(Square* square, Piece* piece);
    Chess::Piece* takePiece(Square* square);

signals:
    void pieceAdded(Chess::Piece* piece);
    void pieceRemoved(Piece* piece);

private:
    QVector<Square*> m_squares;
    QVector<Piece*> m_piecesOnBoard;
};

} // namespace Chess

#endif // CHESSBOARD_H
