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

#ifndef __MORSEAUDIO__MORSEAUDIO__MORSEAUDIO__H
#define __MORSEAUDIO__MORSEAUDIO__MORSEAUDIO__H

#include <QtCore/QObject>

#include <audio/audio.hpp>
#include <morseino/morseino.hpp>

#include "config.hpp"

#include "windows/main.hpp"
#include "windows/config.hpp"
#include "windows/about.hpp"

namespace morseaudio::morseaudio {
    class MorseAudio final : public QObject {
        Q_OBJECT

    public:
        explicit MorseAudio(QObject *parent = nullptr);

        ~MorseAudio() override;

    public slots:
        void start();

        void stop();

    private:
        Config *config;

        audio::Audio *txAudio;
        audio::Audio *monitorAudio;

        morseino::Morseino *morseino;

        windows::Main *mainWindow;
        windows::Config *configWindow;
        windows::About *aboutWindow;

    signals:
        void finished();
    };
}

#endif
