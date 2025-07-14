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

#ifndef __MORSEAUDIO__MORSEINO__CONFIG__H
#define __MORSEAUDIO__MORSEINO__CONFIG__H

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtSerialPort/QSerialPort>

namespace morseaudio::morseino {
    class Config final : public QObject {
        Q_OBJECT

        Q_PROPERTY(QString portName
            READ getPortName
            WRITE setPortName
            NOTIFY portNameChanged)

        Q_PROPERTY(qint32 baudRate
            READ getBaudRate
            WRITE setBaudRate
            NOTIFY baudRateChanged)

        Q_PROPERTY(QSerialPort::DataBits dataBits
            READ getDataBits
            WRITE setDataBits
            NOTIFY dataBitsChanged)

        Q_PROPERTY(QSerialPort::Parity parity
            READ getParity
            WRITE setParity
            NOTIFY parityChanged)

        Q_PROPERTY(QSerialPort::StopBits stopBits
            READ getStopBits
            WRITE setStopBits
            NOTIFY stopBitsChanged)

        Q_PROPERTY(QSerialPort::FlowControl flowControl
            READ getFlowControl
            WRITE setFlowControl
            NOTIFY flowControlChanged)

    public:
        explicit Config(QObject *parent = nullptr);

        ~Config() override;

        [[nodiscard]] QString getPortName() const;

        [[nodiscard]] qint32 getBaudRate() const;

        [[nodiscard]] QSerialPort::DataBits getDataBits() const;

        [[nodiscard]] QSerialPort::Parity getParity() const;

        [[nodiscard]] QSerialPort::StopBits getStopBits() const;

        [[nodiscard]] QSerialPort::FlowControl getFlowControl() const;

    public slots:
        void setPortName(const QString &portName);

        void setBaudRate(qint32 baudRate);

        void setDataBits(QSerialPort::DataBits dataBits);

        void setParity(QSerialPort::Parity parity);

        void setStopBits(QSerialPort::StopBits stopBits);

        void setFlowControl(QSerialPort::FlowControl flowControl);

    private:
        QString portName;
        qint32 baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;

    signals:
        void portNameChanged(const QString &portName);

        void baudRateChanged(qint32 baudRate);

        void dataBitsChanged(QSerialPort::DataBits dataBits);

        void parityChanged(QSerialPort::Parity parity);

        void stopBitsChanged(QSerialPort::StopBits stopBits);

        void flowControlChanged(QSerialPort::FlowControl flowControl);
    };
}

#endif
