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

#include "audio.hpp"

#include <QtCore/QDebug>

#include <QtMultimedia/QMediaDevices>
#include <QtMultimedia/QAudioDevice>
#include <QtMultimedia/QAudioSink>

#include "default.hpp"

using namespace morseaudio::audio;

Audio::Audio(Config *config, QObject *parent) : QObject(parent),
                                                thread(this, "Audio"),
                                                config(config),
                                                oscillator(nullptr),
                                                audioSink(nullptr),
                                                keyPressed(false) {
}

Audio::~Audio() = default;

void Audio::updateStatus(const bool status) {
    QMutexLocker locker(&mutex);

    if (status) {
        start();
    } else {
        stop();
    }
}

void Audio::updateKeyPressed(const bool keyPressed) {
    this->keyPressed = keyPressed;
    QMetaObject::invokeMethod(this, &Audio::recomputeVolume);
}

void Audio::start() {
    if (oscillator != nullptr || audioSink != nullptr) {
        qWarning() << "Already running";
        stop();
        return;
    }

    qDebug() << "Finding audio device";
    bool found = false;
    QAudioDevice audioDevice;
    for (const QAudioDevice &device: QMediaDevices::audioOutputs()) {
        qDebug() << "Checking device:" << device.id();
        if (device.id() == config->getDeviceId()) {
            audioDevice = device;
            found = true;
            break;
        }
    }
    if (!found) {
        qCritical() << "Audio Device not found";
        stop();
        return;
    }

    qDebug() << "Opening audio device:" << audioDevice.id() << "with name:" << audioDevice.description();

    qDebug() << "Configuring audio format";
    QAudioFormat audioFormat = audioDevice.preferredFormat();
    audioFormat.setSampleRate(config->getSamplerate());
    audioFormat.setSampleFormat(config->getSampleFormat());
    audioFormat.setChannelCount(config->getChannels());
    if (!audioDevice.isFormatSupported(audioFormat)) {
        qCritical() << "Audio Format not supported by device";
        stop();
        return;
    }

    qDebug() << "Creating oscillator";
    oscillator = new Oscillator(audioFormat);
    oscillator->setFrequency(config->getFrequency());
    oscillator->open(QIODeviceBase::ReadOnly);

    qDebug() << "Creating Audio sink";
    audioSink = new QAudioSink(audioDevice, audioFormat);
    audioSink->setBufferSize(config->getBufferSize());
    computeVolumeBasedOnKeyPressed();
    audioSink->start(oscillator);

    QMetaObject::invokeMethod(this, "newStatus", Q_ARG(bool, true));
}

void Audio::stop() {
    if (audioSink != nullptr) {
        audioSink->stop();
        QMetaObject::invokeMethod(audioSink, &QAudioSink::deleteLater);
        audioSink = nullptr;
    }

    if (oscillator != nullptr) {
        oscillator->close();
        QMetaObject::invokeMethod(oscillator, &Oscillator::deleteLater);
        oscillator = nullptr;
    }

    QMetaObject::invokeMethod(this, "newStatus", Q_ARG(bool, false));
}

void Audio::computeVolumeBasedOnKeyPressed() const {
    const qreal volume = this->keyPressed ? config->getVolume() : 0.0;
    qDebug() << "Setting volume to:" << volume;
    audioSink->setVolume(volume);
}

void Audio::onBufferSizeChanged() {
    QMutexLocker locker(&mutex);
    if (audioSink == nullptr)
        return;

    audioSink->setBufferSize(config->getBufferSize());
}

void Audio::onVolumeChanged() {
    QMutexLocker locker(&mutex);
    if (audioSink == nullptr)
        return;

    audioSink->setBufferSize(config->getBufferSize());
}

void Audio::onFrequencyChanged() {
    QMutexLocker locker(&mutex);
    if (oscillator == nullptr)
        return;

    oscillator->setFrequency(config->getFrequency());
}

void Audio::recomputeVolume() {
    QMutexLocker locker(&mutex);
    if (audioSink == nullptr)
        return;

    computeVolumeBasedOnKeyPressed();
}
