configure_file(version.hpp.in version.hpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(morseaudio
        WIN32 MACOSX_BUNDLE
        config.hpp config.cpp
        main.hpp main.cpp
        morseaudio.hpp morseaudio.cpp
        version.hpp.in
        windows/about.ui windows/about.hpp windows/about.cpp
        windows/config.ui windows/config.hpp windows/config.cpp
        windows/main.ui windows/main.hpp windows/main.cpp)

set_target_properties(morseaudio
        PROPERTIES
        OUTPUT_NAME MorseAudio)

target_link_libraries(morseaudio PRIVATE
        audio morseino widgets
        Qt::Core Qt::SerialPort Qt::Gui Qt::Widgets Qt::Multimedia Qt::OpenGL Qt::OpenGLWidgets)
