#include "pch.h"
#include "Orphean.h"
#include <QQmlContext>

Orphean* Orphean::s_instance = nullptr;

Orphean::Orphean()
{
    init();

    s_instance = this;

    engine.load(QUrl(QStringLiteral("qrc:/qrc/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        exit(-1);
}

Orphean* Orphean::getInstance() {
    return s_instance;
}

void Orphean::init()
{
}

bool Orphean::openInputDevice(QString devName)
{
	return true;
}

bool Orphean::openOutputDevice(QString devName)
{
	return true;
}

void Orphean::getInputDevices()
{
    auto list = QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioInput);
    inputDevices.clear();
    for (auto& i : list) {
        inputDevices.push_back(i.deviceName());
    }
    engine.rootContext()->setContextProperty("inputAudioDeviceNames", inputDevices);
}

void Orphean::getOutputDevices()
{
    auto list = QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioOutput);
    outputDevices.clear();
    for (auto& i : list) {
        outputDevices.push_back(i.deviceName());
    }
    engine.rootContext()->setContextProperty("outputAudioDeviceNames", outputDevices);
}

