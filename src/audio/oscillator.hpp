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

#ifndef __MORSEAUDIO__AUDIO__OSCILLATOR__H
#define __MORSEAUDIO__AUDIO__OSCILLATOR__H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QList>
#include <QtCore/QIODevice>

#include <QtMultimedia/QAudioFormat>

#include <utilities/thread.hpp>

#define OSCILLATOR_FREQUENCY_MIN 300
#define OSCILLATOR_FREQUENCY_MAX 3000

namespace morseaudio::audio {
    class Oscillator final : public QIODevice {
        Q_OBJECT

    public:
        explicit Oscillator(const QAudioFormat &audioFormat, QObject *parent = nullptr);

        ~Oscillator() override;

        [[nodiscard]]int getFrequency() const;

        [[nodiscard]] bool isSequential() const override;

        [[nodiscard]] bool atEnd() const override;

        [[nodiscard]] qint64 bytesAvailable() const override;

    public slots:
        void setFrequency(int frequency);

    protected:
        qint64 readData(char *data, qint64 maxlen) override;

        qint64 writeData(const char *data, qint64 len) override;

    private:
        utilities::Thread thread;

        const QAudioFormat audioFormat;
        int frequency;

        double phase;
        double phaseIncrement;

        QList<double> generate(qsizetype numberOfSamples);

        static constexpr double DOUBLE_M_PI = 2.0 * M_PI;

    private slots:
        void recomputePulseIncrement();
    };
}

#endif
