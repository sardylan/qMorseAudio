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

#include <QtCore/QSettings>

#include <audio/default.hpp>
#include <morseino/default.hpp>

using namespace morseaudio::morseaudio;

Config::Config(QObject *parent) : QObject(parent),
                                  txAudioConfig(new audio::Config()),
                                  monitorAudioConfig(new audio::Config()),
                                  morseinoConfig(new morseino::Config()) {
    restoreDefault();
    load();
}

Config::~Config() {
    delete morseinoConfig;
    delete monitorAudioConfig;
    delete txAudioConfig;
}

morseaudio::audio::Config *Config::getTxAudioConfig() const {
    return txAudioConfig;
}

morseaudio::audio::Config *Config::getMonitorAudioConfig() const {
    return monitorAudioConfig;
}

morseaudio::morseino::Config *Config::getMorseinoConfig() const {
    return morseinoConfig;
}

void Config::restoreDefault() const {
    txAudioConfig->setDeviceId(AUDIO_DEVICE_ID_DEFAULT);
    txAudioConfig->setSamplerate(AUDIO_SAMPLERATE_DEFAULT);
    txAudioConfig->setSampleFormat(AUDIO_SAMPLE_FORMAT_DEFAULT);
    txAudioConfig->setChannels(AUDIO_CHANNELS_DEFAULT);
    txAudioConfig->setFrequency(AUDIO_FREQUENCY_DEFAULT);
    txAudioConfig->setVolume(AUDIO_VOLUME_DEFAULT);

    monitorAudioConfig->setDeviceId(AUDIO_DEVICE_ID_DEFAULT);
    monitorAudioConfig->setSamplerate(AUDIO_SAMPLERATE_DEFAULT);
    monitorAudioConfig->setSampleFormat(AUDIO_SAMPLE_FORMAT_DEFAULT);
    monitorAudioConfig->setChannels(AUDIO_CHANNELS_DEFAULT);
    monitorAudioConfig->setFrequency(AUDIO_FREQUENCY_DEFAULT);
    monitorAudioConfig->setVolume(AUDIO_VOLUME_DEFAULT);

    morseinoConfig->setPortName(MORSEINO_PORT_NAME_DEFAULT);
}

void Config::load() const {
    QSettings settings;

    settings.beginGroup(MORSEAUDIO_CONFIG_GROUP_TX_PARAM);
    txAudioConfig->setDeviceId(
        settings.value(MORSEAUDIO_CONFIG_AUDIO_DEVICE_ID_PARAM, AUDIO_DEVICE_ID_DEFAULT).toByteArray());
    txAudioConfig->setSamplerate(
        settings.value(MORSEAUDIO_CONFIG_AUDIO_SAMPLERATE_PARAM, AUDIO_SAMPLERATE_DEFAULT).toInt());
    txAudioConfig->setSampleFormat(
        static_cast<QAudioFormat::SampleFormat>(settings.value(
            MORSEAUDIO_CONFIG_AUDIO_SAMPLE_FORMAT_PARAM, AUDIO_SAMPLE_FORMAT_DEFAULT).toInt()));
    txAudioConfig->setChannels(settings.value(MORSEAUDIO_CONFIG_AUDIO_CHANNELS_PARAM, AUDIO_CHANNELS_DEFAULT).toInt());
    txAudioConfig->
            setFrequency(settings.value(MORSEAUDIO_CONFIG_AUDIO_FREQUENCY_PARAM, AUDIO_FREQUENCY_DEFAULT).toInt());
    txAudioConfig->setVolume(settings.value(MORSEAUDIO_CONFIG_AUDIO_VOLUME_PARAM, AUDIO_VOLUME_DEFAULT).toReal());
    settings.endGroup();

    settings.beginGroup(MORSEAUDIO_CONFIG_GROUP_MONITOR_PARAM);
    monitorAudioConfig->setDeviceId(
        settings.value(MORSEAUDIO_CONFIG_AUDIO_DEVICE_ID_PARAM,AUDIO_DEVICE_ID_DEFAULT).toByteArray());
    monitorAudioConfig->setSamplerate(
        settings.value(MORSEAUDIO_CONFIG_AUDIO_SAMPLERATE_PARAM, AUDIO_SAMPLERATE_DEFAULT).toInt());
    monitorAudioConfig->setSampleFormat(
        static_cast<QAudioFormat::SampleFormat>(settings.value(
            MORSEAUDIO_CONFIG_AUDIO_SAMPLE_FORMAT_PARAM, AUDIO_SAMPLE_FORMAT_DEFAULT).toInt()));
    monitorAudioConfig->setChannels(
        settings.value(MORSEAUDIO_CONFIG_AUDIO_CHANNELS_PARAM, AUDIO_CHANNELS_DEFAULT).toInt());
    monitorAudioConfig->setFrequency(
        settings.value(MORSEAUDIO_CONFIG_AUDIO_FREQUENCY_PARAM, AUDIO_FREQUENCY_DEFAULT).toInt());
    monitorAudioConfig->setVolume(settings.value(MORSEAUDIO_CONFIG_AUDIO_VOLUME_PARAM, AUDIO_VOLUME_DEFAULT).toReal());
    settings.endGroup();

    settings.beginGroup(MORSEAUDIO_CONFIG_GROUP_MORSEINO_PARAM);
    morseinoConfig->setPortName(
        settings.value(MORSEAUDIO_CONFIG_MORSEINO_PORT_NAME_PARAM, MORSEINO_PORT_NAME_DEFAULT).toString());
    settings.endGroup();
}

void Config::save() const {
    QSettings settings;

    settings.beginGroup(MORSEAUDIO_CONFIG_GROUP_TX_PARAM);
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_DEVICE_ID_PARAM, txAudioConfig->getDeviceId());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_SAMPLERATE_PARAM, txAudioConfig->getSamplerate());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_SAMPLE_FORMAT_PARAM, txAudioConfig->getSampleFormat());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_CHANNELS_PARAM, txAudioConfig->getChannels());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_FREQUENCY_PARAM, txAudioConfig->getFrequency());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_VOLUME_PARAM, txAudioConfig->getVolume());
    settings.endGroup();

    settings.beginGroup(MORSEAUDIO_CONFIG_GROUP_MONITOR_PARAM);
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_DEVICE_ID_PARAM, monitorAudioConfig->getDeviceId());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_SAMPLERATE_PARAM, monitorAudioConfig->getSamplerate());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_SAMPLE_FORMAT_PARAM, monitorAudioConfig->getSampleFormat());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_CHANNELS_PARAM, monitorAudioConfig->getChannels());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_FREQUENCY_PARAM, monitorAudioConfig->getFrequency());
    settings.setValue(MORSEAUDIO_CONFIG_AUDIO_VOLUME_PARAM, monitorAudioConfig->getVolume());
    settings.endGroup();

    settings.beginGroup(MORSEAUDIO_CONFIG_GROUP_MORSEINO_PARAM);
    settings.setValue(MORSEAUDIO_CONFIG_MORSEINO_PORT_NAME_PARAM, morseinoConfig->getPortName());
    settings.endGroup();
}
