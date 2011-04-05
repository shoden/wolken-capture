#include "vision.h"

Vision::Vision()
{
  cap = 0;
  dev = 0;
}

int Vision::open(int device)
{
  dev = device;

  cap = cvCaptureFromCAM( dev );
  if( !cap ) {
    fprintf(stderr,"No se pudo conectar con el dispositivo /dev/video%d\n", dev);
    exit(EXIT_FAILURE);
  }

  return 0;
}


int Vision::capture(const QString &file)
{
  // Variables
  IplImage  *img = 0; // Imagen a capturar

  // Captura de imagen
  img = cvQueryFrame( cap );
  img = cvQueryFrame( cap );
  img = cvQueryFrame( cap );
  img = cvQueryFrame( cap );
  img = cvQueryFrame( cap );
  if( !img ) {
    fprintf(stderr,"No se pudo capturar la imagen\n");
    exit(EXIT_FAILURE);
  }

 // CvRect rect = cvRect(50, 60, 400, 300);
 // cvSetImageROI(img, rect);

  // Guardar imagen
  if( !cvSaveImage( file.toUtf8().data(), img) ) {
    fprintf(stderr,"No se pudo guardar la imagen\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
