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
#include <linux/videodev.h>
#include <libv4l2.h>

// OpenCV
#include <opencv/highgui.h>


class Device
{
public:
    Device(const QString &d);

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
    bool roi;
    CvRect roiRect;
    QDir dir;
    //! Número de intentos para cada captura
    int tries;
};

#endif // DEVICE_H
