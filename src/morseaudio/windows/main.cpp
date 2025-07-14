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

#include "main.hpp"

#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QDateTime>

#include <QtMultimedia/QMediaDevices>
#include <QtMultimedia/QAudioDevice>

#include <QtGui/QPainter>

#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>

#include <QtWidgets/QMessageBox>

#include <audio/oscillator.hpp>

#include "config.hpp"

using namespace morseaudio::morseaudio::windows;

Main::Main(QWidget *parent): QMainWindow(parent),
                             ui(new Ui::Main()),
                             clockLabel(new QLabel(this)),
                             clockTimer(new QTimer(this)),
                             morseStrip(new widgets::MorseStrip(this)),
                             keyPressedPixmap(MORSEKEY_IMAGE_SIZE,MORSEKEY_IMAGE_SIZE),
                             keyReleasedPixmap(MORSEKEY_IMAGE_SIZE,MORSEKEY_IMAGE_SIZE) {
    ui->setupUi(this);

    ui->morseStripWidget->addWidget(morseStrip);

    preparePixmap(&keyPressedPixmap, Qt::yellow);
    preparePixmap(&keyReleasedPixmap, Qt::gray);

    clockLabel->setText("loading...");
    clockLabel->setAlignment(Qt::AlignRight);
    clockLabel->setFixedWidth(150);
    ui->statusbar->addPermanentWidget(clockLabel);
    clockTimer->setInterval(1000);
    clockTimer->setSingleShot(false);
    connect(clockTimer, &QTimer::timeout, this, &Main::updateStatusBarClock);
    QMetaObject::invokeMethod(this, &Main::updateStatusBarClock);
    QMetaObject::invokeMethod(clockTimer, qOverload<>(&QTimer::start));

    ui->txFrequencySlider->setMinimum(OSCILLATOR_FREQUENCY_MIN);
    ui->txFrequencySlider->setMaximum(OSCILLATOR_FREQUENCY_MAX);
    ui->txFrequencyValue->setMinimum(OSCILLATOR_FREQUENCY_MIN);
    ui->txFrequencyValue->setMaximum(OSCILLATOR_FREQUENCY_MAX);

    ui->txVolumeSlider->setMinimum(0);
    ui->txVolumeSlider->setMaximum(100);
    ui->txVolumeValue->setMinimum(0);
    ui->txVolumeValue->setMaximum(100);

    ui->monitorFrequencySlider->setMinimum(OSCILLATOR_FREQUENCY_MIN);
    ui->monitorFrequencySlider->setMaximum(OSCILLATOR_FREQUENCY_MAX);
    ui->monitorFrequencyValue->setMinimum(OSCILLATOR_FREQUENCY_MIN);
    ui->monitorFrequencyValue->setMaximum(OSCILLATOR_FREQUENCY_MAX);

    ui->monitorVolumeSlider->setMinimum(0);
    ui->monitorVolumeSlider->setMaximum(100);
    ui->monitorVolumeValue->setMinimum(0);
    ui->monitorVolumeValue->setMaximum(100);

    connect(ui->txRunButton, &QPushButton::toggled, [this](const bool checked) {
        ui->txRunButton->setEnabled(false);
        QMetaObject::invokeMethod(this, "newTxStatus", Q_ARG(bool, checked));
    });

    connect(ui->txFrequencySlider, &QSlider::valueChanged, [this](const int value) {
        ui->txFrequencyValue->setValue(value);
        QMetaObject::invokeMethod(this, "newTxFrequency", Q_ARG(int, value));
    });
    connect(ui->txFrequencyValue, &QSpinBox::valueChanged, [this](const int value) {
        ui->txFrequencySlider->setValue(value);
        QMetaObject::invokeMethod(this, "newTxFrequency", Q_ARG(int, value));
    });

    connect(ui->txVolumeSlider, &QSlider::valueChanged, [this](const int value) {
        ui->txVolumeValue->setValue(value);
        QMetaObject::invokeMethod(this, "newTxVolume", Q_ARG(qreal, static_cast<qreal>(value) / 100));
    });
    connect(ui->txVolumeValue, &QSpinBox::valueChanged, [this](const int value) {
        ui->txVolumeSlider->setValue(value);
        QMetaObject::invokeMethod(this, "newTxVolume", Q_ARG(qreal, static_cast<qreal>(value) / 100));
    });

    connect(ui->monitorRunButton, &QPushButton::toggled, [this](const bool checked) {
        ui->monitorRunButton->setEnabled(false);
        QMetaObject::invokeMethod(this, "newMonitorStatus", Q_ARG(bool, checked));
    });

    connect(ui->monitorFrequencySlider, &QSlider::valueChanged, [this](const int value) {
        ui->monitorFrequencyValue->setValue(value);
        QMetaObject::invokeMethod(this, "newMonitorFrequency", Q_ARG(int, value));
    });
    connect(ui->monitorFrequencyValue, &QSpinBox::valueChanged, [this](const int value) {
        ui->monitorFrequencySlider->setValue(value);
        QMetaObject::invokeMethod(this, "newMonitorFrequency", Q_ARG(int, value));
    });

    connect(ui->monitorVolumeSlider, &QSlider::valueChanged, [this](const int value) {
        ui->monitorVolumeValue->setValue(value);
        QMetaObject::invokeMethod(this, "newMonitorVolume", Q_ARG(qreal, static_cast<qreal>(value) / 100));
    });
    connect(ui->monitorVolumeValue, &QSpinBox::valueChanged, [this](const int value) {
        ui->monitorVolumeSlider->setValue(value);
        QMetaObject::invokeMethod(this, "newMonitorVolume", Q_ARG(qreal, static_cast<qreal>(value) / 100));
    });

    connect(ui->morseRunButton, &QPushButton::toggled, [this](const bool checked) {
        ui->morseRunButton->setEnabled(false);
        QMetaObject::invokeMethod(this, "newMorseStatus", Q_ARG(bool, checked));
    });

    connect(ui->actionAbout, &QAction::triggered, this, &Main::showAbout);
    connect(ui->actionConfig, &QAction::triggered, this, &Main::showConfig);
}

