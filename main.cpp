#include "device.h"
#include "vision.h"

int main(int argc, char *argv[])
{
    Device dev;
    Vision vis;

    if( dev.open() == EXIT_SUCCESS ){
      vis.open(2);

      dev.setParam("Exposure, Auto", 1);

      dev.setParam("Exposure (Absolute)", 30);
      vis.capture("/home/juan/Escritorio/x1.bmp");

      dev.setParam("Exposure (Absolute)", 80);
      vis.capture("/home/juan/Escritorio/x2.bmp");

      dev.setParam("Exposure (Absolute)", 120);
      vis.capture("/home/juan/Escritorio/x3.bmp");

      dev.setParam("Exposure (Absolute)", 200);
      vis.capture("/home/juan/Escritorio/x4.bmp");


      dev.close();
    }


    return EXIT_SUCCESS;
}
