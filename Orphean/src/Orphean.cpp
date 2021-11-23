#include "pch.h"
#include "Orphean.h"

Orphean* Orphean::s_instance = nullptr;

Orphean::Orphean()
{
    engine.load(QUrl(QStringLiteral("qrc:/qrc/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        exit(-1);

    init();

    s_instance = this;
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

