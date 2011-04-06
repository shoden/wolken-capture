#include "device.h"

Device::Device()
{
  device = "/dev/video2";
  dev = 2;
  cap = 0;
}

int Device::open()
{
  // V4L2
  fd = v4l2_open(device.toUtf8().data() , O_RDWR, 0);

  if(fd < 0) {
      fprintf(stderr, "No se pudo abrir el dispositivo %s: %s\n", device.toUtf8().data(), strerror(errno));
      exit(EXIT_FAILURE);
  }

  getParams();

  // OpenCV
  cap = cvCaptureFromCAM( dev );
  if( !cap ) {
    fprintf(stderr,"No se pudo conectar con el dispositivo /dev/video%d\n", dev);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

int Device::capture(const QString &file)
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

void Device::close()
{
  v4l2_close(fd);
}

void Device::getParams()
{
  int i;
   struct v4l2_queryctrl ctrl;
   struct v4l2_control c;
   const char *param;
   param = "ueee";

#ifdef V4L2_CTRL_FLAG_NEXT_CTRL
   /* Try the extended control API first */
   ctrl.id = V4L2_CTRL_FLAG_NEXT_CTRL;
   if(0 == v4l2_ioctl (fd, VIDIOC_QUERYCTRL, &ctrl)) {
       do {
           c.id = ctrl.id;
           ctrl.id |= V4L2_CTRL_FLAG_NEXT_CTRL;
           if(ctrl.flags & V4L2_CTRL_FLAG_DISABLED) {
               continue;
           }
           if(ctrl.type != V4L2_CTRL_TYPE_INTEGER &&
              ctrl.type != V4L2_CTRL_TYPE_BOOLEAN &&
              ctrl.type != V4L2_CTRL_TYPE_MENU) {
               continue;
           }
           if(v4l2_ioctl(fd, VIDIOC_G_CTRL, &c) == 0) {
               //printf("1. %u:%31s:%d\n", c.id, ctrl.name, c.value);
               //param = (char*)ctrl.name;
              // cout << "[" << param << "] [" << c.id << "] [" << c.value << "]" << endl;
               params.insert(QString( (char*)ctrl.name ), c.id);

           }
       } while(0 == v4l2_ioctl (fd, VIDIOC_QUERYCTRL, &ctrl));
   } else
#endif
   {
       /* Check all the standard controls */
       for(i=V4L2_CID_BASE; i<V4L2_CID_LASTP1; i++) {
           ctrl.id = i;
           if(v4l2_ioctl(fd, VIDIOC_QUERYCTRL, &ctrl) == 0) {
               if(ctrl.flags & V4L2_CTRL_FLAG_DISABLED) {
                   continue;
               }
               if(ctrl.type != V4L2_CTRL_TYPE_INTEGER &&
                  ctrl.type != V4L2_CTRL_TYPE_BOOLEAN &&
                  ctrl.type != V4L2_CTRL_TYPE_MENU) {
                   continue;
               }
               c.id = i;
               if(v4l2_ioctl(fd, VIDIOC_G_CTRL, &c) == 0) {
                   //printf("2. %u:%31s:%d\n", i, ctrl.name, c.value);
                   params.insert(QString( (char*)ctrl.name ), i);
               }
           }
       }

       /* Check any custom controls */
       for(i=V4L2_CID_PRIVATE_BASE; ; i++) {
           ctrl.id = i;
           if(v4l2_ioctl(fd, VIDIOC_QUERYCTRL, &ctrl) == 0) {
               if(ctrl.flags & V4L2_CTRL_FLAG_DISABLED) {
                   continue;
               }
               if(ctrl.type != V4L2_CTRL_TYPE_INTEGER &&
                  ctrl.type != V4L2_CTRL_TYPE_BOOLEAN &&
                  ctrl.type != V4L2_CTRL_TYPE_MENU) {
                   continue;
               }
               c.id = i;
               if(v4l2_ioctl(fd, VIDIOC_G_CTRL, &c) == 0) {
                   //printf("3. %u:%31s:%d\n", i, ctrl.name, c.value);

                 params.insert(QString( (char*)ctrl.name ), i);
               }
           } else {
               break;
           }
       }
   }
}

void Device::listParams()
{
   QMapIterator<QString, int> it(params);
   while (it.hasNext()) {
       it.next();
       cout << it.key().toUtf8().data() << ": " << it.value() << endl;
   }
}

int Device::setParam(const QString &name, int value)
{
//  __u32 id;
//  __s32 value;
  struct v4l2_queryctrl ctrl;
  struct v4l2_control c;

  if(!params.contains(name))
    exit(EXIT_FAILURE);

  ctrl.id = params.value(name);


  if(v4l2_ioctl(fd, VIDIOC_QUERYCTRL, &ctrl) == 0) {

    c.id = params.value(name);
    c.value = value;
    if(v4l2_ioctl(fd, VIDIOC_S_CTRL, &c) != 0) {
      fprintf(stderr, "Failed to set control \"%s\": %s\n", name.toUtf8().data(), strerror(errno));
    }
  }
  else {
    fprintf(stderr, "Error querying control %s: %s\n", name.toUtf8().data(), strerror(errno));
    return EXIT_FAILURE;
 }

  return EXIT_SUCCESS;
}

