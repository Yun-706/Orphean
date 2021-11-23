#pragma once

#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>

class OrpheanAudioDevice
{
public:
	static QList<QAudioDeviceInfo> GetInputDevicesInfo();
	static QList<QAudioDeviceInfo> GetOutputDevicesInfo();
	static QAudioDeviceInfo GetDefaultInputDeviceInfo();
	static QAudioDeviceInfo GetDefaultOutputDeviceInfo();
};


class AudioInputDevice : public OrpheanAudioDevice
{
public:
	AudioInputDevice(QString devName);

};
