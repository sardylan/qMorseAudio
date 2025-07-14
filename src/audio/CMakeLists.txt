add_library(audio
        audio.hpp audio.cpp
        config.hpp config.cpp
        default.hpp
        oscillator.hpp oscillator.cpp)

target_link_libraries(audio PUBLIC
        utilities
        Qt::Core Qt::Multimedia)
