cmake_minimum_required(VERSION 2.8)


#sources
file(GLOB cucca_coreext_SRC "*.cpp")
add_library(cucca-coreext SHARED ${cucca_coreext_SRC})


#libraries

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

#GLEW
find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)
include_directories(${GLEW_INCLUDE_DIR})
add_definitions(-DGLEW_STATIC)

#SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cucca-coreext cucca-core ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} ${SFML_LIBRARIES})
else()
    #target_link_libraries(cucca-coreext cucca-core sfml-system sfml-window)
endif()


#link debug
if(CUCCA_BUILD_DEBUG)
    target_link_libraries(cucca-coreext cucca-debug)
endif()


#install
install (TARGETS cucca-coreext      DESTINATION lib)
