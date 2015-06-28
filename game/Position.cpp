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

#include "game/Position.h"
#include "game/Constants.h"

#include <QtCore/QDebug>

namespace Chess
{

namespace
{
int compare(const Position &one, const Position &other);
}

Position::Position(const File file, const Rank rank)
    : m_file(file)
    , m_rank(rank)
{
}

Position Position::fromString(const QString &string, bool *error)
{
    if (string.size() != 2)
    {
        qWarning() << "Invalid position size" << string.size();
        if (error) *error = false;
        return Position::A1();
    }

    // TODO: use Qt enums for parsing...

    const QChar fileChar = string[0];
    const int file = fileChar.toLatin1() - 'A';
    if (file < 0 || static_cast<int>(File::H) < file)
    {
        qWarning() << "Invalid file" << string[0];
        if (error) *error = false;
        return Position::A1();
    }

    const QString rankLetter = string[1];

    bool ok = false;
    const int rank = rankLetter.toInt(&ok) - 1;
    if (!ok)
    {
        qWarning() << "Invalid rank" << rankLetter;
        if (error) *error = false;
        return Position::A1();
    }

    if (rank < 0 || static_cast<int>(Rank::R8) < rank)
    {
        qWarning() << "Invalid file" << string[0];
        if (error) *error = false;
        return Position::A1();
    }

    if (error) *error = true;
    return Position(static_cast<File>(file), static_cast<Rank>(rank));
}

Position Position::operator++(int)
{
    Position temp = *this;
    this->operator ++();
    return temp;
}

Position &Position::operator++()
{
    m_file = next(m_file);
    if (m_file == File::A)
    {
        m_rank = next(m_rank);
    }

    return *this;
}

File Position::file() const
{
    return m_file;
}

Rank Position::rank() const
{
    return m_rank;
}

Color Position::color() const
{
    const int rank = static_cast<int>(m_rank);
    const int file = static_cast<int>(m_file);
    const bool odd = ((file + rank) % 2) == 1;

    return odd ? Color::White : Color::Black;
}

int Position::index() const
{
    const int rank = static_cast<int>(m_rank);
    const int file = static_cast<int>(m_file);
    return ((rank * CHESS_SIZE) + file);
}

QString Position::toString() const
{
    return QString("%1%2").arg(Chess::toString(m_file)).arg(Chess::toString(m_rank));
}

bool operator==(const Position &one, const Position &other)
{
    return (one.file() == other.file()) && (one.rank() == other.rank());
}

bool operator!=(const Position &one, const Position &other)
{
    return !(one == other);
}

bool operator<(const Position &one, const Position &other)
{
    return (compare(one, other) < 0);
}

bool operator<=(const Position &one, const Position &other)
{
    return (compare(one, other) <= 0);
}

bool operator>(const Position &one, const Position &other)
{
    return (compare(one, other) > 0);
}

bool operator>=(const Position &one, const Position &other)
{
    return (compare(one, other) >= 0);
}

namespace
{
int compare(const Position &one, const Position &other)
{
    if (one.rank() < other.rank())
    {
        return -1;
    }
    else if (one.rank() > other.rank())
    {
        return 1;
    }

    if (one.file() < other.file())
    {
        return -1;
    }
    else if (one.file() > other.file())
    {
        return 1;
    }

    return 0;
}
}

// namespace

} // namespace Chess
