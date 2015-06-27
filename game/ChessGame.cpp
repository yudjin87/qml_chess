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

#include "game/ChessGame.h"
#include "game/Chessboard.h"
#include "game/Piece.h"
#include "game/Position.h"

#include <QtCore/QtAlgorithms>

namespace Chess
{

ChessGame::ChessGame(QObject *parent)
    : QObject(parent)
    , m_board(nullptr)
    , m_piecesOnBoard()
    , m_killedPieces()
{

}

ChessGame::~ChessGame()
{
    qDeleteAll(m_piecesOnBoard);
    qDeleteAll(m_killedPieces);
}

void ChessGame::createGame(Chessboard *onBoard)
{
    Q_ASSERT(onBoard != nullptr && "Null pointer is not allowed!");

    // TODO: clean up previ game
    m_board = onBoard;

    Piece* pawn = new Piece(PieceType::Pawn, Color::White, m_board);
    //m_piecesOnBoard.push_back(pawn);
    m_board->putPiece(Position::A2(), pawn);

    pawn = new Piece(PieceType::Pawn, Color::White, m_board);
    //m_piecesOnBoard.push_back(pawn);
    m_board->putPiece(Position::B2(), pawn);
}

} // namespace Chess

