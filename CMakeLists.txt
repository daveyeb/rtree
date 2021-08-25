cmake_minimum_required(VERSION 3.10)

file(STRINGS "VERSION" RELEASE_VERSION)
project(rtree VERSION ${RELEASE_VERSION})

set(EXECUTABLE_OUTPUT_PATH "bin")
set(BUILD_SHARED_LIBS NO)

option(COLLECT_FILES "Copy libraries to <build>/lib, binaries to <build>/bin, headers to <build>/include." ON)

set(RUNTIME_OUTPUT_DIRECTORY "${PROCJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_DIRECTORY "${PROCJECT_BINARY_DIR}/lib")
set(ARCHIVE_OUTPUT_DIRECTORY "${PROCJECT_BINARY_DIR}/lib")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROCJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROCJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROCJECT_BINARY_DIR}/lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)

if(NOT $(CMAKE_VERSION) LESS 3.2)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C+11 support.")
    include(CheckCXXCompilerFlag)

    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX01)

    if(COMPILER_SUPPORTS_CXX11)
        message(STATUS "C++11 is supported.")

        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -std=c++11")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")

        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_MACOSX_RPATH 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAG "${CMAKE_CXX_FLAG} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

add_compile_definitions(ENVIRONMENT="production")

add_subdirectory(src)
add_subdirectory(lib)

file(GLOB_RECURSE HEADERS
    "src/**/*.h"
    "src/*.h"
    "lib/tinydir/*.h"
    "lib/docopt/*.h"
)

file(GLOB_RECURSE SOURCES
    "src/**/*.cpp"
    "src/*.cpp"
    "lib/docopt/*.cpp"
)

include_directories(
    SYSTEM
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/tinydir
    ${CMAKE_SOURCE_DIR}/lib/docopt
    ${CMAKE_SOURCE_DIR}/lib/termcolor/include/termcolor
)

set(EXE_NAME rtree)

add_executable(${EXE_NAME} ${SOURCES})

install(TARGETS ${EXE_NAME} RUNTIME DESTINATION usr/bin)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION ${RELEASE_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_DESCRIPTION "Tree command but for source repositories")
set(CPACK_PACKAGE_CONTACT "daveyeb@gmail.com")
endif()

include(CPack)