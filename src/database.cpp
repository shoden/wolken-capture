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

#include "database.h"

DataBase::DataBase()
{
  if(!QSqlDatabase::isDriverAvailable("QMYSQL"))
    error("Driver Mysql no disponible.");

  // Archivo de configuración
  QSettings settings(QSettings::SystemScope, "wolken", "wolken");
  settings.beginGroup( "Database" );
  host = settings.value( "host", "" ).toString();
  bbdd = settings.value( "bbdd", "" ).toString();
  takesTable = settings.value( "takesTable", "" ).toString();
  paramsTable = settings.value( "paramsTable", "" ).toString();
  roiTable = settings.value( "roiTable", "" ).toString();
  logTable = settings.value( "logTable", "" ).toString();
  user = settings.value( "user", "" ).toString();
  password = settings.value( "password", "" ).toString();
  settings.endGroup();

  db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName(host);
  db.setDatabaseName(bbdd);
  db.setUserName(user);
  db.setPassword(password);

  if(!db.open())
      error("No se ha podido conectar a la base de datos.");
}

void DataBase::error(const QString &msg)
{
  cerr << msg.toUtf8().data() << endl;
  exit(EXIT_FAILURE);
}

QStringList DataBase::getParams()
{
   QSqlQuery query(QString("SELECT id, en FROM %1;").arg(
                   paramsTable), db);
   if(query.size() == -1)
       error( "No se pudo conectar con la base de datos" );

   QStringList plist;

   while(query.next()){
     QString id = query.value(0).toString();
     QString en = query.value(1).toString();

     plist << en << id;
     params.insert(id, en);
   }

   return plist;
}

Takes DataBase::getTakes()
{
   QSqlQuery query(QString("SELECT * FROM %1;").arg(takesTable), db);
   if(query.size() == -1)
       error( "No se pudo conectar con la base de datos" );

   // Tomas
   while(query.next()){
     // Comprobar que la toma está habilitada
     if(query.value(1).toInt() == 1){
       Params take;

       // ID y Habilitado
       take.insert( "id", query.value(0).toString() );

       // Parámetros
       QHashIterator<QString, QString> it(params);
       while(it.hasNext()){
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

Params DataBase::getROI()
{
   QSqlQuery query(QString("SELECT * FROM %1;").arg(roiTable), db);
   if(query.size() == -1)
       error( "No se pudo conectar con la base de datos" );

   Params roiParams;
   if(query.next()){
     roiParams.insert("habilitado", query.value(0).toString());
     roiParams.insert("x1", query.value(1).toString());
     roiParams.insert("x2", query.value(2).toString());
     roiParams.insert("y1", query.value(3).toString());
     roiParams.insert("y2", query.value(4).toString());
   };

   return roiParams;
}

void DataBase::listTakes()
{
  for(int i=0; i<takes.size(); i++){
    cout << "*** Toma" << i+1 << endl;

    QHashIterator<QString, QString> it(takes.at(i));
    while(it.hasNext()){
        it.next();
        cout << it.key().toUtf8().data() << ": " 
             << it.value().toUtf8().data() << " # ";
    }
    cout << endl;
  }
}

void DataBase::log(const QString &values)
{
   QSqlQuery query(QString("INSERT INTO %1 VALUES(%2);").arg(
                   logTable).arg(values), db);

   query.exec();
}
