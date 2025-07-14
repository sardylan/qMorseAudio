add_library(morseino
        config.hpp config.cpp
        default.hpp
        morseino.hpp morseino.cpp)

target_link_libraries(morseino PUBLIC
        utilities
        Qt::Core Qt::SerialPort)
