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

#include "about.hpp"

#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

using namespace morseaudio::morseaudio::windows;

About::About(QWidget *parent): QDialog(parent),
                               ui(new Ui::About()) {
    ui->setupUi(this);

    ui->titleLabel->setText(QString("%1 %2").arg(QCoreApplication::applicationName(),
                                                 QCoreApplication::applicationVersion()));

    connect(ui->buttonBox->button(QDialogButtonBox::Close), &QPushButton::clicked, this, &About::close);
}

About::~About() {
    delete ui;
}
