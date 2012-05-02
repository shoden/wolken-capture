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

SET(SOURCES database.cpp device.cpp main.cpp)
SET(HEADERS common.h database.h device.h)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src)

ADD_EXECUTABLE(wolken ${SOURCES})

TARGET_LINK_LIBRARIES(wolken 
                        ${QT_LIBRARIES}
                        ${QT_QTSQL_LIBRARIES} 
                        ${V4L2_LIBRARY}
                        ${OPENCV_CORE_LIBRARY}
                        ${HIGHGUI_LIBRARY}
                     )

INSTALL(TARGETS wolken DESTINATION bin)
