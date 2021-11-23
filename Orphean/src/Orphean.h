#pragma once
#include "pch.h"
#include <QObject>
#include <QQmlApplicationEngine>
#include "Devices.h"

class Orphean : public QObject
{
	Q_OBJECT
    QQmlApplicationEngine engine;

    QMap<QString, OrpheanAudioDevice> m_devices;
public:
	Orphean();
    static Orphean* getInstance();

    bool openInputDevice(QString devName);
    bool openOutputDevice(QString devName);


private:
    void init();
    static Orphean* s_instance;
};

