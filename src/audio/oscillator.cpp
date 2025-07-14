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

#include "oscillator.hpp"

#include <QtCore/QtDebug>
#include <QtCore/QtMath>

#include "default.hpp"

using namespace morseaudio::audio;

Oscillator::Oscillator(const QAudioFormat &audioFormat, QObject *parent) : QIODevice(parent),
                                                                           thread(this, "Oscillator"),
                                                                           audioFormat(audioFormat),
                                                                           frequency(AUDIO_FREQUENCY_DEFAULT),
                                                                           phase(0),
                                                                           phaseIncrement(0) {
    recomputePulseIncrement();
}

Oscillator::~Oscillator() = default;

int Oscillator::getFrequency() const {
    return frequency;
}

void Oscillator::setFrequency(const int frequency) {
    if (frequency == this->frequency)
        return;
    if (frequency < OSCILLATOR_FREQUENCY_MIN)
        this->frequency = OSCILLATOR_FREQUENCY_MIN;
    else if (frequency > OSCILLATOR_FREQUENCY_MAX)
        this->frequency = OSCILLATOR_FREQUENCY_MAX;
    else
        this->frequency = frequency;

    qDebug() << "Oscillator frequency set to" << frequency << "Hz";

    recomputePulseIncrement();
}

qint64 Oscillator::readData(char *data, qint64 maxlen) {
    if (audioFormat.channelCount() == 0 || audioFormat.bytesPerSample() == 0)
        return 0;

    // qDebug() << "Preparing" << maxlen << "bytes of audio data";

    const qsizetype numberOfSamples = maxlen / audioFormat.channelCount() / audioFormat.bytesPerSample();
    auto samples = generate(numberOfSamples);
    for (qsizetype i = 0; i < numberOfSamples; i++) {
        const auto offset = i * audioFormat.bytesPerSample() * audioFormat.channelCount();
        for (qsizetype c = 0; c < audioFormat.channelCount(); c++) {
            void *dest = data + offset + audioFormat.bytesPerSample() * c;

            switch (audioFormat.sampleFormat()) {
                case QAudioFormat::UInt8: {
                    auto val = static_cast<quint8>(samples[i] * INT_LEAST8_MAX + INT_LEAST8_MAX);
                    memcpy(dest, &val, sizeof(quint8));
                }
                break;

                case QAudioFormat::Int16: {
                    auto val = static_cast<qint16>(samples[i] * INT_LEAST16_MAX);
                    memcpy(dest, &val, sizeof(qint16));
                }
                break;

                case QAudioFormat::Int32: {
                    auto val = static_cast<qint32>(samples[i] * INT_LEAST32_MAX);
                    memcpy(dest, &val, sizeof(qint32));
                }
                break;

                case QAudioFormat::Float: {
                    auto val = static_cast<float>(samples[i]);
                    memcpy(dest, &val, sizeof(float));
                }
                break;

                default:
                    return 0;
            }
        }
    }

    return numberOfSamples * audioFormat.bytesPerSample() * audioFormat.channelCount();
}

qint64 Oscillator::writeData(const char *data, qint64 len) {
    Q_UNUSED(data);
    Q_UNUSED(len);
    return 0;
}

QList<double> Oscillator::generate(const qsizetype numberOfSamples) {
    QList<double> samples;

    for (qsizetype t = 0; t < numberOfSamples; ++t) {
        phase = fmod(phase + phaseIncrement, DOUBLE_M_PI);
        const double val = qSin(phase);
        samples.append(val);
    }

    return samples;
}

void Oscillator::recomputePulseIncrement() {
    this->phaseIncrement = DOUBLE_M_PI * frequency / audioFormat.sampleRate();
    qDebug() << "Phase increment is" << phaseIncrement;
}
