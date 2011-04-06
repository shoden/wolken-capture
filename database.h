#ifndef DATABASE_H
#define DATABASE_H

#include <common.h>

// Qt SQL
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class DataBase
{
public:
  DataBase();

  void getParams();
  Takes getTakes();
  void listTakes();

protected:
  void error(const QString &msg);

private:
  QString user;
  QString password;
  QString host;
  QString bbdd;
  QString paramsTable, takesTable;

  Params params;
  Takes takes;
};

#endif // DATABASE_H
