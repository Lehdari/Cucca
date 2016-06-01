cmake_minimum_required(VERSION 2.8)


#sources
file(GLOB cucca_core_SRC "*.cpp")
add_library(cucca-core SHARED ${cucca_core_SRC})


#libraries
#find_package(OpenGL REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIRS})
#link_directories(${OpenGL_LIBRARY_DIRS})
#add_definitions(${OpenGL_DEFINITIONS})

#find_path(GLEW_INCLUDE_DIR GL/glew.h)
#find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)
#add_definitions(-DGLEW_STATIC)

target_link_libraries(cucca-core ${GLEW_LIBRARY})# ${OPENGL_LIBRARIES})


#link debug
if(CUCCA_BUILD_DEBUG)
    target_link_libraries(cucca-core cucca-debug)
endif()


#install
install (TARGETS cucca-core     DESTINATION lib)
