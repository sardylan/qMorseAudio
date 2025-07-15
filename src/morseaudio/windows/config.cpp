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

#include <QtMultimedia/QMediaDevices>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>

#include <audio/config.hpp>
#include <audio/default.hpp>
#include <morseino/config.hpp>
#include <morseino/default.hpp>

using namespace morseaudio::morseaudio::windows;

Config::Config(morseaudio::Config *config, QWidget *parent): QDialog(parent),
                                                             ui(new Ui::Config()),
                                                             config(config) {
    ui->setupUi(this);

    prepareBufferSizeValues(ui->txBufferSizeValue);
    prepareBufferSizeValues(ui->monitorBufferSizeValue);

    connect(ui->txDeviceValue, &QComboBox::currentIndexChanged, this, &Config::updateTxDeviceParams);
    connect(ui->monitorDeviceValue, &QComboBox::currentIndexChanged, this, &Config::updateMonitorDeviceParams);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, [this] {
        QMetaObject::invokeMethod(this, &Config::configSave);
        QMetaObject::invokeMethod(this, &Config::updateButtonEnabledState);
        QMetaObject::invokeMethod(this, &Config::close);
    });

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, [this] {
        QMetaObject::invokeMethod(this, &Config::configSave);
        QMetaObject::invokeMethod(this, &Config::updateButtonEnabledState);
    });

    connect(ui->buttonBox->button(QDialogButtonBox::Close), &QPushButton::clicked, [this] {
        if (isConfigChanged()
            && QMessageBox::question(this,
                                     tr("Close config?"),
                                     tr("Are you sure you want to close config without saving?"))
            != QMessageBox::Yes)
            return;

        QMetaObject::invokeMethod(this, &Config::close);
    });

    connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked, [this] {
        if (QMessageBox::question(this,
                                  tr("Reset config?"),
                                  tr("Are you sure you want to reset the config?"))
            != QMessageBox::Yes)
            return;

        QMetaObject::invokeMethod(this, &Config::configLoad);
    });

    connect(ui->buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, [this] {
        if (QMessageBox::question(this,
                                  tr("Restore defaults?"),
                                  tr("Are you sure you want to restore default settings?"))
            != QMessageBox::Yes)
            return;

        QMetaObject::invokeMethod(this, &Config::configDefault);
    });

    connect(ui->txDeviceValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->txBufferSizeValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->txSamplerateValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->txFormatValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->txChannelsValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);

    connect(ui->monitorDeviceValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->monitorBufferSizeValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->monitorSamplerateValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->monitorFormatValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
    connect(ui->monitorChannelsValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);

    connect(ui->morseinoSerialPortValue, &QComboBox::currentIndexChanged, this, &Config::updateButtonEnabledState);
}

Config::~Config() {
    delete ui;
}

int Config::exec() {
    configLoad();
    return QDialog::exec();
}

bool Config::isConfigChanged() const {
    return config->getTxAudioConfig()->getDeviceId() != ui->txDeviceValue->currentData().toString()
           || config->getTxAudioConfig()->getBufferSize() != ui->txBufferSizeValue->currentData().toInt()
           || config->getTxAudioConfig()->getSamplerate() != ui->txSamplerateValue->currentData().toInt()
           || config->getTxAudioConfig()->getSampleFormat() != ui->txFormatValue->currentData().value<
               QAudioFormat::SampleFormat>()
           || config->getTxAudioConfig()->getChannels() != ui->txChannelsValue->currentData().toInt()

           || config->getMonitorAudioConfig()->getDeviceId() != ui->monitorDeviceValue->currentData().toString()
           || config->getMonitorAudioConfig()->getBufferSize() != ui->monitorBufferSizeValue->currentData().toInt()
           || config->getMonitorAudioConfig()->getSamplerate() != ui->monitorSamplerateValue->currentData().toInt()
           || config->getMonitorAudioConfig()->getSampleFormat() != ui->monitorFormatValue->currentData().value<
               QAudioFormat::SampleFormat>()
           || config->getMonitorAudioConfig()->getChannels() != ui->monitorChannelsValue->currentData().toInt()

           || config->getMorseinoConfig()->getPortName() != ui->morseinoSerialPortValue->currentData().toString();
}

void Config::updateTxDeviceParams() const {
    updateDeviceWidgets(ui->txDeviceValue,
                        ui->txSamplerateValue,
                        ui->txFormatValue,
                        ui->txChannelsValue);
}

void Config::updateMonitorDeviceParams() const {
    updateDeviceWidgets(ui->monitorDeviceValue,
                        ui->monitorSamplerateValue,
                        ui->monitorFormatValue,
                        ui->monitorChannelsValue);
}

void Config::updateButtonEnabledState() const {
    const bool changed = isConfigChanged();
    ui->buttonBox->button(QDialogButtonBox::Reset)->setEnabled(changed);
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(changed);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(changed);
}

