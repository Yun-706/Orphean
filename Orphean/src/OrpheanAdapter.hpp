﻿#pragma once

#include "Orphean.h"

class OrpheanAdapter : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool openInputDevice(QString devName) {
        return Orphean::getInstance()->openInputDevice(devName);
    }

    Q_INVOKABLE bool openOutputDevice(QString devName) {
        return Orphean::getInstance()->openOutputDevice(devName);
    }

    Q_INVOKABLE void getInputDevices() {
        return Orphean::getInstance()->getInputDevices();
    }

    Q_INVOKABLE void getOutputDevices() {
        return Orphean::getInstance()->getOutputDevices();
    }
};
