cmake_minimum_required(VERSION 3.31)

project(qMorseAudio
        VERSION 0.0.0
        LANGUAGES CXX)

include(cmake/version.cmake)
include(cmake/package.cmake)
include(cmake/flags.cmake)
include(cmake/deps.cmake)
include(cmake/qt.cmake)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(desktop)
