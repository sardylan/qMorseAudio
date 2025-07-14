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

#ifndef __MORSEAUDIO__MORSEAUDIO__WINDOWS__MAIN__H
#define __MORSEAUDIO__MORSEAUDIO__WINDOWS__MAIN__H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include <QtMultimedia/QAudioDevice>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>

#include <QtGui/QPixmap>

#include <widgets/morse_strip.hpp>

#include "ui_main.h"

#define MORSEKEY_IMAGE_SIZE 32

namespace morseaudio::morseaudio::windows {
    class Main final : public QMainWindow {
        Q_OBJECT

    public:
        explicit Main(QWidget *parent = nullptr);

        ~Main() override;

    public slots:
        void setTxFrequency(int frequency) const;

        void setTxVolume(qreal volume) const;

        void setMonitorFrequency(int frequency) const;

        void setMonitorVolume(qreal volume) const;

        void showError(const QString &title, const QString &message);

        void updateTxDeviceStatus(bool status) const;

        void updateMonitorDeviceStatus(bool status) const;

        void updateMorseStatus(bool status) const;

        void updateKey(bool pressed) const;

    private:
        Ui::Main *ui;

        QLabel *clockLabel;
        QTimer *clockTimer;

        widgets::MorseStrip *morseStrip;

        QPixmap keyPressedPixmap;
        QPixmap keyReleasedPixmap;

        static void preparePixmap(QPixmap *pixmap, QColor color);

    private slots:
        void updateStatusBarClock() const;

    signals:
        void showConfig();

        void showAbout();

        void newTxStatus(bool status);

        void newTxFrequency(int txFrequency);

        void newTxVolume(qreal txVolume);

        void newMonitorStatus(bool status);

        void newMonitorFrequency(int monitorFrequency);

        void newMonitorVolume(qreal monitorVolume);

        void newMorseStatus(bool status);
    };
}

#endif
