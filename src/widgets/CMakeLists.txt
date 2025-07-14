add_library(widgets
        morse_strip.hpp morse_strip.cpp)

target_link_libraries(widgets
        PUBLIC Qt::Core Qt::Gui Qt::Widgets Qt::OpenGL Qt::OpenGLWidgets)
