option(ae2f_IS_SHARED "Is a shared library or static one." OFF)
option(ae2f_DOC "When activated, it would generate project with the deaders of cmake utility functions." OFF)
option(ae2f_TEST "When activated, it would generate test projects." ON)
set(ae2f_float float CACHE STRING "Float type for the template.")
set(ae2f_packcount 0 CACHE STRING "Pack count for pre-defined structures.")
set(ae2f_ProjRoot ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Current Source Root")
set(ae2f_BinRoot ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "Current Binary Root")

if(ae2f_IS_SHARED)
    set(ae2f_LIBPREFIX SHARED CACHE STRING "SHARED")
else()
    set(ae2f_LIBPREFIX STATIC CACHE STRING "STATIC")
endif()

# @namespace ___DOC_CMAKE
# @brief
# Note they functions defined on CMake, not C/C++.

# @brief
# Iterates a directory `prm_TestSourcesDir` and 
# Make a test case for every source.
# 
# @param prm_LibName
# Base Library name
# 
# @param prm_TestSourcesDir
# A directory where the stand-alone test codes locate. \n
# Every sources under that directory must be stand-alone, which means it must not depends on another memory, function, etc.
# 
# @param ...
# Additional Libraries if you want
# 
# @see ___DOC_CMAKE::ae2f_TEST
function(ae2f_CoreTestTent prm_LibName prm_TestSourcesDir)
    if(ae2f_TEST)
        file(GLOB_RECURSE files "${prm_TestSourcesDir}/*")
        list(LENGTH files list_length)
        
        math(EXPR adjusted_length "${list_length} - 1")

        foreach(i RANGE 0 ${adjusted_length})
            list(GET files ${i} item)
            add_executable("${prm_LibName}-Test${i}" ${item})
            target_link_libraries("${prm_LibName}-Test${i}" ${ARGN} ${prm_LibName})
            add_test(NAME "${prm_LibName}-Test${i}" COMMAND "${prm_LibName}-Test${i}")
        endforeach()
    endif()
endfunction()

# @brief
# Makes a Library installable.
# 
# @param prm_TarName
# Library name you want.
# 
# @param prm_TarPrefix
# [STATIC | SHARED | INTERFACE]
# 
# @param prm_includeDir
# The include directory relative to the project CMakeLists.txt
# 
# @param prm_namespace
# Namespace (or header root directory after include)
# 
# @param ...
# The sources for the project.
function(ae2f_CoreLibTent prm_TarName prm_TarPreFix prm_includeDir prm_namespace)
    # Namespace Package
    include(GNUInstallDirs)

    include_directories(${prm_includeDir})
    add_library(${prm_TarName} ${prm_TarPreFix} ${ARGN})

    target_include_directories(
        ${prm_TarName} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${prm_includeDir}/>  
        $<INSTALL_INTERFACE:${prm_includeDir}/${prm_namespace}/>
    )

    # Install Settings
    install(TARGETS "${prm_TarName}"
        EXPORT ${prm_TarName}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
        
    install(DIRECTORY ${prm_includeDir}/${prm_namespace}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${prm_namespace}
    )

    # Package
    install(EXPORT ${prm_TarName}Targets
        FILE ${prm_TarName}Targets.cmake
        NAMESPACE ae2f::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
    )
        
    # Pack Conf
    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${prm_TarName}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
    )
        
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${prm_TarName}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
    )
endfunction()

# @brief
# Generate an interface project for document code for cmake utility functions. \n
# Available when ___DOC_CMAKE::ae2f_DOC is ON.
# 
# @param prm_TarName
# Library name you want.
# 
# @param prm_includeDir
# Where the documents exist
# The include directory relative to the project CMakeLists.txt
# 
# @param prm_namespace
# Namespace (or header root directory after include)
# 
# @param ...
# The past documents name
# @see ___DOC_CMAKE::ae2f_CoreLibTent
# @see ___DOC_CMAKE::ae2f_DOC
function(ae2f_CoreUtilityDocTent prm_TarName prm_includeDir prm_namespace)
    if(ae2f_DOC)
        file(GLOB_RECURSE src ${prm_includeDir} "*.cmake.hpp")
        ae2f_CoreLibTent(${prm_TarName}-CMakeDoc INTERFACE ${prm_includeDir} ${prm_namespace}doc ${src})
        foreach(lib ${ARGN})
            target_link_libraries(${prm_TarName}-CMakeDoc INTERFACE ${lib}-CMakeDoc)
        endforeach()
    endif()
endfunction()

# @brief 
# It will try to fetch the cmake project ae2f-Core like project for Local and Github. \n
# @see ___DOC_CMAKE::ae2f_LibDirGlob is the given path to check. \n 
# 
# Once the project is in given directory, it will not try to fetch it from internet.
# @param prm_AuthorName 
# Author name
# @param prm_TarName
# Target name 
# @param prm_TagName
# Tag name
function(ae2f_CoreLibFetch prm_AuthorName prm_TarName prm_TagName)
    if(NOT EXISTS ${ae2f_ProjRoot}/submod/${prm_AuthorName}/${prm_TarName}/CMakeLists.txt)
        execute_process(
            COMMAND 
            git clone 
            https://github.com/${prm_AuthorName}/${prm_TarName} 
            ${ae2f_ProjRoot}/submod/${prm_AuthorName}/${prm_TarName}
            --branch ${prm_TagName}
            RESULT_VARIABLE result
        )

        if(result)
            message(FATAL_ERROR "Fetching ${prm_AuthorName}/${prm_TarName} from Github Failed.")
        endif()
    endif()

    if(NOT TARGET ${prm_TarName})
        add_subdirectory(
            ${ae2f_ProjRoot}/submod/${prm_AuthorName}/${prm_TarName}
            ${ae2f_BinRoot}/submod/${prm_AuthorName}/${prm_TarName}
        )
    endif()
endfunction()