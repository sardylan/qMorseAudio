find_package(Qt6
        REQUIRED
        COMPONENTS Core Gui Widgets Multimedia SerialPort Svg OpenGL OpenGLWidgets)

find_package(Qt6
        REQUIRED
        COMPONENTS Test)

qt_standard_project_setup()

if (WIN32 OR APPLE)
    if (WIN32)
        find_program(QT_DEPLOYQT_BIN windeployqt)
    elseif (APPLE)
        find_program(QT_DEPLOYQT_BIN macdeployqt)
    endif ()

    if (NOT QT_DEPLOYQT_BIN)
        message(FATAL_ERROR "No Qt Deploy command found.")
    endif ()
endif ()
