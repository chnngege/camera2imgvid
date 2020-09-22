FIND_PACKAGE( OpenCV REQUIRED )
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

SET( SRC_LIST
main.cpp 
tinyxml/tinystr.cpp 
tinyxml/tinyxml.cpp 
tinyxml/tinyxmlerror.cpp 
tinyxml/tinyxmlparser.cpp )

add_executable( camera2imgvid ${SRC_LIST} )

ADD_LIBRARY( time_camera SHARED time_camera.cpp )
ADD_LIBRARY( xml_para SHARED xml_para.cpp )

INCLUDE_DIRECTORIES( ../include)

TARGET_LINK_LIBRARIES( camera2imgvid time_camera)
TARGET_LINK_LIBRARIES( camera2imgvid xml_para)
TARGET_LINK_LIBRARIES( camera2imgvid ${OpenCV_LIBS} )
