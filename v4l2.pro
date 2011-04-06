LIBS += -lv4l2 \
    -lcv \
    -lhighgui \
    -lcvaux \
    -lml \
    -lcxcore
INCLUDEPATH += /usr/include/opencv
HEADERS += device.h
SOURCES += device.cpp \
    main.cpp
