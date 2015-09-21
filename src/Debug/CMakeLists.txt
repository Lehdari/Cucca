cmake_minimum_required(VERSION 2.8)


#sources
file(GLOB cucca_debug_SRC "*.cpp")
add_library(cucca-debug SHARED ${cucca_debug_SRC})


#install
install (TARGETS cucca-debug        DESTINATION lib)
