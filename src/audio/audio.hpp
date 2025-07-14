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

#ifndef __MORSEAUDIO__AUDIO__AUDIO__H
#define __MORSEAUDIO__AUDIO__AUDIO__H

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QByteArray>
#include <QtCore/QThread>

#include <QtMultimedia/QAudioSink>

#include <utilities/thread.hpp>

#include "config.hpp"
#include "oscillator.hpp"

namespace morseaudio::audio {
    class Audio final : public QObject {
        Q_OBJECT

    public:
        explicit Audio(Config *config, QObject *parent = nullptr);

        ~Audio() override;

    public slots:
        void updateStatus(bool status);

        void updateKeyPressed(bool keyPressed);

    private:
        utilities::Thread thread;

        Config *config;

        QMutex mutex;
        Oscillator *oscillator;
        QAudioSink *audioSink;

        bool keyPressed;

        void start();

        void stop();

        void computeVolumeBasedOnKeyPressed() const;

    private slots:
        void onBufferSizeChanged();

        void onVolumeChanged();

        void onFrequencyChanged();

        void recomputeVolume();

    signals:
        void newStatus(bool status);
    };
}

#endif
