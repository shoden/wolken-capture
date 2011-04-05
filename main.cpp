#include "device.h"

int main(int argc, char *argv[])
{
    Device dev;

    if( dev.open() == EXIT_SUCCESS ){
      dev.getParams();

      dev.setParam("Exposure, Auto", 1);
      dev.setParam("Exposure (Absolute)", 300);

      dev.close();
      return 0;
    }

    return 1;
}
