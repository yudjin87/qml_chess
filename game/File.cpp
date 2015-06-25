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

#include "game/File.h"

namespace Chess
{

QString toString(const Chess::File file)
{
    switch (file)
    {
    case File::A: return "A";
    case File::B: return "B";
    case File::C: return "C";
    case File::D: return "D";
    case File::E: return "E";
    case File::F: return "F";
    case File::G: return "G";
    case File::H: return "H";
    }

    return "INVALID File";
}

File next(const File current)
{
    switch (current)
    {
    case File::A: return File::B;
    case File::B: return File::C;
    case File::C: return File::D;
    case File::D: return File::E;
    case File::E: return File::F;
    case File::F: return File::G;
    case File::G: return File::H;
    case File::H: return File::A;
    }

    Q_ASSERT(false && "Illegal value");
    return File::A;
}

File prev(const File current)
{
    switch (current)
    {
    case File::A: return File::H;
    case File::B: return File::A;
    case File::C: return File::B;
    case File::D: return File::C;
    case File::E: return File::D;
    case File::F: return File::E;
    case File::G: return File::F;
    case File::H: return File::G;
    }

    Q_ASSERT(false && "Illegal value");
    return File::A;
}

} // namespace Chess
