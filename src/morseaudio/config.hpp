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

#ifndef __MORSEAUDIO__MORSEAUDIO__CONFIG__H
#define __MORSEAUDIO__MORSEAUDIO__CONFIG__H

#include <QtCore/QObject>

#include <audio/config.hpp>
#include <morseino/config.hpp>

#define MORSEAUDIO_CONFIG_GROUP_TX_PARAM "tx"
#define MORSEAUDIO_CONFIG_GROUP_MONITOR_PARAM "monitor"
#define MORSEAUDIO_CONFIG_GROUP_MORSEINO_PARAM "morseino"

#define MORSEAUDIO_CONFIG_AUDIO_DEVICE_ID_PARAM "deviceId"
#define MORSEAUDIO_CONFIG_AUDIO_SAMPLERATE_PARAM "samplerate"
#define MORSEAUDIO_CONFIG_AUDIO_SAMPLE_FORMAT_PARAM "sampleFormat"
#define MORSEAUDIO_CONFIG_AUDIO_CHANNELS_PARAM "channels"
#define MORSEAUDIO_CONFIG_AUDIO_FREQUENCY_PARAM "frequency"
#define MORSEAUDIO_CONFIG_AUDIO_VOLUME_PARAM "volume"

#define MORSEAUDIO_CONFIG_MORSEINO_PORT_NAME_PARAM "portName"

namespace morseaudio::morseaudio {
    class Config final : public QObject {
    public:
        explicit Config(QObject *parent = nullptr);

        ~Config() override;

        [[nodiscard]] audio::Config *getTxAudioConfig() const;

        [[nodiscard]] audio::Config *getMonitorAudioConfig() const;

        [[nodiscard]] morseino::Config *getMorseinoConfig() const;

    public slots:
        void restoreDefault() const;

        void load() const;

        void save() const;

    private:
        audio::Config *txAudioConfig;
        audio::Config *monitorAudioConfig;

        morseino::Config *morseinoConfig;
    };
}

#endif
