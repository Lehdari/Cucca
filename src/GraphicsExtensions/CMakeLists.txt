cmake_minimum_required(VERSION 2.8)


#sources
file(GLOB cucca_graphicsext_SRC "*.cpp")
add_library(cucca-graphicsext SHARED ${cucca_graphicsext_SRC})


#libraries
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cucca-graphicsext cucca-graphics ${SFML_LIBRARIES})
else()
    target_link_libraries(cucca-graphicsext cucca-graphics cucca-coreext sfml-system sfml-window) #todo cucca-coreext should not be required
endif()


#install
install (TARGETS cucca-graphicsext  DESTINATION lib)
