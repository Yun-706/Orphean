#pragma once
#include <QtMultimedia/qaudioinput>
#include <QtMultimedia/qaudiooutput>
#include <qstring>
#include <QtMultimedia/qaudioformat>
#include <qiodevice>
#include <QtMultimedia/qaudiodeviceinfo>
#include <QtMultimedia/qaudioformat>
#include <qthread>

extern "C" {
#include "rnnoise-master/src/rnnoise.h"
}

class QIODeviceManager
{
	QIODevice* d;
public:
	QIODeviceManager(QIODevice* device) :d(device) {};
	~QIODeviceManager() {
		if (d != nullptr) {
			d->close();
			delete d;
		}
	}
};

class Work : public QThread
{
	Q_OBJECT

	QAudioDeviceInfo inputDevice, outputDevice;
	bool lockVolume;
	int volume;
	int bufferFrameCount;


	DenoiseState* st;

	const static long FRAME_SIZE = 480;

protected:
	void run() override {

		while (!toQuit) {
			while (toStop && (!toQuit)) {
				QThread::msleep(200);
			}
			if (toQuit) {
				return;
			}

			QAudioFormat fmt;
			fmt.setSampleRate(48000);
			fmt.setSampleSize(16);
			fmt.setChannelCount(1);
			fmt.setCodec("audio/pcm");
			fmt.setByteOrder(QAudioFormat::LittleEndian);
			fmt.setSampleType(QAudioFormat::UnSignedInt);
			QAudioInput input(inputDevice, fmt);
			QAudioOutput output(outputDevice, fmt);

			QIODevice* in = input.start();
			QIODevice* out = output.start();

			QIODeviceManager inManager(in);
			QIODeviceManager outManager(out);

			if (in == nullptr || out == nullptr) {
				toStop = true;
				if (in == nullptr && out == nullptr) {
					emit echo(4);
				}
				else {
					if (in == nullptr) emit echo(2);
					if (out == nullptr) emit echo(3);
				}
			}
			if (!toStop) {
				emit echo(1);

				QByteArray buffer;
				while (!toStop) {
					if (lockVolume) input.setVolume(volume * 0.01);
					buffer.append(in->readAll());
					while (buffer.size() > FRAME_SIZE * bufferFrameCount * 2) {
						doDenoise(buffer.left(FRAME_SIZE * bufferFrameCount * 2), out, 1);
						buffer = buffer.mid(FRAME_SIZE * bufferFrameCount * 2);
					}
					QThread::msleep(1);
				}
			}
			emit echo(0);
		}
	}

private:
	void doDenoise(QByteArray buffer, QIODevice* out, int channel) {
		qint16* raw = (qint16*)buffer.data();
		for (int j = 0; j < buffer.size() / FRAME_SIZE / 2; ++j) {
			float x[FRAME_SIZE];
			for (int i = 0; i < FRAME_SIZE; ++i) x[i] = (FRAME_SIZE * j + raw)[i];
			rnnoise_process_frame(st, x, x);
			for (int i = 0; i < FRAME_SIZE; ++i) (FRAME_SIZE * j + raw)[i] = x[i];
		}
		out->setCurrentWriteChannel(channel);
		out->write(buffer);
	}

public:
	volatile bool toStop;
	volatile bool toQuit;

	Work() : toStop(true), toQuit(false), lockVolume(false), st(rnnoise_create(NULL)), bufferFrameCount(3) {};
	~Work() {
		rnnoise_destroy(st);
	}

	void resetDevices(QAudioDeviceInfo _inputDevice, QAudioDeviceInfo _outputDevice) {
		inputDevice = _inputDevice;
		outputDevice = _outputDevice;
	}

	void resetSettings(int bufferFrameCount, bool _lockVolume, int _volume) {
		bufferFrameCount = bufferFrameCount;
		lockVolume = _lockVolume;
		volume = _volume;
	}

signals:
	void echo(int code);
};
