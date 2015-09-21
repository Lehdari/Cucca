cmake_minimum_required(VERSION 2.8)


#sources
file(GLOB cucca_core_SRC "*.cpp")
add_library(cucca-core SHARED ${cucca_core_SRC})


#libraries
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

target_link_libraries(cucca-core ${OPENGL_LIBRARIES})


#install
install (TARGETS cucca-core     DESTINATION lib)
