#ifndef DEVICE_H
#define DEVICE_H

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
#include <iostream>

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

private:
    int fd, ret;
    QString dev;
    QMap<QString, int> params;
};

#endif // DEVICE_H
