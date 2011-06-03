QT += sql
QT -= gui
LIBS += -lv4l2 \
    -lcv \
    -lhighgui \
    -lcvaux \
    -lml \
    -lcxcore
INCLUDEPATH += /usr/include/opencv
HEADERS += device.h \
    database.h \
    common.h
SOURCES += device.cpp \
    main.cpp \
    database.cpp
