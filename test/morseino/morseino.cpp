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

// #include "morseino.hpp"
//
// #include <QtCore/QDebug>
//
// #include <QtTest/QTest>
// #include <QtTest/QSignalSpy>
//
// using namespace morseaudio::morseino;
//
// QTEST_MAIN(MorseInoTest)
//
// void MorseInoTest::putChar(QBuffer *buffer, char c) {
//     buffer->putChar(c);
//     buffer->seek(buffer->size() - 1);
//     emit buffer->readyRead();
// }
//
// void MorseInoTest::initTestCase() {
//     morseIno = new MorseIno(&device);
// }
//
// void MorseInoTest::cleanupTestCase() {
//     delete morseIno;
//     morseIno = nullptr;
// }
//
// void MorseInoTest::init() const {
//     QVERIFY(!device.isOpen());
//
//     QSignalSpy statusSpy(morseIno, &MorseIno::newStatus);
//     QVERIFY(statusSpy.isValid());
//
//     QMetaObject::invokeMethod(morseIno, "start", Qt::QueuedConnection);
//     QVERIFY(statusSpy.wait());
//     QCOMPARE(statusSpy.count(), 1);
//     QCOMPARE(statusSpy.takeFirst().at(0).toBool(), true);
//     QCOMPARE(device.isOpen(), true);
// }
//
// void MorseInoTest::cleanup() const {
//     QVERIFY(device.isOpen());
//
//     QSignalSpy statusSpy(morseIno, &MorseIno::newStatus);
//     QVERIFY(statusSpy.isValid());
//
//     QMetaObject::invokeMethod(morseIno, "stop", Qt::QueuedConnection);
//     QVERIFY(statusSpy.wait());
//     QCOMPARE(statusSpy.count(), 1);
//     QCOMPARE(statusSpy.takeFirst().at(0).toBool(), false);
//     QCOMPARE(device.isOpen(), false);
// }
//
// void MorseInoTest::testSignals() {
//     QSignalSpy keySpy(morseIno, &MorseIno::newKey);
//     QVERIFY(keySpy.isValid());
//
//     putChar(&device, MORSEINO_CHAR_ON);
//     QVERIFY(keySpy.wait());
//     QCOMPARE(keySpy.count(), 1);
//     QCOMPARE(keySpy.takeFirst().at(0).toBool(), true);
//     QCOMPARE(keySpy.count(), 0);
//     keySpy.clear();
//
//     putChar(&device, MORSEINO_CHAR_OFF);
//     QVERIFY(keySpy.wait());
//     QCOMPARE(keySpy.count(), 1);
//     QCOMPARE(keySpy.takeFirst().at(0).toBool(), false);
//     QCOMPARE(keySpy.count(), 0);
//     keySpy.clear();
// }
