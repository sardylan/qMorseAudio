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

#include "config.hpp"
#include "default.hpp"
#include "oscillator.hpp"

using namespace morseaudio::audio;

Config::Config(QObject *parent) : QObject(parent),
                                  bufferSize(512),
                                  samplerate(AUDIO_SAMPLERATE_DEFAULT),
                                  sampleFormat(AUDIO_SAMPLE_FORMAT_DEFAULT),
                                  channels(AUDIO_CHANNELS_DEFAULT),
                                  volume(AUDIO_VOLUME_DEFAULT),
                                  frequency(AUDIO_FREQUENCY_DEFAULT) {
}

Config::~Config() = default;

QByteArray Config::getDeviceId() const {
    return deviceId;
}

qsizetype Config::getBufferSize() const {
    return bufferSize;
}

int Config::getSamplerate() const {
    return samplerate;
}

QAudioFormat::SampleFormat Config::getSampleFormat() const {
    return sampleFormat;
}

int Config::getChannels() const {
    return channels;
}

int Config::getFrequency() const {
    return frequency;
}

qreal Config::getVolume() const {
    return volume;
}

void Config::setDeviceId(const QByteArray &deviceId) {
    if (this->deviceId == deviceId)
        return;

    this->deviceId = deviceId;
    QMetaObject::invokeMethod(this, "deviceIdChanged", Q_ARG(QByteArray, deviceId));
}

void Config::setBufferSize(qsizetype bufferSize) {
    if (this->bufferSize == bufferSize)
        return;

    this->bufferSize = bufferSize;
    QMetaObject::invokeMethod(this, "bufferSizeChanged", Q_ARG(qsizetype, bufferSize));
}

void Config::setSamplerate(const int samplerate) {
    if (this->samplerate == samplerate)
        return;

    this->samplerate = samplerate;
    QMetaObject::invokeMethod(this, "samplerateChanged", Q_ARG(int, samplerate));
}

void Config::setSampleFormat(const QAudioFormat::SampleFormat sampleFormat) {
    if (this->sampleFormat == sampleFormat)
        return;

    this->sampleFormat = sampleFormat;
    QMetaObject::invokeMethod(this, "sampleFormatChanged", Q_ARG(QAudioFormat::SampleFormat, sampleFormat));
}

void Config::setChannels(const int channels) {
    if (this->channels == channels)
        return;

    this->channels = channels;
    QMetaObject::invokeMethod(this, "channelsChanged", Q_ARG(int, channels));
}

void Config::setFrequency(const int frequency) {
    if (this->frequency == frequency)
        return;

    if (frequency < OSCILLATOR_FREQUENCY_MIN)
        this->frequency = OSCILLATOR_FREQUENCY_MIN;
    else if (frequency > OSCILLATOR_FREQUENCY_MAX)
        this->frequency = OSCILLATOR_FREQUENCY_MAX;
    else
        this->frequency = frequency;

    QMetaObject::invokeMethod(this, "frequencyChanged", Q_ARG(int, frequency));
}

void Config::setVolume(const qreal volume) {
    if (this->volume == volume)
        return;

    this->volume = volume;
    QMetaObject::invokeMethod(this, "volumeChanged", Q_ARG(qreal, volume));
}
