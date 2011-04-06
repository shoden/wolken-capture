#include "database.h"

DataBase::DataBase()
{
  if(!QSqlDatabase::isDriverAvailable("QMYSQL"))
    error("Driver Mysql no disponible.");

  host = "localhost";
  bbdd = "nubes";
  takesTable = "tomas";
  paramsTable = "parametros";
  user = "root";
  password = "jrr360";
}

void DataBase::error(const QString &msg)
{
  std::cerr << msg.toUtf8().data() << std::endl;
  exit(EXIT_FAILURE);
}

void DataBase::getParams()
{
  QSqlDatabase db;
   db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName(host);
   db.setDatabaseName(bbdd);
   db.setUserName(user);
   db.setPassword(password);

   if(!db.open())
       error("No se ha podido conectar a la base de datos.");

   QSqlQuery query(QString("SELECT id, en FROM %1;").arg(paramsTable), db);
   if( query.size() == -1 )
       error( "No se pudo conectar con la base de datos" );

   while (query.next()) {
     QString id = query.value(0).toString();
     QString en = query.value(1).toString();

     params.insert(id, en);
   }
/*
   QMapIterator<QString, QString> it(params);
   while (it.hasNext()) {
       it.next();
       cout << it.key().toUtf8().data() << ": " << it.value().toUtf8().data() << endl;
   }
*/
}

Takes DataBase::getTakes()
{
  QSqlDatabase db;
   db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName(host);
   db.setDatabaseName(bbdd);
   db.setUserName(user);
   db.setPassword(password);

   if(!db.open())
       error("No se ha podido conectar a la base de datos.");

   QSqlQuery query(QString("SELECT * FROM %1;").arg(takesTable), db);
   if( query.size() == -1 )
       error( "No se pudo conectar con la base de datos" );

   // Tomas
   while (query.next()) {
     // Comprobar que la toma está habilitada
     if( query.value(1).toInt() == 1 ){
       Params take;

       // ID y Habilitado
       take.insert( "id", query.value(0).toString() );

       // Parámetros
       QMapIterator<QString, QString> it(params);
       while (it.hasNext()) {
         it.next();
         int num = query.record().indexOf(it.key());
         QString p = query.value(num).toString();

         take.insert(it.value(), p);
       }

       // Añadir toma a la lista de tomas
       takes << take;
     }
   }

   // Devolver la lista de tomas habilitadas
   return takes;
}

void DataBase::listTakes()
{
  for (int i = 0; i < takes.size(); i++) {
    cout << "*** Toma" << i+1 << endl;

    QMapIterator<QString, QString> it(takes.at(i));
    while (it.hasNext()) {
        it.next();
        cout << it.key().toUtf8().data() << ": " << it.value().toUtf8().data() << " # ";
    }
    cout << endl;
  }
}
