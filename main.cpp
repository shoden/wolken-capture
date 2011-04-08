#include "common.h"
#include "device.h"
#include "database.h"

int main(int argc, char *argv[])
{
  opterr = 0;
  int c;

  // Archivo de configuración
  QSettings settings(QSettings::SystemScope, "wolken", "wolken");
  settings.beginGroup( "Main" );
  QString d = settings.value( "device", "/dev/video0" ).toString();
  QString IMGPATH = settings.value( "imgpath", "/home/juan/img/wolken/" ).toString();
  bool roi = settings.value( "roi", 0 ).toBool();
  int roi_x = settings.value( "roi_x", 0 ).toInt();
  int roi_y = settings.value( "roi_y", 0 ).toInt();
  int roi_width = settings.value( "roi_width", 640 ).toInt();
  int roi_height = settings.value( "roi_height", 480 ).toInt();
  int thumb_width = settings.value( "thumb_width", 128 ).toInt();
  int thumb_height = settings.value( "thumb_height", 96 ).toInt();
  settings.endGroup();

  // Procesar los argumentos
  while ((c = getopt (argc, argv, "d:")) != -1)
    switch (c)
    {
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
  Device dev(d);
  if(dev.open() != EXIT_SUCCESS)
    return EXIT_FAILURE;

  // Obtener configuración de la base de datos
  DataBase db;
  QStringList plist = db.getParams();
  Takes takes = db.getTakes();

  // Obtener fecha actual
  QDateTime now = QDateTime::currentDateTime();
  dev.setBaseDir(QString(IMGPATH).append(now.toString("yyyy-MM-dd/hhmm/")));

  // Establecer región de interés de la imagen
  if(roi)
    dev.setROI(roi_x, roi_y, roi_width, roi_height);

  // Para cada captura de la toma
  for (int i = 0; i < takes.size(); i++) {
    QString log = now.toString("\"yyyy-MM-dd\"") + ", " + now.toString("\"hh:mm:ss\"");
    log += ", " + takes.at(i).value("id");

    // Establecer los parámetros de la cámara
    Params take = takes.at(i);
    for (int p = 0; p < plist.size(); ++p){
      QString par = plist.at(p++);
      int val = take.value(par).toInt();

      // Exposicón en modo manual
      if(par == "Exposure (Absolute)")
        dev.setParam("Exposure, Auto", 1);

      dev.setParam(par, val);
      log += ", " + QString::number(val);
    }

    // Capturar y guardar imagen
    QString path = QString("/").append(QString(takes.at(i).value("id")).rightJustified(2,'0')).append(".bmp");
    dev.capture(path, thumb_width, thumb_height);

    // Crear registro en el log
    db.log(log);
  }

  // Cerrar dispositivo de vídeo
  dev.close();

  return EXIT_SUCCESS;
}
