#include "common.h"
#include "device.h"
#include "database.h"

int main(int argc, char *argv[])
{
    Device dev("/dev/video2");

    if( dev.open() == EXIT_SUCCESS ){
/*
      dev.setParam("Exposure, Auto", 1);

      dev.setParam("Exposure (Absolute)", 100);
      dev.capture("/home/juan/Escritorio/x1.bmp");

      dev.setParam("Exposure (Absolute)", 400);
      dev.capture("/home/juan/Escritorio/x2.bmp");

      dev.setParam("Exposure (Absolute)", 700);
      dev.capture("/home/juan/Escritorio/x3.bmp");

      dev.setParam("Exposure (Absolute)", 1000);
      dev.capture("/home/juan/Escritorio/x4.bmp");
*/

    }
    else
      return EXIT_FAILURE;


    DataBase db;
    db.getParams();
    Takes takes = db.getTakes();
    //db.listTakes();

    for (int i = 0; i < takes.size(); i++) {
      cout << endl << "*** Toma " << takes.at(i).value("id").toUtf8().data() << endl;

      QMapIterator<QString, QString> it(takes.at(i));
      while (it.hasNext()) {
          it.next();
          if(it.key() != "id"){
            if(it.key() == "Exposure (Absolute)")
              cout << "setParam(\"Exposure, Auto\", 1);" << endl;

            cout << "setParam(\"" << it.key().toUtf8().data() << "\", " << it.value().toUtf8().data() << ");" << endl;
            dev.setParam(it.key(), it.value().toInt());
          }
      }
      cout << "capture(\"DIR/" << takes.at(i).value("id").toUtf8().data() << ".bmp\")" << endl;

      dev.capture(QString(takes.at(i).value("id")).append(".bmp").toUtf8().data());

      cout << "thumb(\"DIR/" << takes.at(i).value("id").toUtf8().data() << ".bmp\")" << endl;
      cout << "db.log(" << takes.at(i).value("id").toUtf8().data() << ")" << endl;
    }

    dev.close();

    return EXIT_SUCCESS;
}
