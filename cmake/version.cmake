set(APPLICATION_NAME "Morse Audio")
set(APPLICATION_VERSION "${PROJECT_VERSION}")

set(ORGANIZATION_NAME "The HellNet.org")
set(ORGANIZATION_DOMAIN "thehellnet.org")

if (UNIX)
    execute_process(COMMAND date -u +%Y-%m-%dT%H:%M:%SZ
            OUTPUT_VARIABLE APPLICATION_BUILD
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
elseif (WIN32)
    execute_process(COMMAND powershell -Command "Get-Date -Format 'yyyy-MM-ddTHH:mm:ssZ'"
            OUTPUT_VARIABLE APPLICATION_BUILD
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
else ()
    message(ERROR "Unsupported platform for build date generation")
    set(APPLICATION_BUILD "Unknown")
endif ()

message(STATUS "APPLICATION_BUILD: ${APPLICATION_BUILD}")

execute_process(COMMAND git describe --match=NeVeRmAtCh --always --abbrev=7 --dirty
        OUTPUT_VARIABLE APPLICATION_GIT_SHA1
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "APPLICATION_GIT_SHA1: ${APPLICATION_GIT_SHA1}")
