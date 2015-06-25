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

#include "game/Rank.h"


namespace Chess
{

QString toString(const Rank rank)
{
    switch (rank)
    {
    case Rank::R1: return "1";
    case Rank::R2: return "2";
    case Rank::R3: return "3";
    case Rank::R4: return "4";
    case Rank::R5: return "5";
    case Rank::R6: return "6";
    case Rank::R7: return "7";
    case Rank::R8: return "8";
    }

    return "INVALID RANK";
}

Rank next(const Rank current)
{
    switch (current)
    {
    case Rank::R1: return Rank::R2;
    case Rank::R2: return Rank::R3;
    case Rank::R3: return Rank::R4;
    case Rank::R4: return Rank::R5;
    case Rank::R5: return Rank::R6;
    case Rank::R6: return Rank::R7;
    case Rank::R7: return Rank::R8;
    case Rank::R8: return Rank::R1;
    }

    Q_ASSERT(false && "Illegal value");
    return Rank::R1;
}

Rank prev(const Rank current)
{
    switch (current)
    {
    case Rank::R1: return Rank::R8;
    case Rank::R2: return Rank::R1;
    case Rank::R3: return Rank::R2;
    case Rank::R4: return Rank::R3;
    case Rank::R5: return Rank::R4;
    case Rank::R6: return Rank::R5;
    case Rank::R7: return Rank::R6;
    case Rank::R8: return Rank::R7;
    }

    Q_ASSERT(false && "Illegal value");
    return Rank::R1;
}

} // namespace Chess

