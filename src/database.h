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

#ifndef DATABASE_H
#define DATABASE_H

#include "common.h"

// Qt SQL
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class DataBase
{
public:
  DataBase();

  QStringList getParams();
  Takes getTakes();
  void listTakes();
  void log(const QString &);
  Params getROI();

protected:
  void error(const QString &msg);

private:
  QString user;
  QString password;
  QString host;
  QString bbdd;
  QString paramsTable;
  QString takesTable;
  QString logTable;
  QString roiTable;
  QSqlDatabase db;

  Params params;
  Takes takes;
};

#endif // DATABASE_H
