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

#ifndef __MORSEAUDIO__MORSEINO__DEFAULT__H
#define __MORSEAUDIO__MORSEINO__DEFAULT__H

#include <QtSerialPort/QSerialPort>

#ifdef Q_OS_LINUX
#define MORSEINO_PORT_NAME_DEFAULT "ttyACM0"
#elif defined(Q_OS_WIN)
#define MORSEINO_PORT_NAME_DEFAULT "COM3"
#elif defined(Q_OS_MACOS)
#define MORSEINO_PORT_NAME_DEFAULT "tty.usbmodem"
#else
#define MORSEINO_PORT_NAME_DEFAULT ""
#endif

#define MORSEINO_PORT_BAUD_RATE_DEFAULT QSerialPort::Baud115200
#define MORSEINO_PORT_DATA_BITS_DEFAULT QSerialPort::Data8
#define MORSEINO_PORT_PARITY_DEFAULT QSerialPort::NoParity
#define MORSEINO_PORT_STOP_BITS_DEFAULT QSerialPort::OneStop
#define MORSEINO_PORT_FLOW_CONTROL_DEFAULT QSerialPort::NoFlowControl

#endif
