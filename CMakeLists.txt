cmake_minimum_required(VERSION 3.10)
enable_testing()
project(RCore VERSION 2.3.1)

if(NOT TARGET ${PROJECT_NAME})

option(GED_For_Another "Adds additional functions for C# when activated." ON)
if(GED_For_Another)
    message("You are activating [GED_For_Another]. This configuration will consider that you are willing to use it as dynamic linker library for another language than C/C++.")
endif()

configure_file(${PROJECT_SOURCE_DIR}/hin/Mig.h.in ${PROJECT_SOURCE_DIR}/include/GED/Mig.h)

add_library(
    ${PROJECT_NAME} ${ae2f_PREFIX_LIB}
    "hin/Mig.h.in"
    "include/GED/Mig.h"

    "include/GED/Clock.h"
    "src/xClock.cpp"

    "include/GED/Ctrl/MousePoint.h" 
    "src/Ctrl/MousePoint.c"
    
    "include/GED/Ctrl/Ev.h" 
    "src/Ctrl/Ev.c"

    "include/GED/Cam.h"
    "src/Cam.c"

    "include/GED/CLCam.h"
    "src/CLCam.c"

    "src/BmpSrc.c"

    "include/GED/CLPort.h"
    "src/CLPort.c"
)


add_subdirectory(mod/ae2f/BmpCL)
target_link_libraries(${PROJECT_NAME} BmpCL)

add_subdirectory(mod/ae2f/Ds)
target_link_libraries(${PROJECT_NAME} Ds)


include_directories(include)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE GED::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

add_subdirectory(test)

endif()