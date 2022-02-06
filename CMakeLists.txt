cmake_minimum_required(VERSION 3.19.0)

project(haversine VERSION 0.1.0)

# C17 and C++20
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# Folders for IDEs that support it
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# We need to specify these types since we are supporting multi-config IDEs like Xcode and Visual Studio
set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")

if(WIN32)
    include(CMake/Setup.cmake)
endif()

set(header_files
  "source/haversine.h"
  "source/zipcodes.h"
)

set(source_files
  "source/haversine.cpp"
  "source/zipcodes.cpp"
)

if(APPLE)
    list(APPEND source_files "source/mac/main.m" "source/mac/WndController.mm")
    list(APPEND header_files "source/mac/WndController.h")
endif()
if(WIN32)
    list(APPEND source_files "source/win/main.cpp")
endif()

#####################################################
# Main app
add_executable(haversine "${source_files}" "${header_files}")

include_directories(source)

if(WIN32)
    target_link_libraries(haversine
        PRIVATE
        argparse::argparse
)
endif()

# The following file is used by the CLI
configure_file("zips.csv" "${CMAKE_BINARY_DIR}" COPYONLY)
