if (UNIX)
    include(GNUInstallDirs)
endif ()

set(CPACK_PACKAGE_NAME "${APPLICATION_NAME}")
set(CPACK_PACKAGE_VENDOR "${ORGANIZATION_NAME}")
set(CPACK_PACKAGE_VERSION "${APPLICATION_VERSION}")
set(CPACK_PACKAGE_CONTACT "sardylan@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Morse tone generator for SDR transmission")
set(CPACK_PACKAGE_EXECUTABLES qMorseAudio "qMorseAudio")

#set(CPACK_RESOURCE_FILE_LICENSE "LICENSE.txt")
#set(CPACK_RESOURCE_FILE_README "README.txt")
#set(CPACK_RESOURCE_FILE_WELCOME "WELCOME.txt")

if (UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB")

    execute_process(COMMAND dpkg --print-architecture
            OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)

    execute_process(COMMAND lsb_release --short --codename
            OUTPUT_VARIABLE LSB_DISTRO_CODENAME
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE)

    message(STATUS "Packaging distro: ${LSB_DISTRO_CODENAME}")

    set(CPACK_PACKAGE_FILE_NAME "qmorseaudio-${CPACK_PACKAGE_VERSION}-${LSB_DISTRO_CODENAME}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
elseif (WIN32)
    set(CPACK_GENERATOR "WIX")

    set(CPACK_WIX_UPGRADE_GUID "E6D59A10-31FD-4512-868C-4F86EF50950F")
    set(CPACK_WIX_PROPERTY_ARPHELPLINK "https://github.com/sardylan/qMorseaudio")
    set(CPACK_WIX_LICENSE_RTF ${CMAKE_SOURCE_DIR}/doc/gpl-3.0.rtf)
    set(CPACK_WIX_UI_BANNER ${CMAKE_SOURCE_DIR}/doc/wix-ui-banner.png)
    set(CPACK_WIX_UI_DIALOG ${CMAKE_SOURCE_DIR}/doc/wix-ui-dialog.png)
    #    set(CPACK_WIX_PROPERTY_ARPSIZE "0")

    set(CPACK_WIX_ROOT_FEATURE_TITLE "qMorseAudio")
    set(CPACK_WIX_ROOT_FEATURE_DESCRIPTION "qMorseAudio Application bundle")

    set(CPACK_PACKAGE_INSTALL_DIRECTORY "qMorseAudio")
    set(CPACK_PACKAGE_ICON ../icons/application-256.png)

    set(CPACK_PACKAGE_FILE_NAME "qmorseaudio-${CPACK_PACKAGE_VERSION}")
#elseif (APPLE)
#    #    set(CPACK_GENERATOR "OSXX11")
#    set(CPACK_GENERATOR "Bundle")
#
#    set(CPACK_PACKAGE_FILE_NAME "qmorseaudio-${CPACK_PACKAGE_VERSION}")
endif ()

include(CPack)

cpack_add_component(app_qmorseaudio
        DISPLAY_NAME "Binary"
        DESCRIPTION "Morse tone generator for SDR transmission"
        REQUIRED)

if (WIN32 OR APPLE)
    cpack_add_component(qt_libs
            DISPLAY_NAME "Qt libs"
            DESCRIPTION "Qt libraries"
            REQUIRED)
endif ()
