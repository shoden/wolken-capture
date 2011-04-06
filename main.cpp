#include "device.h"

int main(int argc, char *argv[])
{
    Device dev("/dev/video2");

    if( dev.open() == EXIT_SUCCESS ){

      dev.setParam("Exposure, Auto", 1);

      dev.setParam("Exposure (Absolute)", 100);
      dev.capture("/home/juan/Escritorio/x1.bmp");

      dev.setParam("Exposure (Absolute)", 400);
      dev.capture("/home/juan/Escritorio/x2.bmp");

      dev.setParam("Exposure (Absolute)", 700);
      dev.capture("/home/juan/Escritorio/x3.bmp");

      dev.setParam("Exposure (Absolute)", 1000);
      dev.capture("/home/juan/Escritorio/x4.bmp");

      dev.close();
    }

    return EXIT_SUCCESS;
}
