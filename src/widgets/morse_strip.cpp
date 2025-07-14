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

#include "morse_strip.hpp"

#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QPaintEvent>

using namespace morseaudio::widgets;

MorseStrip::MorseStrip(QWidget *parent) : QOpenGLWidget(parent),
                                          key(false),
                                          timer(nullptr),
                                          timerMillis(0),
                                          tickShiftSmall(0),
                                          tickShiftBig(0),
                                          whitePen(Qt::white),
                                          blackPen(Qt::black),
                                          greyPen(Qt::gray) {
    whitePen.setWidth(0);
    blackPen.setWidth(0);
    greyPen.setWidth(0);

    tickShiftSmall = 0;
    tickShiftBig = 0;
    timerMillis = MORSE_STRIP_TIMER_MILLIS_DEFAULT;

    setAutoFillBackground(false);

    connect(&timer, &QTimer::timeout, this, &MorseStrip::animate);
    timer.setSingleShot(false);
    updateTimerInterval();
}

MorseStrip::~MorseStrip() = default;

void MorseStrip::updateKey(const bool key) {
    this->key = key;
}

void MorseStrip::setTimerMillis(const int timerMillis) {
    if (timerMillis == this->timerMillis)
        return;

    if (timerMillis < MORSE_STRIP_TIMER_MILLIS_MIN)
        this->timerMillis = MORSE_STRIP_TIMER_MILLIS_MIN;
    else if (timerMillis > MORSE_STRIP_TIMER_MILLIS_MAX)
        this->timerMillis = MORSE_STRIP_TIMER_MILLIS_MAX;
    else
        this->timerMillis = timerMillis;

    updateTimerInterval();
}

void MorseStrip::start() {
    QMetaObject::invokeMethod(&timer, qOverload<>(&QTimer::start));
}

void MorseStrip::stop() {
    QMetaObject::invokeMethod(&timer, &QTimer::stop);
}

void MorseStrip::clear() {
    points.clear();
    tickShiftSmall = 0;
    tickShiftBig = 0;

    if (!timer.isActive())
        animate();
}

void MorseStrip::paintEvent(QPaintEvent *e) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(e->rect(), Qt::white);
    painter.translate(0, 0);

    if (points.size() == painter.window().width()) {
        tickShiftSmall++;
        if (tickShiftSmall == shiftLimitSmall)
            tickShiftSmall = 0;
        tickShiftBig++;
        if (tickShiftBig == shiftLimitBig)
            tickShiftBig = 0;
    }

    for (int x = 0; x < points.size(); x++) {
        painter.save();

        painter.setPen(points.at(x) ? blackPen : whitePen);
        painter.drawPoint(QPoint(x, 12));
        painter.drawPoint(QPoint(x, 13));
        painter.drawPoint(QPoint(x, 14));
        painter.drawPoint(QPoint(x, 15));
        painter.drawPoint(QPoint(x, 16));

        painter.setPen(greyPen);

        if ((x + tickShiftSmall) % shiftLimitSmall == 0)
            painter.drawPoint(QPoint(x, 22));

        if ((x + tickShiftBig) % shiftLimitBig == 0) {
            painter.drawPoint(QPoint(x, 23));
            painter.drawPoint(QPoint(x, 24));
        }

        painter.drawPoint(QPoint(x, 21));

        painter.restore();
    }

    painter.end();
}

void MorseStrip::animate() {
    points.append(key);

    QPainter painter;
    painter.begin(this);
    while (points.size() > painter.window().width())
        points.removeFirst();
    painter.end();

    update();
}

void MorseStrip::updateTimerInterval() {
    timer.setInterval(MORSE_STRIP_TIMER_MILLIS_MAX - (timerMillis - MORSE_STRIP_TIMER_MILLIS_MIN));
}
