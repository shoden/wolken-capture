#include "device.h"

Device::Device(const QString &d)
{
  device = d;
  cap = 0;
  roi = false;
}

void Device::setDevice(const QString &d)
{
  device = d;
}

int Device::open()
{
  // V4L2
  fd = v4l2_open(device.toUtf8().data() , O_RDWR, 0);

  if(fd < 0) {
      fprintf(stderr, "No se pudo abrir el dispositivo %s: %s\n", device.toUtf8().data(), strerror(errno));
      return EXIT_FAILURE;
  }

  getParams();

  // OpenCV
  cap = cvCaptureFromCAM( device.right(1).toInt() );
  if( !cap ) {
    fprintf(stderr,"No se pudo conectar con el dispositivo /dev/video%d\n", device.right(1).toInt());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void Device::setROI(int x, int y, int width, int height)
{
  roiRect = cvRect(x, y, width, height);
  roi = true;
}

void Device::resetROI()
{
  roi = false;
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
  img = cvQueryFrame( cap );
  img = cvQueryFrame( cap );
  img = cvQueryFrame( cap );
  img = cvQueryFrame( cap );
  if( !img ) {
    fprintf(stderr,"No se pudo capturar la imagen\n");
    exit(EXIT_FAILURE);
  }

  // ROI
  if(roi)
    cvSetImageROI(img, roiRect);

  // Guardar imagen
  cout << "F:" << dir.path().append(file).toUtf8().data() << endl;
  if( !cvSaveImage( dir.path().append(file).toUtf8().data(), img) ) {
    fprintf(stderr,"No se pudo guardar la imagen\n");
    exit(EXIT_FAILURE);
  }

  // Crear miniatura
  QString cmd = QString("convert %1%2 -resize 120x90 %1/thumbs%2").arg(dir.path()).arg(file);
 // cout << cmd.toUtf8().data() << endl;
  int ret = system(cmd.toUtf8().data());

  return ret;
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

bool Device::setBaseDir(const QString &d)
{
  dir.setPath(d);

  if(!dir.exists())
    return (dir.mkpath(d) && dir.mkpath(QString(d).append("thumbs/")));

  return true;
}
