LIBS += -lv4l2 -lcv -lhighgui -lcvaux -lml -lcxcore
INCLUDEPATH += /usr/include/opencv
HEADERS += device.h \
    vision.h
SOURCES += device.cpp \
    main.cpp \
    vision.cpp
