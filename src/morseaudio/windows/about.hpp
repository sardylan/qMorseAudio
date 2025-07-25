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

#ifndef __MORSEAUDIO__MORSEAUDIO__WINDOWS__ABOUT__H
#define __MORSEAUDIO__MORSEAUDIO__WINDOWS__ABOUT__H

#include <QtWidgets/QDialog>

#include "ui_about.h"

namespace morseaudio::morseaudio::windows {
    class About final : public QDialog {
        Q_OBJECT

    public:
        explicit About(QWidget *parent = nullptr);

        ~About() override;

    private:
        Ui::About *ui;
    };
}

#endif
