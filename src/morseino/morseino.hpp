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

#ifndef __MORSEAUDIO__MORSEINO__MORSEINO__H
#define __MORSEAUDIO__MORSEINO__MORSEINO__H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QThread>

#include <QtSerialPort/QSerialPort>

#include <utilities/thread.hpp>

#include "config.hpp"

#define MORSEINO_CHAR_ON 'X'
#define MORSEINO_CHAR_OFF 'O'

namespace morseaudio::morseino {
    class Morseino final : public QObject {
        Q_OBJECT

    public:
        explicit Morseino(const Config *config, QObject *parent = nullptr);

        ~Morseino() override;

    public slots:
        void updateStatus(bool status);

    private:
        utilities::Thread thread;

        const Config *config;

        QMutex mutex;
        QSerialPort *device;

        void start();

        void stop();

    private slots:
        void readDevice();

    signals:
        void newStatus(bool status);

        void newKey(bool pressed);
    };
}

#endif
