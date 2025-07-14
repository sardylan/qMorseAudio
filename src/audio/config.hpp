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

#ifndef __MORSEAUDIO__AUDIO__CONFIG__H
#define __MORSEAUDIO__AUDIO__CONFIG__H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QIODevice>

#include <QtMultimedia/QAudioFormat>

namespace morseaudio::audio {
    class Config final : public QObject {
        Q_OBJECT

        Q_PROPERTY(QByteArray deviceId
            READ getDeviceId
            WRITE setDeviceId
            NOTIFY deviceIdChanged)

        Q_PROPERTY(int samplerate
            READ getSamplerate
            WRITE setSamplerate
            NOTIFY samplerateChanged)

        Q_PROPERTY(QAudioFormat::SampleFormat sampleFormat
            READ getSampleFormat
            WRITE setSampleFormat
            NOTIFY sampleFormatChanged)

        Q_PROPERTY(int channels
            READ getChannels
            WRITE setChannels
            NOTIFY channelsChanged)

        Q_PROPERTY(qreal volume
            READ getVolume
            WRITE setVolume
            NOTIFY volumeChanged)

        Q_PROPERTY(int frequency
            READ getFrequency
            WRITE setFrequency
            NOTIFY frequencyChanged)

    public:
        explicit Config(QObject *parent = nullptr);

        ~Config() override;

        [[nodiscard]] QByteArray getDeviceId() const;

        [[nodiscard]] qsizetype getBufferSize() const;

        [[nodiscard]] int getSamplerate() const;

        [[nodiscard]] QAudioFormat::SampleFormat getSampleFormat() const;

        [[nodiscard]] int getChannels() const;

        [[nodiscard]] qreal getVolume() const;

        [[nodiscard]] int getFrequency() const;

    public slots:
        void setDeviceId(const QByteArray &deviceId);

        void setBufferSize(qsizetype bufferSize);

        void setSamplerate(int samplerate);

        void setSampleFormat(QAudioFormat::SampleFormat sampleFormat);

        void setChannels(int channels);

        void setVolume(qreal volume);

        void setFrequency(int frequency);

    private:
        QByteArray deviceId;
        qsizetype bufferSize;
        int samplerate;
        QAudioFormat::SampleFormat sampleFormat;
        int channels;
        qreal volume;
        int frequency;

    signals:
        void deviceIdChanged(const QByteArray &deviceId);

        void bufferSizeChanged(qsizetype bufferSize);

        void samplerateChanged(int samplerate);

        void sampleFormatChanged(QAudioFormat::SampleFormat sampleFormat);

        void channelsChanged(int channels);

        void volumeChanged(qreal volume);

        void frequencyChanged(int frequency);
    };
}

#endif