Main::~Main() {
    delete ui;
}

void Main::setTxFrequency(const int frequency) const {
    ui->txFrequencyValue->setValue(frequency);
    ui->txFrequencySlider->setValue(frequency);
}

void Main::setTxVolume(const qreal volume) const {
    ui->txVolumeValue->setValue(volume);
    ui->txVolumeSlider->setValue(static_cast<int>(volume * 100));
}

void Main::setMonitorFrequency(const int frequency) const {
    ui->monitorFrequencyValue->setValue(frequency);
    ui->monitorFrequencySlider->setValue(frequency);
}

void Main::setMonitorVolume(const qreal volume) const {
    ui->monitorVolumeValue->setValue(volume);
    ui->monitorVolumeSlider->setValue(static_cast<int>(volume * 100));
}

void Main::showError(const QString &title, const QString &message) {
    QMessageBox::critical(this, title, message);
}

void Main::updateTxDeviceStatus(const bool status) const {
    ui->txRunButton->setChecked(status);
    ui->txRunButton->setEnabled(true);
}

void Main::updateMonitorDeviceStatus(const bool status) const {
    ui->monitorRunButton->setChecked(status);
    ui->monitorRunButton->setEnabled(true);
}

void Main::updateMorseStatus(const bool status) const {
    ui->morseRunButton->setChecked(status);
    ui->morseRunButton->setEnabled(true);

    if (status) {
        morseStrip->start();
    } else {
        morseStrip->stop();
    }
}

void Main::updateKey(const bool pressed) const {
    ui->morseKeyState->setPixmap(pressed ? keyPressedPixmap : keyReleasedPixmap);
    morseStrip->updateKey(pressed);
}

void Main::preparePixmap(QPixmap *pixmap, const QColor color) {
    pixmap->fill(Qt::transparent);

    QPainter painter(pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(color));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, MORSEKEY_IMAGE_SIZE, MORSEKEY_IMAGE_SIZE);
}

void Main::updateStatusBarClock() const {
    clockLabel->setText(QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd HH:mm:ss"));
}
