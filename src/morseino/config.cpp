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

using namespace morseaudio::morseino;

Config::Config(QObject *parent) : QObject(parent),
                                  portName(MORSEINO_PORT_NAME_DEFAULT),
                                  baudRate(MORSEINO_PORT_BAUD_RATE_DEFAULT),
                                  dataBits(MORSEINO_PORT_DATA_BITS_DEFAULT),
                                  parity(MORSEINO_PORT_PARITY_DEFAULT),
                                  stopBits(MORSEINO_PORT_STOP_BITS_DEFAULT),
                                  flowControl(MORSEINO_PORT_FLOW_CONTROL_DEFAULT) {
}

Config::~Config() = default;

QString Config::getPortName() const {
    return portName;
}

qint32 Config::getBaudRate() const {
    return baudRate;
}

QSerialPort::DataBits Config::getDataBits() const {
    return dataBits;
}

QSerialPort::Parity Config::getParity() const {
    return parity;
}

QSerialPort::StopBits Config::getStopBits() const {
    return stopBits;
}

QSerialPort::FlowControl Config::getFlowControl() const {
    return flowControl;
}

void Config::setPortName(const QString &portName) {
    if (this->portName == portName)
        return;

    this->portName = portName;
    QMetaObject::invokeMethod(this, "portNameChanged", Q_ARG(QString, this->portName));
}

void Config::setBaudRate(const qint32 baudRate) {
    if (this->baudRate == baudRate)
        return;

    this->baudRate = baudRate;
    QMetaObject::invokeMethod(this, "baudRateChanged", Q_ARG(qint32, this->baudRate));
}

void Config::setDataBits(const QSerialPort::DataBits dataBits) {
    if (this->dataBits == dataBits)
        return;

    this->dataBits = dataBits;
    QMetaObject::invokeMethod(this, "dataBitsChanged", Q_ARG(QSerialPort::DataBits, this->dataBits));
}

void Config::setParity(const QSerialPort::Parity parity) {
    if (this->parity == parity)
        return;

    this->parity = parity;
    QMetaObject::invokeMethod(this, "parityChanged", Q_ARG(QSerialPort::Parity, this->parity));
}

void Config::setStopBits(const QSerialPort::StopBits stopBits) {
    if (this->stopBits == stopBits)
        return;

    this->stopBits = stopBits;
    QMetaObject::invokeMethod(this, "stopBitsChanged", Q_ARG(QSerialPort::StopBits, this->stopBits));
}

void Config::setFlowControl(const QSerialPort::FlowControl flowControl) {
    if (this->flowControl == flowControl)
        return;

    this->flowControl = flowControl;
    QMetaObject::invokeMethod(this, "flowControlChanged", Q_ARG(QSerialPort::FlowControl, this->flowControl));
}
