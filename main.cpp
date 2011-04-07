#include "common.h"
#include "device.h"
#include "database.h"

int main(int argc, char *argv[])
{
  // Dispositivo por defecto
  QString d = "/dev/video0";
  opterr = 0;
  int c;

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
  dev.setBaseDir(QString(IMG_DIR).append(now.toString("yyyy-MM-dd/hhmm/")));

  // Establecer región de interés de la imagen
  //dev.setROI(50, 50, 320, 240);

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
    dev.capture(path);

    // Crear registro en el log
    db.log(log);
  }

  // Cerrar dispositivo de vídeo
  dev.close();

  return EXIT_SUCCESS;
}
