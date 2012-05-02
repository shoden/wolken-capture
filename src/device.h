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

#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"

// C
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/types.h>
#include <libv4l1-videodev.h>
#include <linux/videodev2.h>
#include <libv4l2.h>

// OpenCV
#include <highgui.h>

class Device
{
public:
  Device(const QString &d);
  ~Device();

  int open();
  void close();
  void setDevice(const QString &d);
  void getParams();
  int setParam(const QString &name, int value);
  void listParams();
  void setROI(int x, int y, int width, int height);
  void resetROI();
  int capture(const QString &file, int thumbWidth, int thumbHeight);
  bool setBaseDir(const QString &d);
  void setTries(int t);

private:
  //! Descriptor del dispositivo de vídeo
  int fd;
  //! Número del dispositivo de vídeo
  QString device;
  //! Lista de parámetros (nombre, id)
  QMap<QString, int> params;
  //! Dispositivo de vídeo
  CvCapture *cap;
  //! Bandera para la región de interés
  bool roi;
  //! Rectángulo de la región de interés
  CvRect roiRect;
  //! Directorio base para guardar las capturas
  QDir dir;
  //! Número de intentos para cada captura
  int tries;
};

#endif // DEVICE_H
