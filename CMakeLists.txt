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

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Project name
PROJECT(wolken-capture)

# Qt4 (only QtCore) and Qt4 SQL module
FIND_PACKAGE(Qt4 REQUIRED COMPONENTS QtCore)
ADD_DEFINITIONS(${QT_DEFINITIONS})

IF(QT_FOUND)
  INCLUDE(${QT_USE_FILE})
  MESSAGE(STATUS "Looking for Qt4 - found")
  IF(QT_QTSQL_FOUND)
    SET(QT_USE_QTSQL TRUE)
    SET(QT_DONT_USE_QTGUI TRUE)
    INCLUDE_DIRECTORIES(${QT_QTSQL_INCLUDE_DIR})
    MESSAGE(STATUS "Looking for Qt4 SQL module - found")
  ELSE(QT_QTSQL_FOUND)
    MESSAGE(FATAL_ERROR "Looking for Qt4 SQL module - not found")
  ENDIF(QT_QTSQL_FOUND) 
ELSE(QT_FOUND)
  MESSAGE(FATAL_ERROR "Looking for Qt4 - not found.")
ENDIF(QT_FOUND)

# Looking for V4L2
MESSAGE(STATUS "Looking for v4l2")
FIND_LIBRARY(V4L2_LIBRARY v4l2)
IF (V4L2_LIBRARY)
    MESSAGE(STATUS "Looking for v4l2 - found")
ELSE (V4L2_LIBRARY)
    MESSAGE(FATAL_ERROR "Looking for v4l2 - not found.")
ENDIF (V4L2_LIBRARY)

# Looking for OpenCV Highgui
MESSAGE(STATUS "Looking for highgui")
FIND_LIBRARY(HIGHGUI_LIBRARY highgui)
IF (HIGHGUI_LIBRARY)
    MESSAGE(STATUS "Looking for highgui - found")
ELSE (HIGHGUI_LIBRARY)
    MESSAGE(FATAL_ERROR "Looking for highgui - not found.")
ENDIF (HIGHGUI_LIBRARY)

# Include OpenCV path
INCLUDE_DIRECTORIES("/usr/include/opencv")

# Adding src subdirectory
ADD_SUBDIRECTORY(src)

