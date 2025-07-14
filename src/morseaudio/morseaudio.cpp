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

#include "morseaudio.hpp"

#include <QtWidgets/QApplication>

using namespace morseaudio::morseaudio;

MorseAudio::MorseAudio(QObject *parent): QObject(parent),
                                         config(new Config()),
                                         txAudio(new audio::Audio(config->getTxAudioConfig())),
                                         monitorAudio(new audio::Audio(config->getMonitorAudioConfig())),
                                         morseino(new morseino::Morseino(config->getMorseinoConfig())),
                                         mainWindow(new windows::Main()),
                                         configWindow(new windows::Config(config)),
                                         aboutWindow(new windows::About()) {
    connect(mainWindow, &windows::Main::showConfig, configWindow, &windows::Config::exec);
    connect(mainWindow, &windows::Main::showAbout, aboutWindow, &windows::About::exec);

    connect(mainWindow, &windows::Main::newTxStatus, txAudio, &audio::Audio::updateStatus);
    connect(mainWindow, &windows::Main::newTxFrequency, config->getTxAudioConfig(), &audio::Config::setFrequency);
    connect(mainWindow, &windows::Main::newTxVolume, config->getTxAudioConfig(), &audio::Config::setVolume);

    connect(mainWindow, &windows::Main::newMonitorStatus, monitorAudio, &audio::Audio::updateStatus);
    connect(mainWindow, &windows::Main::newMonitorFrequency, config->getMonitorAudioConfig(),
            &audio::Config::setFrequency);
    connect(mainWindow, &windows::Main::newMonitorVolume, config->getMonitorAudioConfig(), &audio::Config::setVolume);

    connect(mainWindow, &windows::Main::newMorseStatus, morseino, &morseino::Morseino::updateStatus);

    connect(mainWindow, &windows::Main::newTxFrequency, config, &Config::save);
    connect(mainWindow, &windows::Main::newTxVolume, config, &Config::save);

    connect(mainWindow, &windows::Main::newMonitorFrequency, config, &Config::save);
    connect(mainWindow, &windows::Main::newMonitorVolume, config, &Config::save);

    connect(txAudio, &audio::Audio::newStatus, mainWindow, &windows::Main::updateTxDeviceStatus);
    connect(monitorAudio, &audio::Audio::newStatus, mainWindow, &windows::Main::updateMonitorDeviceStatus);

    connect(morseino, &morseino::Morseino::newStatus, mainWindow, &windows::Main::updateMorseStatus);
    connect(morseino, &morseino::Morseino::newKey, txAudio, &audio::Audio::updateKeyPressed);
    connect(morseino, &morseino::Morseino::newKey, monitorAudio, &audio::Audio::updateKeyPressed);
    connect(morseino, &morseino::Morseino::newKey, mainWindow, &windows::Main::updateKey);
}

MorseAudio::~MorseAudio() {
    delete config;
};

void MorseAudio::start() {
    qInfo() << "Starting MorseAudio";
    QMetaObject::invokeMethod(config, &Config::load);

    mainWindow->setTxFrequency(config->getTxAudioConfig()->getFrequency());
    mainWindow->setTxVolume(config->getTxAudioConfig()->getVolume());
    mainWindow->setMonitorFrequency(config->getMonitorAudioConfig()->getFrequency());
    mainWindow->setMonitorVolume(config->getMonitorAudioConfig()->getVolume());
    QMetaObject::invokeMethod(mainWindow, &windows::Main::show);
}

void MorseAudio::stop() {
    qInfo() << "Stopping MorseAudio";

    QMetaObject::invokeMethod(txAudio, "updateStatus", Qt::BlockingQueuedConnection, Q_ARG(bool, false));
    QMetaObject::invokeMethod(monitorAudio, "updateStatus", Qt::BlockingQueuedConnection,Q_ARG(bool, false));

    QMetaObject::invokeMethod(morseino, "updateStatus", Qt::BlockingQueuedConnection,Q_ARG(bool, false));

    QMetaObject::invokeMethod(aboutWindow, &windows::Config::hide);
    QMetaObject::invokeMethod(configWindow, &windows::Config::hide);
    QMetaObject::invokeMethod(mainWindow, &windows::Main::hide);

    QMetaObject::invokeMethod(config, &Config::save);

    QMetaObject::invokeMethod(this, &MorseAudio::finished);
}
