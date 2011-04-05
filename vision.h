#ifndef VISION_H
#define VISION_H

#include <stdio.h>   // Cabecera C++
#include <iostream>   // Cabecera C++
#include <highgui.h>  // Cabecera OpenCV
#include <QString>

class Vision
{
public:
    Vision();

    int open(int device);
    int capture(const QString &file);

private:
    CvCapture *cap; // Dispositivo de vídeo
    int        dev; // Número del dispositivo de vídeo
};

#endif // VISION_H
