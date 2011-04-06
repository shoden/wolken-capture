#include "common.h"
#include "device.h"
#include "database.h"

int main(int argc, char *argv[])
{
    Device dev("/dev/video0");

    if( dev.open() != EXIT_SUCCESS )
      return EXIT_FAILURE;

    //dev.setROI(50, 50, 320, 240);
    DataBase db;
    QStringList plist = db.getParams();
    Takes takes = db.getTakes();
    QDateTime now = QDateTime::currentDateTime();
    dev.setBaseDir(QString(IMG_DIR).append(now.toString("yyyy-MM-dd/hhmm/")));

    // Para cada captura de la toma
    for (int i = 0; i < takes.size(); i++) {
     // cout << endl << "*** Toma " << takes.at(i).value("id").toUtf8().data() << endl;
      QString log = now.toString("\"yyyy-MM-dd\"") + ", " + now.toString("\"hh:mm:ss\"");
      log += ", " + takes.at(i).value("id");

      // Establecer los parámetros de la cámara
      Params take = takes.at(i);
      for (int p = 0; p < plist.size(); ++p){
        QString par = plist.at(p++);
        int val = take.value(par).toInt();
       // cout << "> setParam(" << par.toUtf8().data() << ", " << val << ")" << endl;
        dev.setParam(par, val);
        log += ", " + QString::number(val);
      }

      // Capturar y guardar imagen
      QString path = QString("/").append(QString(takes.at(i).value("id")).rightJustified(2,'0')).append(".bmp");
      dev.capture(path);

      // Crear el log
      db.log(log);
    }

    dev.close();
    return EXIT_SUCCESS;
}
