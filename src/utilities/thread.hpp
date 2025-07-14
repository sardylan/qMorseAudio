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

#ifndef __MORSEAUDIO__UTILITIES__THREAD__H
#define __MORSEAUDIO__UTILITIES__THREAD__H

#include <QtCore/QThread>
#include <QtCore/QString>

namespace morseaudio::utilities {
    class Thread {
    public:
        explicit Thread(QObject *object, const QString &threadName = "");

        ~Thread();

    private:
        QThread *thread;
    };
}

#endif
