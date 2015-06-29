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

#include "game/BoardCreator.h"
#include "game/Chessboard.h"
#include "game/Position.h"
#include "game/Rules/PawnRule.h"
#include "game/Rules/KnightRule.h"
#include "game/Rules/BishopRule.h"
#include "game/Rules/RookRule.h"
#include "game/Rules/QueenRule.h"
#include "game/Rules/KingRule.h"

namespace Chess
{

BoardCreator::BoardCreator(Chessboard &board)
    : m_board(board)
{
}

std::vector<Piece::UPtr> BoardCreator::createDefault()
{
    std::vector<Piece::UPtr> addedPieces;
    {
        Piece* knight1 = new Piece(PieceType::Knight, Color::White, &m_board, new KnightRule(m_board));
        m_board.putPiece(Position::B1(), knight1);
        addedPieces.emplace_back(knight1);
        Piece* knight2 = new Piece(PieceType::Knight, Color::White, &m_board, new KnightRule(m_board));
        m_board.putPiece(Position::G1(), knight2);
        addedPieces.emplace_back(knight2);

        Piece* bishop1 = new Piece(PieceType::Bishop, Color::White, &m_board, new BishopRule(m_board));
        m_board.putPiece(Position::C1(), bishop1);
        addedPieces.emplace_back(bishop1);
        Piece* bishop2 = new Piece(PieceType::Bishop, Color::White, &m_board, new BishopRule(m_board));
        m_board.putPiece(Position::F1(), bishop2);
        addedPieces.emplace_back(bishop2);

        Piece* rook1 = new Piece(PieceType::Rook, Color::White, &m_board, new RookRule(m_board));
        m_board.putPiece(Position::A1(), rook1);
        addedPieces.emplace_back(rook1);
        Piece* rook2 = new Piece(PieceType::Rook, Color::White, &m_board, new RookRule(m_board));
        m_board.putPiece(Position::H1(), rook2);
        addedPieces.emplace_back(rook2);

        Piece* queen = new Piece(PieceType::Queen, Color::White, &m_board, new QueenRule(m_board));
        m_board.putPiece(Position::D1(), queen);
        addedPieces.emplace_back(queen);
        Piece* king = new Piece(PieceType::King, Color::White, &m_board, new KingRule(m_board));
        m_board.putPiece(Position::E1(), king);
        addedPieces.emplace_back(king);

        for (Position p = Position::A2(); p <= Position::H2(); ++p)
        {
            Piece* pawn = new Piece(PieceType::Pawn, Color::White, &m_board, new PawnRule(m_board));
            addedPieces.emplace_back(pawn);
            m_board.putPiece(p, pawn);
        }
    }

    {
        Piece* knight1 = new Piece(PieceType::Knight, Color::Black, &m_board, new KnightRule(m_board));
        m_board.putPiece(Position::B8(), knight1);
        addedPieces.emplace_back(knight1);
        Piece* knight2 = new Piece(PieceType::Knight, Color::Black, &m_board, new KnightRule(m_board));
        m_board.putPiece(Position::G8(), knight2);
        addedPieces.emplace_back(knight2);

        Piece* bishop1 = new Piece(PieceType::Bishop, Color::Black, &m_board, new BishopRule(m_board));
        m_board.putPiece(Position::C8(), bishop1);
        addedPieces.emplace_back(bishop1);
        Piece* bishop2 = new Piece(PieceType::Bishop, Color::Black, &m_board, new BishopRule(m_board));
        m_board.putPiece(Position::F8(), bishop2);
        addedPieces.emplace_back(bishop2);

        Piece* rook1 = new Piece(PieceType::Rook, Color::Black, &m_board, new RookRule(m_board));
        m_board.putPiece(Position::A8(), rook1);
        addedPieces.emplace_back(rook1);
        Piece* rook2 = new Piece(PieceType::Rook, Color::Black, &m_board, new RookRule(m_board));
        m_board.putPiece(Position::H8(), rook2);
        addedPieces.emplace_back(rook2);

        Piece* queen = new Piece(PieceType::Queen, Color::Black, &m_board, new QueenRule(m_board));
        m_board.putPiece(Position::D8(), queen);
        addedPieces.emplace_back(queen);
        Piece* king = new Piece(PieceType::King, Color::Black, &m_board, new KingRule(m_board));
        m_board.putPiece(Position::E8(), king);
        addedPieces.emplace_back(king);

        for (Position p = Position::A7(); p <= Position::H7(); ++p)
        {
            Piece* pawn = new Piece(PieceType::Pawn, Color::Black, &m_board, new PawnRule(m_board));
            addedPieces.emplace_back(pawn);
            m_board.putPiece(p, pawn);
        }
    }

    return addedPieces;
}

} // namespace Chess
