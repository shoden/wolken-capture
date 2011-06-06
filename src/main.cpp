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

#include "common.h"
#include "device.h"
#include "database.h"

int main(int argc, char *argv[])
{
  opterr = 0;
  int c;

  // Archivo de configuración
  QSettings settings(QSettings::SystemScope, "wolken", "wolken");
  settings.beginGroup("Main");
  QString d = settings.value("device", "/dev/video0").toString();
  QString IMGPATH = settings.value("imgpath", "/home/juan/img/wolken/").toString();
  int thumb_width = settings.value("thumb_width", 128).toInt();
  int thumb_height = settings.value("thumb_height", 96).toInt();
  int tries = settings.value("capture_tries", 10).toInt();
  settings.endGroup();

  // Procesar los argumentos
  while((c = getopt (argc, argv, "d:")) != -1)
    switch(c){
      case 'd':
        d = optarg;
        break;
      case '?':
        if (optopt == 'd')
          fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
        else
          fprintf (stderr,
              "Unknown option character `\\x%x'.\n",
              optopt);
        return EXIT_FAILURE;
      default:
        abort ();
    }

  // Abrir dispositivo de vídeo
  Device *dev = new Device(d);
  if(dev->open() != EXIT_SUCCESS)
    return EXIT_FAILURE;

  // Obtener configuración de la base de datos
  DataBase *db = new DataBase();
  QStringList plist = db->getParams();
  Takes takes = db->getTakes();

  // Obtener fecha actual
  QDateTime now = QDateTime::currentDateTime();
  dev->setBaseDir(QString(IMGPATH).append(now.toString("yyyy-MM-dd/hhmm/")));

  // Establecer la región de interés de la imagen
  Params roiParams = db->getROI();
  bool roi = (roiParams.value("habilitado").compare("1") == 0) ? true : false;
  if(roi){
    int roi_x = roiParams.value("x1").toInt();
    int roi_y = roiParams.value("y1").toInt();
    int roi_width = roiParams.value("x2").toInt() - roi_x;
    int roi_height = roiParams.value("y2").toInt() - roi_y;
    dev->setROI(roi_x, roi_y, roi_width, roi_height);
  };

  // Establecer el número de intentos para cada captura
  dev->setTries(tries);

  // Para cada captura de la toma
  for(int i=0; i<takes.size(); i++){
    QString log = now.toString("\"yyyy-MM-dd\"") + ", "
                + now.toString("\"hh:mm:ss\"");
    log += ", " + takes.at(i).value("id");

    // Establecer los parámetros de la cámara
    Params take = takes.at(i);
    for(int p=0; p<plist.size(); ++p){
      QString par = plist.at(p++);
      int val = take.value(par).toInt();

      // Exposicón en modo manual
      if(par == "Exposure (Absolute)")
        dev->setParam("Exposure, Auto", 1);

      dev->setParam(par, val);
      log += ", " + QString::number(val);
    }

    // Capturar y guardar imagen
    QString path = QString("/").append(QString(takes.at(i).value("id")
                               ).rightJustified(2,'0')).append(".bmp");
    dev->capture(path, thumb_width, thumb_height);

    // Crear registro en el log
    db->log(log);
  }

  // Cerrar dispositivo de vídeo
  dev->close();

  // Liberar memoria
  delete db;
  delete dev;

  return EXIT_SUCCESS;
}
