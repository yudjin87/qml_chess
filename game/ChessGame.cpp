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

    // TODO: builder?
    {
        Piece* rook1 = new Piece(PieceType::Rook, Color::White, m_board);
        m_board->putPiece(Position::A1(), rook1);
        Piece* rook2 = new Piece(PieceType::Rook, Color::White, m_board);
        m_board->putPiece(Position::H1(), rook2);

        Piece* knight1 = new Piece(PieceType::Knight, Color::White, m_board);
        m_board->putPiece(Position::B1(), knight1);
        Piece* knight2 = new Piece(PieceType::Knight, Color::White, m_board);
        m_board->putPiece(Position::G1(), knight2);

        Piece* bishop1 = new Piece(PieceType::Bishop, Color::White, m_board);
        m_board->putPiece(Position::C1(), bishop1);
        Piece* bishop2 = new Piece(PieceType::Bishop, Color::White, m_board);
        m_board->putPiece(Position::F1(), bishop2);

        Piece* queen = new Piece(PieceType::Queen, Color::White, m_board);
        m_board->putPiece(Position::D1(), queen);
        Piece* king = new Piece(PieceType::King, Color::White, m_board);
        m_board->putPiece(Position::E1(), king);

        for (Position p = Position::A2(); p <= Position::H2(); ++p)
        {
            Piece* pawn = new Piece(PieceType::Pawn, Color::White, m_board);
            //m_piecesOnBoard.push_back(pawn);
            m_board->putPiece(p, pawn);
        }
    }

    {
        Piece* rook1 = new Piece(PieceType::Rook, Color::Black, m_board);
        m_board->putPiece(Position::A8(), rook1);
        Piece* rook2 = new Piece(PieceType::Rook, Color::Black, m_board);
        m_board->putPiece(Position::H8(), rook2);

        Piece* knight1 = new Piece(PieceType::Knight, Color::Black, m_board);
        m_board->putPiece(Position::B8(), knight1);
        Piece* knight2 = new Piece(PieceType::Knight, Color::Black, m_board);
        m_board->putPiece(Position::G8(), knight2);

        Piece* bishop1 = new Piece(PieceType::Bishop, Color::Black, m_board);
        m_board->putPiece(Position::C8(), bishop1);
        Piece* bishop2 = new Piece(PieceType::Bishop, Color::Black, m_board);
        m_board->putPiece(Position::F8(), bishop2);

        Piece* queen = new Piece(PieceType::Queen, Color::Black, m_board);
        m_board->putPiece(Position::D8(), queen);
        Piece* king = new Piece(PieceType::King, Color::Black, m_board);
        m_board->putPiece(Position::E8(), king);

        for (Position p = Position::A7(); p <= Position::H7(); ++p)
        {
            Piece* pawn = new Piece(PieceType::Pawn, Color::Black, m_board);
            //m_piecesOnBoard.push_back(pawn);
            m_board->putPiece(p, pawn);
        }
    }
}

} // namespace Chess

