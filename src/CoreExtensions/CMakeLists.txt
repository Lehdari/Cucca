cmake_minimum_required(VERSION 2.8)


#sources
file(GLOB cucca_coreext_SRC "*.cpp")
add_library(cucca-coreext SHARED ${cucca_coreext_SRC})


#libraries
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cucca-coreext cucca-core ${SFML_LIBRARIES})
else()
    target_link_libraries(cucca-coreext cucca-core sfml-system sfml-window)
endif()

if(BUILD_DEBUG)
    target_link_libraries(cucca-coreext cucca-debug)
endif()


#install
install (TARGETS cucca-coreext      DESTINATION lib)
