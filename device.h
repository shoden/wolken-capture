#ifndef DEVICE_H
#define DEVICE_H

#include <common.h>

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
#include <highgui.h>


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
    int capture(const QString &file);

private:
    //! Descriptor del dispositivo de vídeo
    int fd;
    //! Número del dispositivo de vídeo
    QString device;
    //! Lista de parámetros (nombre, id)
    QMap<QString, int> params;
    //! Dispositivo de vídeo
    CvCapture *cap;
};

#endif // DEVICE_H
