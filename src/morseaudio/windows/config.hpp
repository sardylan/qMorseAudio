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

#ifndef __MORSEAUDIO__MORSEAUDIO__WINDOWS__CONFIG__H
#define __MORSEAUDIO__MORSEAUDIO__WINDOWS__CONFIG__H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <QtMultimedia/QAudioDevice>

#include <QtWidgets/QDialog>

#include "../config.hpp"

#include "ui_config.h"

namespace morseaudio::morseaudio::windows {
    class Config final : public QDialog {
        Q_OBJECT

    public:
        explicit Config(morseaudio::Config *config, QWidget *parent = nullptr);

        ~Config() override;

    public slots:
        int exec() override;

    private:
        Ui::Config *ui;

        morseaudio::Config *config;

        [[nodiscard]] bool isConfigChanged() const;

        static void updateDeviceWidgets(const QComboBox *deviceValue,
                                        QComboBox *samplerateValue,
                                        QComboBox *audioFormatValue,
                                        QComboBox *channelsValue);

        static QList<int> getSupportedSamplerates(const QAudioDevice &device);

        static QString samplerateToString(const int &samplerate);

        static QString sampleFormatToString(const QAudioFormat::SampleFormat &format);

        static QString channelsToString(const int &channels);

        static void selectOrAddItem(QComboBox *comboBox, const QVariant &itemData);

        static int findItem(const QComboBox *comboBox, const QVariant &itemData);

        static void prepareBufferSizeValues(QComboBox *comboBox);

    private slots:
        void updateTxDeviceParams() const;

        void updateMonitorDeviceParams() const;

        void updateButtonEnabledState() const;

        void configLoad();

        void configSave() const;

        void configDefault();
    };
}

#endif
