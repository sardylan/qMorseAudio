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

#ifndef __MORSEAUDIO__MORSEAUDIO__MAIN__H
#define __MORSEAUDIO__MORSEAUDIO__MAIN__H

#include <QtCore/QtGlobal>

#ifdef Q_OS_LINUX

#include <csignal>

#endif

#ifdef Q_OS_WINDOWS

#include <Windows.h>

#endif

int main(int argc, char** argv);

#ifdef Q_OS_LINUX

void signalHandler(int signal);

#endif

#ifdef Q_OS_WINDOWS

BOOL WINAPI ctrlHandler(DWORD ctrlHandler);

#endif

void closeApplication();

void printHeader();

void registerMetaTypes();

#endif