void Config::configLoad() {
    qInfo() << "Resetting interface";

    ui->txDeviceValue->clear();
    ui->txSamplerateValue->clear();
    ui->txFormatValue->clear();
    ui->txChannelsValue->clear();

    ui->monitorDeviceValue->clear();
    ui->monitorSamplerateValue->clear();
    ui->monitorFormatValue->clear();
    ui->monitorChannelsValue->clear();

    for (const QAudioDevice &device: QMediaDevices::audioOutputs()) {
        QString itemText = device.description();
        QByteArray itemData = device.id();
        qDebug() << itemText << "|" << itemData;
        ui->txDeviceValue->addItem(itemText, itemData);
        ui->monitorDeviceValue->addItem(itemText, itemData);
    }

    selectOrAddItem(ui->txDeviceValue, config->getTxAudioConfig()->getDeviceId());
    selectOrAddItem(ui->txBufferSizeValue, config->getTxAudioConfig()->getBufferSize());
    QMetaObject::invokeMethod(this, &Config::updateTxDeviceParams);
    selectOrAddItem(ui->txSamplerateValue, config->getTxAudioConfig()->getSamplerate());
    selectOrAddItem(ui->txFormatValue, config->getTxAudioConfig()->getSampleFormat());
    selectOrAddItem(ui->txChannelsValue, config->getTxAudioConfig()->getChannels());

    selectOrAddItem(ui->monitorDeviceValue, config->getMonitorAudioConfig()->getDeviceId());
    selectOrAddItem(ui->monitorBufferSizeValue, config->getMonitorAudioConfig()->getBufferSize());
    QMetaObject::invokeMethod(this, &Config::updateMonitorDeviceParams);
    selectOrAddItem(ui->monitorSamplerateValue, config->getMonitorAudioConfig()->getSamplerate());
    selectOrAddItem(ui->monitorFormatValue, config->getMonitorAudioConfig()->getSampleFormat());
    selectOrAddItem(ui->monitorChannelsValue, config->getMonitorAudioConfig()->getChannels());

    ui->morseinoSerialPortValue->clear();
    for (const QSerialPortInfo &portInfo: QSerialPortInfo::availablePorts()) {
        qDebug() << "Adding serial port:" << portInfo.portName() << "|" << portInfo.description();
        ui->morseinoSerialPortValue->addItem(portInfo.portName(), portInfo.portName());
    }

    selectOrAddItem(ui->morseinoSerialPortValue, config->getMorseinoConfig()->getPortName());
}

void Config::configSave() const {
    config->getTxAudioConfig()->setDeviceId(ui->txDeviceValue->currentData().toByteArray());
    config->getTxAudioConfig()->setBufferSize(ui->txBufferSizeValue->currentData().toLongLong());
    config->getTxAudioConfig()->setSamplerate(ui->txSamplerateValue->currentData().toInt());
    config->getTxAudioConfig()->setSampleFormat(ui->txFormatValue->currentData().value<QAudioFormat::SampleFormat>());
    config->getTxAudioConfig()->setChannels(ui->txChannelsValue->currentData().toInt());

    config->getMonitorAudioConfig()->setDeviceId(ui->monitorDeviceValue->currentData().toByteArray());
    config->getMonitorAudioConfig()->setBufferSize(ui->monitorBufferSizeValue->currentData().toLongLong());
    config->getMonitorAudioConfig()->setSamplerate(ui->monitorSamplerateValue->currentData().toInt());
    config->getMonitorAudioConfig()->setSampleFormat(
        ui->monitorFormatValue->currentData().value<QAudioFormat::SampleFormat>());
    config->getMonitorAudioConfig()->setChannels(ui->monitorChannelsValue->currentData().toInt());

    config->getMorseinoConfig()->setPortName(ui->morseinoSerialPortValue->currentData().toString());

    QMetaObject::invokeMethod(config, &morseaudio::Config::save);
}

void Config::configDefault() {
    qInfo() << "Setting interface to default values";

    selectOrAddItem(ui->txDeviceValue, AUDIO_DEVICE_ID_DEFAULT);
    selectOrAddItem(ui->txBufferSizeValue, AUDIO_BUFFER_SIZE_DEFAULT);
    QMetaObject::invokeMethod(this, &Config::updateTxDeviceParams);
    selectOrAddItem(ui->txSamplerateValue, AUDIO_SAMPLERATE_DEFAULT);
    selectOrAddItem(ui->txFormatValue, AUDIO_SAMPLE_FORMAT_DEFAULT);
    selectOrAddItem(ui->txChannelsValue, AUDIO_CHANNELS_DEFAULT);

    selectOrAddItem(ui->monitorDeviceValue, AUDIO_DEVICE_ID_DEFAULT);
    selectOrAddItem(ui->monitorBufferSizeValue, AUDIO_BUFFER_SIZE_DEFAULT);
    QMetaObject::invokeMethod(this, &Config::updateMonitorDeviceParams);
    selectOrAddItem(ui->monitorSamplerateValue, AUDIO_SAMPLERATE_DEFAULT);
    selectOrAddItem(ui->monitorFormatValue, AUDIO_SAMPLE_FORMAT_DEFAULT);
    selectOrAddItem(ui->monitorChannelsValue, AUDIO_CHANNELS_DEFAULT);

    selectOrAddItem(ui->morseinoSerialPortValue, MORSEINO_PORT_NAME_DEFAULT);
}

