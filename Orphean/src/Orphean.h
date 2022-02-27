#pragma once
#include "pch.h"
#include <QObject>
#include <QQmlApplicationEngine>
#include "Devices.h"

class Orphean : public QObject
{
	Q_OBJECT
    QQmlApplicationEngine engine;
    QStringList inputDevices;
    QStringList outputDevices;

    QMap<QString, OrpheanAudioDevice> devices;
public:
	Orphean();
    static Orphean* getInstance();

    bool openInputDevice(QString devName);
    bool openOutputDevice(QString devName);
    void getInputDevices();
    void getOutputDevices();

private:
    void init();
    static Orphean* s_instance;
};

