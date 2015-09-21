cmake_minimum_required(VERSION 2.8)


#sources
file(GLOB cucca_graphics_SRC "*.cpp")
add_library(cucca-graphics SHARED ${cucca_graphics_SRC})


#libraries
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)

target_link_libraries(cucca-graphics cucca-core ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})


#install
install (TARGETS cucca-graphics     DESTINATION lib)
