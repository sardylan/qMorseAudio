if (UNIX AND NOT APPLE)
    configure_file(qmorseaudio.desktop.in qmorseaudio.desktop @ONLY)

    install(FILES ${CMAKE_BINARY_DIR}/desktop/qmorseaudio.desktop
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications"
            COMPONENT qmorseaudio)
    install(FILES ../icons/application.svg
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons"
            RENAME "qmorseaudio.svg"
            COMPONENT qmorseaudio)
endif ()