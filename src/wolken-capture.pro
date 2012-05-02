#
#  Copyright © 2011 Juan Roldan Ruiz <juan@shoden.es>
#
#  This file is part of wolken-capture.
#
#  wolken-capture is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  wolken-capture is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with wolken-capture.  If not, see <http://www.gnu.org/licenses/>.
#

QT += sql
QT -= gui
LIBS += \
    -lv4l2 \
    -lopencv_highgui \
    -lopencv_core
INCLUDEPATH += /usr/include/opencv
HEADERS += device.h \
    database.h \
    common.h
SOURCES += device.cpp \
    main.cpp \
    database.cpp
TARGET=wolken
