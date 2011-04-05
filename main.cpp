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
      vis.capture("x1.bmp");
      dev.close();
    }

    return 1;
}
