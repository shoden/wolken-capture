#ifndef DEVICE_H
#define DEVICE_H

// C
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/types.h>
#include <linux/videodev.h>
#include <libv4l2.h>

// C++
#include <iostream>

// OpenCV
#include <highgui.h>

// Qt4
#include <QString>
#include <QMap>
#include <QMapIterator>

using namespace std;

class Device
{
public:
    Device();

    int open();
    void close();
    void getParams();
    int setParam(const QString &name, int value);
    void listParams();
    int capture(const QString &file);

private:
    int fd, ret;
    QString device;
    QMap<QString, int> params;
    CvCapture *cap; // Dispositivo de vídeo
    int        dev; // Número del dispositivo de vídeo
};

#endif // DEVICE_H
