configure_file(version.hpp.in version.hpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(qmorseaudio
        WIN32 MACOSX_BUNDLE
        config.hpp config.cpp
        main.hpp main.cpp
        morseaudio.hpp morseaudio.cpp
        version.hpp.in
        windows/about.ui windows/about.hpp windows/about.cpp
        windows/config.ui windows/config.hpp windows/config.cpp
        windows/main.ui windows/main.hpp windows/main.cpp
        icons.rc)

set_target_properties(qmorseaudio
        PROPERTIES
        OUTPUT_NAME qMorseAudio)

target_link_libraries(qmorseaudio PRIVATE
        audio morseino widgets
        Qt::Core Qt::SerialPort Qt::Gui Qt::Widgets Qt::Multimedia Qt::OpenGL Qt::OpenGLWidgets)

if (UNIX)
    set(QMORSEAUDIO_TARGET_INSTALL_DIR ${CMAKE_INSTALL_BINDIR})
else ()
    set(QMORSEAUDIO_TARGET_INSTALL_DIR ".")
endif ()

if (WIN32)
    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/windeployqt)

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(QMORSEAUDIO_DEPLOYQT_TYPE "--debug")
    else ()
        set(QMORSEAUDIO_DEPLOYQT_TYPE "--release")
    endif ()

    add_custom_command(TARGET qmorseaudio
            POST_BUILD COMMAND
            ${QT_DEPLOYQT_BIN} $<TARGET_FILE:qmorseaudio> ${QMORSEAUDIO_DEPLOYQT_TYPE} --dir ${PROJECT_BINARY_DIR}/windeployqt)

    install(DIRECTORY ${PROJECT_BINARY_DIR}/windeployqt/
            DESTINATION ${QMORSEAUDIO_TARGET_INSTALL_DIR} COMPONENT qt_libs)
#elseif (APPLE)
#    set_target_properties(qmorseaudio
#            PROPERTIES
#            MACOSX_BUNDLE_ICON_FILE ../../icons/macos/icon.icns)
#    add_custom_command(TARGET qmorseaudio
#            POST_BUILD COMMAND
#            ${QT_DEPLOYQT_BIN} $<TARGET_FILE:qmorseaudio> ${QMORSEAUDIO_DEPLOYQT_TYPE})
endif ()

install(TARGETS qmorseaudio
        RUNTIME DESTINATION ${QMORSEAUDIO_TARGET_INSTALL_DIR} COMPONENT app_qmorseaudio
        BUNDLE DESTINATION ${QMORSEAUDIO_TARGET_INSTALL_DIR} COMPONENT app_qmorseaudio)
