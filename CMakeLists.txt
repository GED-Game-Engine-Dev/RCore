cmake_minimum_required(VERSION 3.10)
enable_testing()
project(RCore VERSION 2.6.11)
include(cmake/Core.cmake)

if(NOT TARGET ${PROJECT_NAME})

option(GED_For_Another "Adds additional functions for C# when activated." ON)
if(GED_For_Another)
    message("You are activating [GED_For_Another]. This configuration will consider that you are willing to use it as dynamic linker library for another language than C/C++.")
endif()

configure_file(${PROJECT_SOURCE_DIR}/hin/Mig.h.in ${PROJECT_SOURCE_DIR}/include/GED/Mig.h)

ae2f_CoreLibFetch(ae2f CL-Bmp Rel-v4.7.18)
ae2f_CoreLibFetch(ae2f Ds Rel-v1.11.2)

ae2f_CoreLibTent(
    ${PROJECT_NAME} 
    ${ae2f_LIBPREFIX} 
    include GED
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

    "include/GED/Mov2/Rect.h"
    "src/Mov2/Rect.c"
)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC CL-Bmp)
target_link_libraries(${PROJECT_NAME} PUBLIC Ds)

endif()