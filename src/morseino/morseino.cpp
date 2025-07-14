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

#include "morseino.hpp"

#include <QtCore/QDebug>
#include <QtCore/QMutexLocker>

using namespace morseaudio::morseino;

Morseino::Morseino(const Config *config, QObject *parent) : QObject(parent),
                                                            thread(this, "Morseino"),
                                                            config(config),
                                                            device(nullptr) {
}

Morseino::~Morseino() = default;

void Morseino::updateStatus(const bool status) {
    QMutexLocker locker(&mutex);

    if (status)
        start();
    else
        stop();
}

void Morseino::start() {
    if (device != nullptr) {
        qCritical() << "Device is already open";
        return;
    }

    device = new QSerialPort();
    device->setPortName(config->getPortName());
    device->setBaudRate(config->getBaudRate());
    device->setDataBits(config->getDataBits());
    device->setParity(config->getParity());
    device->setStopBits(config->getStopBits());
    device->setFlowControl(config->getFlowControl());

    connect(device, &QIODevice::readyRead, this, &Morseino::readDevice);

    qDebug() << "Opening Device:" << device->portName();

    if (!device->open(QIODevice::ReadWrite)) {
        qCritical() << "Failed to open Device:" << device->errorString();
        stop();
        return;
    }

    QMetaObject::invokeMethod(this, "newStatus", Qt::QueuedConnection, Q_ARG(bool, true));
}

void Morseino::stop() {
    if (device != nullptr) {
        qDebug() << "Closing Device:" << device->portName();

        device->close();
        device = nullptr;
    }

    QMetaObject::invokeMethod(this, "newStatus", Qt::QueuedConnection, Q_ARG(bool, false));
}

void Morseino::readDevice() {
    QMutexLocker locker(&mutex);
    if (device == nullptr) {
        qCritical() << "Device is already closed";
        return;
    }

    qDebug() << "Reading from device";

    char c;

    while (device->bytesAvailable()) {
        if (!device->getChar(&c)) {
            qCritical() << "Failed to read from Device:" << device->errorString();
            return;
        }

        switch (c) {
            case MORSEINO_CHAR_ON:
                QMetaObject::invokeMethod(this, "newKey", Qt::QueuedConnection, Q_ARG(bool, true));
                break;

            case MORSEINO_CHAR_OFF:
                QMetaObject::invokeMethod(this, "newKey", Qt::QueuedConnection, Q_ARG(bool, false));
                break;

            default:
                qWarning() << "Command not recognized:" << c;
        }
    }
}