void Config::updateDeviceWidgets(const QComboBox *deviceValue,
                                 QComboBox *samplerateValue,
                                 QComboBox *audioFormatValue,
                                 QComboBox *channelsValue) {
    samplerateValue->clear();
    audioFormatValue->clear();
    channelsValue->clear();

    const QByteArray deviceId = deviceValue->currentData().toByteArray();

    for (const QAudioDevice &device: QMediaDevices::audioOutputs()) {
        if (device.id() != deviceId)
            continue;

        for (const int sampleRate: getSupportedSamplerates(device)) {
            samplerateValue->addItem(samplerateToString(sampleRate), sampleRate);
        }

        for (const QAudioFormat::SampleFormat format: device.supportedSampleFormats()) {
            audioFormatValue->addItem(sampleFormatToString(format), format);
        }

        for (int c = device.minimumChannelCount(); c <= device.maximumChannelCount(); c++) {
            channelsValue->addItem(channelsToString(c), c);
        }

        break;
    }
}

QList<int> Config::getSupportedSamplerates(const QAudioDevice &device) {
    qInfo() << "Getting supported Sample Rates for device" << device.description();

    QList<int> testSampleRates;
    testSampleRates.append(8000);
    testSampleRates.append(16000);
    testSampleRates.append(22050);
    testSampleRates.append(44100);
    testSampleRates.append(48000);
    testSampleRates.append(96000);
    testSampleRates.append(192000);

    QList<int> sampleRates;

    for (const int sampleRate: testSampleRates) {
        QAudioFormat format;
        format.setChannelCount(2);
        format.setSampleFormat(QAudioFormat::Int16);
        format.setSampleRate(sampleRate);
        if (!device.isFormatSupported(format))
            continue;

        qDebug() << sampleRate << "Hz is supported.";
        sampleRates.append(sampleRate);
    }

    return sampleRates;
}

QString Config::samplerateToString(const int &samplerate) {
    return QString("%1 Hz").arg(samplerate);
}

QString Config::sampleFormatToString(const QAudioFormat::SampleFormat &format) {
    switch (format) {
        case QAudioFormat::Unknown:
            return "Unknown";
        case QAudioFormat::UInt8:
            return "Unsigned 8-bit";
        case QAudioFormat::Int16:
            return "Signed 16-bit";
        case QAudioFormat::Int32:
            return "Signed 32-bit";
        case QAudioFormat::Float:
            return "Float 32-bit";
        case QAudioFormat::NSampleFormats:
            return "NSampleFormats";
        default:
            return "Not implemented";
    }
}

QString Config::channelsToString(const int &channels) {
    switch (channels) {
        case 1:
            return "1 (Mono)";
        case 2:
            return "2 (Stereo)";
        default:
            return QString::number(channels);
    }
}

void Config::selectOrAddItem(QComboBox *comboBox, const QVariant &itemData) {
    qInfo() << "Selecting or adding item to combobox:" << itemData;

    int idx = findItem(comboBox, itemData);
    if (idx == -1) {
        qDebug() << "Data not present, adding item";
        comboBox->addItem(itemData.toString(), itemData);
    }

    idx = findItem(comboBox, itemData);

    qDebug() << "Item is idx" << idx;
    comboBox->setCurrentIndex(idx);
}

int Config::findItem(const QComboBox *comboBox, const QVariant &itemData) {
    qDebug() << "Finding if itemData is already present in an item";
    for (int i = 0; i < comboBox->count(); i++) {
        qDebug() << "Checking if" << comboBox->itemData(i) << "==" << itemData;
        if (comboBox->itemData(i) == itemData) {
            qDebug() << "Data present in item" << i;
            return i;
        }
    }

    qDebug() << "Not found";
    return -1;
}

void Config::prepareBufferSizeValues(QComboBox *comboBox) {
    comboBox->clear();
    comboBox->addItem("128 bytes", 128);
    comboBox->addItem("256 bytes", 256);
    comboBox->addItem("512 bytes", 512);
    comboBox->addItem("1 kB (1024 bytes)", 1024);
    comboBox->addItem("2 kB (2048 bytes)", 2048);
    comboBox->addItem("4 kB (4096 bytes)", 4096);
    comboBox->addItem("8 kB (8192 bytes)", 8192);
    comboBox->addItem("16 kB (16384 bytes)", 16384);
    comboBox->addItem("32 kB (32768 bytes)", 32768);
    comboBox->addItem("64 kB (65536 bytes)", 65536);
    comboBox->addItem("128 kB (131072 bytes)", 131072);
    comboBox->addItem("256 kB (262144 bytes)", 262144);
    comboBox->addItem("512 kB (524288 bytes)", 524288);
}
