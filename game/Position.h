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

#ifndef POSITION_H
#define POSITION_H

#include "game/game_api.h"
#include "game/Color.h"
#include "game/File.h"
#include "game/Rank.h"

#include <QtCore/QObject>
#include <QtCore/QString>

namespace Chess
{

class GAME_API Position
{
public:
    Position(const int index);
    Position(const File file, const Rank rank);

    static Position fromString(const QString& string, bool *error);

    static Position A1() { return Position(File::A, Rank::R1); }
    static Position A2() { return Position(File::A, Rank::R2); }
    static Position A3() { return Position(File::A, Rank::R3); }
    static Position A4() { return Position(File::A, Rank::R4); }
    static Position A5() { return Position(File::A, Rank::R5); }
    static Position A6() { return Position(File::A, Rank::R6); }
    static Position A7() { return Position(File::A, Rank::R7); }
    static Position A8() { return Position(File::A, Rank::R8); }

    static Position B1() { return Position(File::B, Rank::R1); }
    static Position B2() { return Position(File::B, Rank::R2); }
    static Position B3() { return Position(File::B, Rank::R3); }
    static Position B4() { return Position(File::B, Rank::R4); }
    static Position B5() { return Position(File::B, Rank::R5); }
    static Position B6() { return Position(File::B, Rank::R6); }
    static Position B7() { return Position(File::B, Rank::R7); }
    static Position B8() { return Position(File::B, Rank::R8); }

    static Position C1() { return Position(File::C, Rank::R1); }
    static Position C2() { return Position(File::C, Rank::R2); }
    static Position C3() { return Position(File::C, Rank::R3); }
    static Position C4() { return Position(File::C, Rank::R4); }
    static Position C5() { return Position(File::C, Rank::R5); }
    static Position C6() { return Position(File::C, Rank::R6); }
    static Position C7() { return Position(File::C, Rank::R7); }
    static Position C8() { return Position(File::C, Rank::R8); }

    static Position D1() { return Position(File::D, Rank::R1); }
    static Position D2() { return Position(File::D, Rank::R2); }
    static Position D3() { return Position(File::D, Rank::R3); }
    static Position D4() { return Position(File::D, Rank::R4); }
    static Position D5() { return Position(File::D, Rank::R5); }
    static Position D6() { return Position(File::D, Rank::R6); }
    static Position D7() { return Position(File::D, Rank::R7); }
    static Position D8() { return Position(File::D, Rank::R8); }

    static Position E1() { return Position(File::E, Rank::R1); }
    static Position E2() { return Position(File::E, Rank::R2); }
    static Position E3() { return Position(File::E, Rank::R3); }
    static Position E4() { return Position(File::E, Rank::R4); }
    static Position E5() { return Position(File::E, Rank::R5); }
    static Position E6() { return Position(File::E, Rank::R6); }
    static Position E7() { return Position(File::E, Rank::R7); }
    static Position E8() { return Position(File::E, Rank::R8); }

    static Position F1() { return Position(File::F, Rank::R1); }
    static Position F2() { return Position(File::F, Rank::R2); }
    static Position F3() { return Position(File::F, Rank::R3); }
    static Position F4() { return Position(File::F, Rank::R4); }
    static Position F5() { return Position(File::F, Rank::R5); }
    static Position F6() { return Position(File::F, Rank::R6); }
    static Position F7() { return Position(File::F, Rank::R7); }
    static Position F8() { return Position(File::F, Rank::R8); }

    static Position G1() { return Position(File::G, Rank::R1); }
    static Position G2() { return Position(File::G, Rank::R2); }
    static Position G3() { return Position(File::G, Rank::R3); }
    static Position G4() { return Position(File::G, Rank::R4); }
    static Position G5() { return Position(File::G, Rank::R5); }
    static Position G6() { return Position(File::G, Rank::R6); }
    static Position G7() { return Position(File::G, Rank::R7); }
    static Position G8() { return Position(File::G, Rank::R8); }

    static Position H1() { return Position(File::H, Rank::R1); }
    static Position H2() { return Position(File::H, Rank::R2); }
    static Position H3() { return Position(File::H, Rank::R3); }
    static Position H4() { return Position(File::H, Rank::R4); }
    static Position H5() { return Position(File::H, Rank::R5); }
    static Position H6() { return Position(File::H, Rank::R6); }
    static Position H7() { return Position(File::H, Rank::R7); }
    static Position H8() { return Position(File::H, Rank::R8); }

    Position& operator++();
    Position operator++(int);

    File file() const;
    Rank rank() const;
    Color color() const;
    int index() const;

    QString toString() const;

private:
    File m_file;
    Rank m_rank;
};

GAME_API bool operator==(const Position& one, const Position& other);
GAME_API bool operator!=(const Position& one, const Position& other);
GAME_API bool operator<(const Position& one, const Position& other);
GAME_API bool operator<=(const Position& one, const Position& other);
GAME_API bool operator>(const Position& one, const Position& other);
GAME_API bool operator>=(const Position& one, const Position& other);

} // namespace Chess

#endif // POSITION_H
