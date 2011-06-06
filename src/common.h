/*
 *  Copyright © 2011 Juan Roldan Ruiz <juan@shoden.es>
 *
 *  This file is part of wolken-capture.
 *
 *  wolken-capture is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  wolken-capture is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with wolken-capture.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_H
#define COMMON_H

// C
#include <stdio.h>
#include <stdlib.h>

// C++
#include <iostream>

// Qt
#include <QDateTime>
#include <QDir>
#include <QList>
#include <QHash>
#include <QHashIterator>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QVariant>

using namespace std;

typedef QHash<QString,QString> Params;
typedef QList<Params> Takes;

#endif // COMMON_H
