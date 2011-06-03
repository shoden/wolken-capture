SET(SOURCES database.cpp device.cpp main.cpp)
SET(HEADERS common.h database.h device.h)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src)

ADD_EXECUTABLE(wolken ${SOURCES})

TARGET_LINK_LIBRARIES(wolken ${QT_LIBRARIES} ${QT_QTSQL_LIBRARIES} 
                             ${V4L2_LIBRARY} ${CV_LIBRARY} 
                             ${CVAUX_LIBRARY} ${HIGHGUI_LIBRARY})

INSTALL(TARGETS wolken DESTINATION bin)
