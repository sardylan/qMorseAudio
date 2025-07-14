/*
 * qMorseAudio
 * Copyright (C) 2025  Luca Cireddu <sardylan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "main.hpp"

#include <iostream>
#include <QtWidgets/QApplication>

#include "morseaudio.hpp"
#include "version.hpp"

morseaudio::morseaudio::MorseAudio *instance;

int main(int argc, char **argv) {
    printHeader();

    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);

    qSetMessagePattern("\x1b[94;1m[\x1b[96;1m%{time yyyy-MM-dd hh:mm:ss.zzz}\x1b[94;1m]\x1b[39;0m "
        "PID:\x1b[31m%{pid}\x1b[39m "
        "TID:\x1b[91m%{threadid}\x1b[39m "
        "["
        "%{if-debug}\x1b[37m DEBUG  \x1b[39m%{endif}"
        "%{if-info}\x1b[92m INFO   \x1b[39m%{endif}"
        "%{if-warning}\x1b[93mWARNING \x1b[39m%{endif}"
        "%{if-critical}\x1b[91mCRITICAL\x1b[39m%{endif}"
        "%{if-fatal}\x1b[91;5m FATAL  \x1b[39;25m%{endif}"
        "]: "
        "%{file}:%{line} "
        "[\x1b[97m%{function}()\x1b[39m] "
        "%{message}");

    QApplication application(argc, argv);

    instance = new morseaudio::morseaudio::MorseAudio(&application);

    QApplication::connect(&application,
                          &QApplication::lastWindowClosed,
                          instance,
                          &morseaudio::morseaudio::MorseAudio::stop);
    QApplication::connect(instance, &morseaudio::morseaudio::MorseAudio::finished, [] { QApplication::quit(); });

    QMetaObject::invokeMethod(instance, &morseaudio::morseaudio::MorseAudio::start);

#ifdef Q_OS_LINUX
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGQUIT, signalHandler);
#endif

#ifdef Q_OS_WINDOWS
    if (SetConsoleCtrlHandler(ctrlHandler, TRUE) != TRUE)
        qWarning() << "Unable to set Control Handler";
#endif

    qInfo() << "Starting application";
    const int result = QApplication::exec();

    delete instance;

    return result;
}


#ifdef Q_OS_LINUX

void signalHandler(int signal) {
    switch (signal) {
        case SIGINT:
        case SIGTERM:
        case SIGQUIT:
            closeApplication();
            break;

        default:
            return;
    }
}

#endif

#ifdef Q_OS_WINDOWS

BOOL WINAPI ctrlHandler(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
        closeApplication();
        return TRUE;

    default:
        return FALSE;
    }
}

#endif

void closeApplication() {
    qInfo() << "Closing application";
    QMetaObject::invokeMethod(instance, &morseaudio::morseaudio::MorseAudio::stop, Qt::QueuedConnection);
}

void printHeader() {
    std::cout << APPLICATION_NAME << " " << APPLICATION_VERSION << std::endl;
    std::cout << "Build at " << APPLICATION_BUILD << std::endl;
#ifdef APPLICATION_GIT_SHA1
    std::cout << "Git SHA1: " << APPLICATION_GIT_SHA1 << std::endl;
#endif
}

void registerMetaTypes() {
}
