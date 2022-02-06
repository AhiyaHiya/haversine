
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(
    REQUIRES
        # https://github.com/p-ranav/argparse
        argparse/2.2
    GENERATORS
        cmake_find_package_multi
)

# Each config has to be set up for each package, so we'll loop through each (Debug, Release)
foreach(type ${CMAKE_CONFIGURATION_TYPES})
    message(STATUS "Configuring build type ${type}")
    conan_cmake_autodetect(settings BUILD_TYPE ${type})
    conan_cmake_install(PATH_OR_REFERENCE .
                        BUILD missing
                        SETTINGS ${settings})
endforeach()

# Now call find_package
find_package(argparse CONFIG)
