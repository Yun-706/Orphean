#include "pch.h"
#include "AudioDevice.h"

QList<QAudioDeviceInfo> OrpheanAudioDevice::GetInputDevicesInfo() {
	return QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioInput);
}

QList<QAudioDeviceInfo> OrpheanAudioDevice::GetOutputDevicesInfo() {
	return QAudioDeviceInfo::availableDevices(QAudio::Mode::AudioOutput);
}

QAudioDeviceInfo OrpheanAudioDevice::GetDefaultInputDeviceInfo() {
	return QAudioDeviceInfo::defaultInputDevice();
}

QAudioDeviceInfo OrpheanAudioDevice::GetDefaultOutputDeviceInfo() {
	return QAudioDeviceInfo::defaultOutputDevice();
}