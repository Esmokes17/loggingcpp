cmake_minimum_required(VERSION 3.9)

project(logging VERSION 1.0.0)

add_library(logging SHARED logging.cpp)
set_target_properties(logging PROPERTIES
                    VERSION ${PROJECT_VERSION}
                    PUBLIC_HEADER logging.h)

include(GNUInstallDirs)
install(TARGETS logging
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
add_subdirectory(test)
