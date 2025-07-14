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

#ifndef __MORSEAUDIO__AUDIO__DEFAULT__H
#define __MORSEAUDIO__AUDIO__DEFAULT__H

#include <QtCore/QByteArray>

#include <QtMultimedia/QAudioFormat>

#define AUDIO_DEVICE_ID_DEFAULT QByteArray()
#define AUDIO_SAMPLERATE_DEFAULT 48000
#define AUDIO_SAMPLE_FORMAT_DEFAULT QAudioFormat::Int16
#define AUDIO_CHANNELS_DEFAULT 2
#define AUDIO_FREQUENCY_DEFAULT 600
#define AUDIO_VOLUME_DEFAULT 1.0

#endif
