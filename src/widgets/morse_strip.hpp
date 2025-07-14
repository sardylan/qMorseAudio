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

#ifndef __MORSEAUDIO__WIDGETS__MORSE_STRIP__H
#define __MORSEAUDIO__WIDGETS__MORSE_STRIP__H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QList>

#include <QtGui/QPen>

#include <QtOpenGLWidgets/QOpenGLWidget>

#define MORSE_STRIP_TIMER_MILLIS_MIN 5
#define MORSE_STRIP_TIMER_MILLIS_MAX  20
#define MORSE_STRIP_TIMER_MILLIS_DEFAULT 10

#define MORSE_STRIP_TICK_INTERVAL_SMALL 25
#define MORSE_STRIP_TICK_INTERVAL_BIG 4

namespace morseaudio::widgets {
    class MorseStrip final : public QOpenGLWidget {
        Q_OBJECT

    public:
        explicit MorseStrip(QWidget *parent = nullptr);

        ~MorseStrip() override;

    public slots:
        void updateKey(bool key);

        void setTimerMillis(int timerMillis);

        void start();

        void stop();

        void clear();

    protected:
        void paintEvent(QPaintEvent *e) override;

    private:
        bool key;
        QTimer timer;
        QList<bool> points;
        int timerMillis;
        int tickShiftSmall;
        int tickShiftBig;

        QPen whitePen;
        QPen blackPen;
        QPen greyPen;

        static constexpr int shiftLimitSmall = MORSE_STRIP_TICK_INTERVAL_SMALL;
        static constexpr int shiftLimitBig = MORSE_STRIP_TICK_INTERVAL_SMALL * MORSE_STRIP_TICK_INTERVAL_BIG;

    private slots:
        void animate();

        void updateTimerInterval();
    };
}

#endif
