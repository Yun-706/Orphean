#include "pch.h"
#include <QGuiApplication>
#include <QFont>
#include "OrpheanAdapter.hpp"

int main(int argc, char *argv[])
{
    qmlRegisterType<OrpheanAdapter>("Orphean", 1, 0, "Orphean");

#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QFont font("Microsoft YaHei");
    app.setFont(font);

    Orphean orphean;

    return app.exec();
}
